#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/ADT/SCCIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/TypeBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Local.h"

#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/ADT/StringRef.h"

#include <vector>
#include <queue>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>

#include "llvm/Analysis/CFG.h"

using namespace llvm;

Module *mod_ptr;

struct store_sets {
  std::vector<StoreInst *> in;
  std::vector<std::string> in_vars;

  std::vector<StoreInst *> out;
  std::vector<std::string> out_vars;
};

std::map<std::string, store_sets *> store_sets_map;

StringRef input_array = "array";
//StringRef input_array = "yytable";
// StringRef input_array = "yy_accept";

// Structure for holding information about our array
struct array_info {

  StringRef name;
  Type *element_type;
  std::map<int, std::vector<int> > val2IdxMap;
  std::vector<int> content;
  std::vector<int> range_idx;
  std::vector<int> range_val;
  std::vector<LoadInst *> loads;
  Constant *array_const;
};

// Map where key is the name of the array and val is the corresponding
// array_info
std::map<StringRef, array_info *> ArrayMap;

void buildArrayMap() {
  // Get the global variable list as arrays (even local) with
  // initialized values
  iplist<GlobalVariable> &gvl = mod_ptr->getGlobalList();

  // For each global get all of its information
  for (iplist<GlobalVariable>::iterator it = gvl.begin(); it != gvl.end();
       it++) {
    if (it->hasInitializer()) {
      if (ArrayType *at =
              dyn_cast<ArrayType>(it->getInitializer()->getType())) {
        if (!isa<ConstantAggregateZero>(it->getInitializer())) {
          // FIXME: remove and generalize
          if (at->getArrayElementType()->isIntegerTy()) {
            Constant *array_const = dyn_cast<Constant>(it->getInitializer());

            struct array_info *temp = new array_info;
            temp->name = it->getName();
            temp->element_type =
                array_const->getAggregateElement((unsigned)0)->getType();
            temp->array_const = array_const;

            // Build the val2IdxMap for each array
            for (unsigned int i = 0; i < at->getNumElements(); i++) {
              if (ConstantInt *ci = dyn_cast<ConstantInt>(
                      array_const->getAggregateElement(i))) {
                // Add to content so we have the regular layout of the
                // array in memory
                temp->content.push_back(ci->getSExtValue());
                std::map<int, std::vector<int> >::iterator found_val =
                    temp->val2IdxMap.find(ci->getSExtValue());
                // If the value is already in the map
                if (found_val != temp->val2IdxMap.end()) {
                  found_val->second.push_back(i);
                } else {
                  temp->val2IdxMap.insert(std::make_pair(
                      ci->getSExtValue(), *(new std::vector<int>)));
                  temp->val2IdxMap[ci->getSExtValue()].push_back(i);
                }
              }
            }

            // Insert the created array info structure into the array map
            ArrayMap.insert(std::make_pair(it->getName(), temp));
          }
        }
      }
    }
  }
}

std::vector<StoreInst *> getReachingStores(LoadInst *li) {

  std::vector<StoreInst *> result;
  std::string var_name = li->getOperand(0)->getName().str();
  BasicBlock *bb = li->getParent();

  bool store_in_bb = false;

  // If the load from an nameless internal variable it has no reaching
  // stores
  if(var_name == "") {
	  return result;
  }

  // For each instruction before the load, look for stores to the same variable
  // being
  // loaded. Store the most immediate store into the result.
  for (BasicBlock::iterator inst = bb->begin(), inst_e = bb->end();
       inst != inst_e; ++inst) {
    if (StoreInst *si = dyn_cast<StoreInst>(&*inst)) {
      if (si->getOperand(1)->getName().str() == var_name) {
        store_in_bb = true;
        if (result.size() == 0) {
          result.push_back(si);
        } else {
          result[0] = si;
        }
      }
    } else if (LoadInst *curr_li = dyn_cast<LoadInst>(&*inst)) {
      if (curr_li == li) {
        break;
      }
    }     
  }

  // If there is a store to the variable in the load's bb it will be the only
  // reaching store. Thus, we are done
  if (store_in_bb) {
    return result;
  }

  // If there was not a store we must get all the stores in the bb's in set
  if (store_sets_map.find(bb->getName().str()) != store_sets_map.end()) {
    std::vector<StoreInst *> in_set =
        store_sets_map.find(bb->getName().str())->second->in;
    for (int i = 0; i < in_set.size(); i++) {
      if (in_set[i]->getOperand(1)->getName().str() == var_name) {
        result.push_back(in_set[i]);
      }
    }
  } else {
    errs() << "getReachingStores: Can't find the bb's store set\n";
  }

  return result;
}

struct var_condition {
  CmpInst *ci;
  std::vector<StoreInst *> reaching_stores;
};

// Find all the cmpinst that perform a comparison between an array read and
// a constant
std::vector<struct var_condition> getArrayVarConditions(std::string array) {

  std::vector<struct var_condition> result;

  // Iterate through each instruction
  for (Module::iterator func = mod_ptr->begin(), func_e = mod_ptr->end();
       func != func_e; ++func) {
    for (Function::iterator bb = func->begin(), bb_e = func->end(); bb != bb_e;
         ++bb) {
      for (BasicBlock::iterator inst = bb->begin(), inst_e = bb->end();
           inst != inst_e; ++inst) {
        if (CmpInst *ci = dyn_cast<CmpInst>(&*inst)) {

          // Find which operand of the cmp is a constant
          int variable_operand_num;
          if (ConstantInt *cons = dyn_cast<ConstantInt>(ci->getOperand(0))) {
            variable_operand_num = 1;
          } else if (ConstantInt *cons =
                         dyn_cast<ConstantInt>(ci->getOperand(1))) {
            variable_operand_num = 0;
          } else {
            // If neither is a constant skip it
            continue;
          }

          // Get the load instruction being used in the cmpinst
          if (LoadInst *li =
                  dyn_cast<LoadInst>(ci->getOperand(variable_operand_num))) {
            //
            // Get all the stores to this variable that reach the load
            std::vector<StoreInst *> reaching_stores = getReachingStores(li);

            // For each reaching store
            for (int i = 0; i < reaching_stores.size(); i++) {

              LoadInst *li_2;

              // Get the instruction that is being stored into the variable
              if (isa<LoadInst>(reaching_stores[i]->getOperand(0))) {
                li_2 = dyn_cast<LoadInst>(reaching_stores[i]->getOperand(0));
              } else if (SExtInst *sei = dyn_cast<SExtInst>(
                             reaching_stores[i]->getOperand(0))) {
                if (LoadInst *li_3 = dyn_cast<LoadInst>(sei->getOperand(0))) {
                  li_2 = li_3;
                }
              } else {
		continue;
	      }
              // If the instruction being stored is an array access
              if (GetElementPtrInst *gep =
                      dyn_cast<GetElementPtrInst>(li_2->getOperand(0))) {
		    if(gep->getOperand(0)->getType()->isPointerTy()) {
		      PointerType *pt = dyn_cast<PointerType>(gep->getOperand(0)->getType());
		      if(!pt->getElementType()->isArrayTy()) {
		        continue;
		      }
		    }
                //if (gep->getOperand(0)->getName().str() == array) {
                  // Create the variable condition and add it to the
                  // result
                  struct var_condition vc;
                  vc = *(new struct var_condition);
                  vc.ci = ci;
                  vc.reaching_stores = reaching_stores;
                  result.push_back(vc);
                  break;
                //}
              }
            }
          }
        }
      }
    }
  }

  return result;
}

// Returns the list of conditions that are dependent on an array
std::vector<Instruction *> getArrayConditions(std::string array) {
  std::vector<Instruction *> result;

  // Iterate through each instruction
  for (Module::iterator func = mod_ptr->begin(), func_e = mod_ptr->end();
       func != func_e; ++func) {
    for (Function::iterator bb = func->begin(), bb_e = func->end(); bb != bb_e; ++bb) {
      for (BasicBlock::iterator inst = bb->begin(), inst_e = bb->end();
           inst != inst_e; ++inst) {
        // If the instruction is a GetElementPtr
        if (GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(inst)) {
          // If the gep is accessing the desired array
          //if (gep->getOperand(0)->getName().str() == array) {
            // Iterate through each use of the gep instruction
            for (Value::use_iterator use = gep->use_begin();
                 use != gep->use_end(); ++use) {
              // If the use instruction is a load
              if (LoadInst *li = dyn_cast<LoadInst>(*use)) {
                // For each use of the load
                for (Value::use_iterator li_use = li->use_begin();
                     li_use != li->use_end(); ++li_use) {
                  // If load is used as a parameter to a cmp instruction
                  if (CmpInst *ci = dyn_cast<CmpInst>(*li_use)) {

	            int variable_operand_num;

                    if (ConstantInt *cons = dyn_cast<ConstantInt>(ci->getOperand(0))) {
                      variable_operand_num = 1;
                    } else if (ConstantInt *cons =
                                   dyn_cast<ConstantInt>(ci->getOperand(1))) {
                      variable_operand_num = 0;
                    } else {
                      // If neither is a constant skip it
                      continue;
                    }

		    if(gep->getOperand(0)->getType()->isPointerTy()) {
		      PointerType *pt = dyn_cast<PointerType>(gep->getOperand(0)->getType());
		      if(!pt->getElementType()->isArrayTy()) {
		        continue;
		      }
		    }
                    result.push_back(ci);
                  }
                }
              }
            }
          //}
        }
      }
    }
  }

  return result;
}

CmpInst::Predicate getOperator(Instruction *conditional) {
  bool lhs = false;

  if (CmpInst *ci = dyn_cast<CmpInst>(conditional)) {
    // Determine if the constant value is LHS or RHS of CmpInst
    if (ConstantInt *cons = dyn_cast<ConstantInt>(ci->getOperand(0))) {
      lhs = true;
    }

    // Handle every possible type of integer cmp. Note that if the constant
    // value in the comparison is on the left side the operator is reversed.
    // This makes it easier to deal with as in later functions I can always
    // assume that the constant value can be used on the right side
    // FIXME: extend to other types
    CmpInst::Predicate predicate = ci->getPredicate();
    switch (predicate) {
    case CmpInst::ICMP_EQ:
    case CmpInst::ICMP_NE:
      return predicate;
    case CmpInst::ICMP_SGT:
      return lhs ? CmpInst::ICMP_SLT : predicate;
    case CmpInst::ICMP_SGE:
      return lhs ? CmpInst::ICMP_SLE : predicate;
    case CmpInst::ICMP_SLT:
      return lhs ? CmpInst::ICMP_SGT : predicate;
    case CmpInst::ICMP_SLE:
      return lhs ? CmpInst::ICMP_SGE : predicate;
    case CmpInst::ICMP_UGT:
      return lhs ? CmpInst::ICMP_ULT : predicate;
    case CmpInst::ICMP_UGE:
      return lhs ? CmpInst::ICMP_ULE : predicate;
    case CmpInst::ICMP_ULT:
      return lhs ? CmpInst::ICMP_UGT : predicate;
    case CmpInst::ICMP_ULE:
      return lhs ? CmpInst::ICMP_UGE : predicate;
    default:
      errs() << "getOperator: instruction is not integer CmpInst\n";
      return CmpInst::BAD_ICMP_PREDICATE;
    }
  }
  errs() << "getOperator: instruction is not a CmpInst\n";
  return CmpInst::BAD_ICMP_PREDICATE;
}

int getValue(Instruction *conditional) {
  if (CmpInst *ci = dyn_cast<CmpInst>(conditional)) {
    // Handle both instances of the constant value being on the right
    // or left side of the cmp inst
    if (ConstantInt *cons = dyn_cast<ConstantInt>(ci->getOperand(0))) {
      return cons->getSExtValue();
    } else if (ConstantInt *cons = dyn_cast<ConstantInt>(ci->getOperand(1))) {
      return cons->getSExtValue();
    }
  } else {
    errs() << "getValue: instruction is not a CmpInst\n";
    return -1;
  }
  return -1;
}

Instruction *getIndex(Instruction *conditional) {
  if (CmpInst *ci = dyn_cast<CmpInst>(conditional)) {
    // Again, handle both cases of the array being on the
    // right or left side of the cmp inst
    if (LoadInst *li = dyn_cast<LoadInst>(ci->getOperand(0))) {
      if (GetElementPtrInst *gep =
              dyn_cast<GetElementPtrInst>(li->getOperand(0))) {
        if(gep->getOperand(0)->getType()->isPointerTy()) {
          PointerType *pt = dyn_cast<PointerType>(gep->getOperand(0)->getType());
          if(!pt->getElementType()->isArrayTy()) {
            return NULL;
          }
        }
        return dyn_cast<Instruction>(gep->getOperand(2));
      }
    } else if (LoadInst *li = dyn_cast<LoadInst>(ci->getOperand(1))) {
      if (GetElementPtrInst *gep =
              dyn_cast<GetElementPtrInst>(li->getOperand(0))) {
        if(gep->getOperand(0)->getType()->isPointerTy()) {
          PointerType *pt = dyn_cast<PointerType>(gep->getOperand(0)->getType());
          if(!pt->getElementType()->isArrayTy()) {
            return NULL;
          }
        }
        return dyn_cast<Instruction>(gep->getOperand(2));
      }
    } else if(SExtInst *sei = dyn_cast<SExtInst>(ci->getOperand(0))) {
	    if(LoadInst *li = dyn_cast<LoadInst>(sei->getOperand(0))) {
		    if(GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(li->getOperand(0))) {
			if(gep->getOperand(0)->getType()->isPointerTy()) {
			  PointerType *pt = dyn_cast<PointerType>(gep->getOperand(0)->getType());
			  if(!pt->getElementType()->isArrayTy()) {
			    return NULL;
			  }
			}
        		return dyn_cast<Instruction>(gep->getOperand(2));
		    }
	    }
    } else if(SExtInst *sei = dyn_cast<SExtInst>(ci->getOperand(1))) {
	    if(LoadInst *li = dyn_cast<LoadInst>(sei->getOperand(0))) {
		    if(GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(li->getOperand(0))) {
			if(gep->getOperand(0)->getType()->isPointerTy()) {
			  PointerType *pt = dyn_cast<PointerType>(gep->getOperand(0)->getType());
			  if(!pt->getElementType()->isArrayTy()) {
			    return NULL;
			  }
			}
        		return dyn_cast<Instruction>(gep->getOperand(2));
		    }
	    }
    }
  } else if (StoreInst *si = dyn_cast<StoreInst>(conditional)) {
    if (LoadInst *li = dyn_cast<LoadInst>(si->getOperand(0))) {
      if (GetElementPtrInst *gep =
              dyn_cast<GetElementPtrInst>(li->getOperand(0))) {
	if(gep->getOperand(0)->getType()->isPointerTy()) {
	  PointerType *pt = dyn_cast<PointerType>(gep->getOperand(0)->getType());
	  if(!pt->getElementType()->isArrayTy()) {
	    return NULL;
	  }
	}
        return dyn_cast<Instruction>(gep->getOperand(2));
      } else {
        return NULL;
      }
    }
    if (SExtInst *sei = dyn_cast<SExtInst>(si->getOperand(0))) {
      if (LoadInst *li = dyn_cast<LoadInst>(sei->getOperand(0))) {
        if (GetElementPtrInst *gep =
                dyn_cast<GetElementPtrInst>(li->getOperand(0))) {
	  if(gep->getOperand(0)->getType()->isPointerTy()) {
	    PointerType *pt = dyn_cast<PointerType>(gep->getOperand(0)->getType());
	    if(!pt->getElementType()->isArrayTy()) {
	      return NULL;
	    }
	  }
          return dyn_cast<Instruction>(gep->getOperand(2));
        } else {
          return NULL;
        }
      }
    }
  } else {
  errs() << "getIndex: instruction is not a CmpInst\n";
  conditional->dump();
  }

  return NULL;
}

// Functions used for performing all the different comparisons
bool eq(int lhs, int rhs) { return (lhs == rhs); }

bool ne(int lhs, int rhs) { return (lhs != rhs); }

bool lt(int lhs, int rhs) { return (lhs < rhs); }

bool gt(int lhs, int rhs) { return (lhs > rhs); }

bool lte(int lhs, int rhs) { return (lhs <= rhs); }

bool gte(int lhs, int rhs) { return (lhs >= rhs); }

std::vector<bool> computeValidIndexes(Instruction *conditional,
                                      std::string array_name,
                                      CmpInst::Predicate op, int val) {

  std::vector<bool> result;
  struct array_info *ai; // = ArrayMap[array_name];
  bool (*op_func)(int, int);

  // Find the array in the array map or return
  if (ArrayMap.find(array_name) != ArrayMap.end()) {
    ai = ArrayMap[array_name];
  } else if (ArrayMap.find(
                 conditional->getParent()->getParent()->getName().str() + "." +
                 array_name) != ArrayMap.end()) {
    ai = ArrayMap[conditional->getParent()->getParent()->getName().str() + "." +
                  array_name];
  } else {
    errs() << "computeValidIndexes: " << array_name << " not found in map\n";
    return result;
  }

  // Assign a function pointer to the correct type of comparison
  switch (op) {
  case CmpInst::ICMP_EQ:
    op_func = eq;
    break;
  case CmpInst::ICMP_NE:
    op_func = ne;
    break;
  case CmpInst::ICMP_SGT:
  case CmpInst::ICMP_UGT:
    op_func = gt;
    break;
  case CmpInst::ICMP_SGE:
  case CmpInst::ICMP_UGE:
    op_func = gte;
    break;
  case CmpInst::ICMP_SLT:
  case CmpInst::ICMP_ULT:
    op_func = lt;
    break;
  case CmpInst::ICMP_SLE:
  case CmpInst::ICMP_ULE:
    op_func = lte;
    break;
  default:
    errs() << "computeValidIndexes: " << op << " not valid operator\n";
    break;
  }

  // Create a mask indicating if the index satisfies the constraint or not
  result.resize(ai->content.size());
  for (int i = 0; i < ai->content.size(); i++) {
    if (op_func(ai->content[i], val)) {
      result[i] = true;
    } else {
      result[i] = false;
    }
  }

  return result;
}

std::vector<std::pair<int, int> > computeRanges(std::vector<bool> input) {
  bool range_started = false;
  std::pair<int, int> curr_range;
  std::vector<std::pair<int, int> > result;

  // Find all the different ranges that satisfy the conditional
  for (int i = 0; i < input.size(); i++) {
    if (input[i] == true) {
      // If the value is the first true in the sequence
      if (range_started == false) {
        range_started = true;
        curr_range.first = i;
      }

      // If the last value is true
      if (i == (input.size() - 1)) {
        range_started = false;
        curr_range.second = i;
        result.push_back(curr_range);
      }
    } else if (range_started) {
      range_started = false;
      curr_range.second = i - 1;
      result.push_back(curr_range);
    }
  }

  return result;
}

void rewriteCondition(Instruction *conditional, Instruction *index_val,
                      std::vector<std::pair<int, int> > index_ranges) {
  std::vector<BinaryOperator *> and_vector;

  // If there are any ranges that satisfy the conditional
  if (index_ranges.size() > 0) {
    for (int i = 0; i < index_ranges.size(); i++) {
      // Create the first cmp
      Value *first_range_constant =
          ConstantInt::getSigned(index_val->getType(), index_ranges[i].first);
      ICmpInst *first_cmp_inst =
          new ICmpInst(conditional, ICmpInst::ICMP_SGE, index_val,
                       first_range_constant, "first_cmp");
      // Create the second cmp
      Value *second_range_constant =
          ConstantInt::getSigned(index_val->getType(), index_ranges[i].second);
      ICmpInst *second_cmp_inst =
          new ICmpInst(conditional, ICmpInst::ICMP_SLE, index_val,
                       second_range_constant, "second_cmp");
      // Create the instruction that And's the two cmp instructions
      BinaryOperator *cmp_and =
          BinaryOperator::CreateAnd(first_cmp_inst, second_cmp_inst, "cmp_and");
      cmp_and->insertBefore(conditional);

      and_vector.push_back(cmp_and);
    }

    // If there is more than one range of indexes that satisfy the conditional
    if (and_vector.size() > 1) {
      // Start with the initial and as the first instruction being or'd together
      BinaryOperator *curr_or = and_vector[0];
      for (int i = 1; i < and_vector.size(); i++) {
        BinaryOperator *new_or =
            BinaryOperator::CreateOr(curr_or, and_vector[i]);
        new_or->insertBefore(conditional);
        curr_or = new_or;
      }

      // Replace the uses of the original cmp inst
      conditional->replaceAllUsesWith(curr_or);
    } else {
      // Replace the uses of the original cmp inst
      conditional->replaceAllUsesWith(and_vector[0]);
    }
  }
}

void debugPrintValidIndexesMask(std::vector<bool> indexes) {
  errs() << "Index mask: ";
  for (int j = 0; j < indexes.size(); j++) {
    if (indexes[j])
      errs() << 1 << " ";
    else
      errs() << 0 << " ";
  }
  errs() << "\n";
}

void debugPrintRanges(std::vector<std::pair<int, int> > ranges) {
  errs() << "Index range:";
  for (int i = 0; i < ranges.size(); i++) {
    errs() << "[" << ranges[i].first << "," << ranges[i].second << "] ";
  }
  errs() << "\n";
}

void rewriteVarCondition(Instruction *ci, Instruction *ai, Instruction *si,
                         Instruction *index_val,
                         std::vector<std::pair<int, int> > index_ranges) {

  std::vector<BinaryOperator *> and_vector;

  if (index_val != NULL) {

    // If there are any ranges that satisfy the conditional
    if (index_ranges.size() > 0) {
      for (int i = 0; i < index_ranges.size(); i++) {
        // Create the first cmp
        Value *first_range_constant =
            ConstantInt::getSigned(index_val->getType(), index_ranges[i].first);
        ICmpInst *first_cmp_inst =
            new ICmpInst(si, ICmpInst::ICMP_SGE, index_val,
                         first_range_constant, "first_cmp");
        // Create the second cmp
        Value *second_range_constant = ConstantInt::getSigned(
            index_val->getType(), index_ranges[i].second);
        ICmpInst *second_cmp_inst =
            new ICmpInst(si, ICmpInst::ICMP_SLE, index_val,
                         second_range_constant, "second_cmp");
        // Create the instruction that And's the two cmp instructions
        BinaryOperator *cmp_and = BinaryOperator::CreateAnd(
            first_cmp_inst, second_cmp_inst, "cmp_and");
        cmp_and->insertBefore(si);

        and_vector.push_back(cmp_and);
      }

      // If there is more than one range of indexes that satisfy the conditional
      if (and_vector.size() > 1) {
        // Start with the initial and as the first instruction being or'd
        // together
        BinaryOperator *curr_or = and_vector[0];
        for (int i = 1; i < and_vector.size(); i++) {
          BinaryOperator *new_or =
              BinaryOperator::CreateOr(curr_or, and_vector[i]);
          new_or->insertBefore(si);
          curr_or = new_or;
        }

        // Store curr_or to the variable
        new StoreInst(curr_or, ai, si);
      } else {
        // Replace the uses of the original cmp inst
        new StoreInst(and_vector[0], ai, si);
      }
    }
  } else {
    // Non array access store
    CmpInst *new_ci = dyn_cast<CmpInst>(ci);
    int to_replace;

    if (ConstantInt *cons = dyn_cast<ConstantInt>(new_ci->getOperand(0))) {
      ICmpInst *cmp_inst =
          new ICmpInst(si, new_ci->getPredicate(), new_ci->getOperand(0),
                       si->getOperand(0), "no_array_cmp");
      new StoreInst(cmp_inst, ai, si);
    } else if (ConstantInt *cons =
                   dyn_cast<ConstantInt>(new_ci->getOperand(1))) {
      ICmpInst *cmp_inst =
          new ICmpInst(si, new_ci->getPredicate(), si->getOperand(0),
                       new_ci->getOperand(1), "no_array_cmp");
      new StoreInst(cmp_inst, ai, si);
    }
  }
}

void nameBBs() {
  // name every basic block in the module: function name + "bb" + number
  for (Module::iterator func = mod_ptr->begin(), func_e = mod_ptr->end();
       func != func_e; ++func) {
    for (Function::iterator bb = func->begin(), bb_e = func->end(); bb != bb_e;
         ++bb) {
      bb->setName(func->getName().str() + "bb");
    }
  }
}

struct SCC {
  std::vector<BasicBlock *> components;
};

void initStoreSetsMap(std::vector<struct SCC> topo) {

  for (int i = 0; i < topo.size(); i++) {
    for (int j = 0; j < topo[i].components.size(); j++) {

      BasicBlock *curr_bb = topo[i].components[j];
      struct store_sets *curr_store_set = new struct store_sets;
      store_sets_map.insert(std::pair<std::string, struct store_sets *>(
          curr_bb->getName().str(), curr_store_set));
    }
  }
}

std::vector<StoreInst *> storeSetUnion(std::vector<StoreInst *> a,
                                       std::vector<StoreInst *> b) {

  std::set<StoreInst *> all;

  all.insert(a.begin(), a.end());
  all.insert(b.begin(), b.end());

  std::vector<StoreInst *> result(all.begin(), all.end());

  return result;
}

// Function for inserting store instructions that are found in a BB into it's
// out
// set
void BBStoreInsert(std::vector<StoreInst *> *vec, StoreInst *si) {

  // Get the variable that is being stored to
  std::string store_var = si->getOperand(1)->getName();

  // Iterate through the out set
  for (int i = 0; i < vec->size(); i++) {
    std::string curr_var = (*vec)[i]->getOperand(1)->getName();
    // If a more recent store to the variable occurs (store comes later)
    // replace it
    if (store_var == curr_var) {
      (*vec)[i] = si;
      return;
    }
  }

  // If a store to this particular variable has not previously been made
  // at it to the set
  vec->push_back(si);
}

void SCCQueueInsert(std::vector<BasicBlock *> *bbs, BasicBlock *toInsert) {

  bool duplicate = false;
  for (int i = 0; i < bbs->size(); i++) {
    if ((*bbs)[i]->getName().str() == toInsert->getName().str()) {
      duplicate = true;
      break;
    }
  }
  if (!duplicate) {
    bbs->push_back(toInsert);
  }
}

std::vector<struct SCC> getTopologicalSort(Function *func) {

  std::vector<struct SCC> topological_scc_order;
  // Use LLVM's Strongly Connected Components (SCCs) iterator to produce
  // a reverse topological sort of SCCs.
  for (scc_iterator<Function *> I = scc_begin(func), IE = scc_end(func);
       I != IE; ++I) {

    struct SCC curr_scc = *((struct SCC *)new struct SCC);

    // Obtain the vector of BBs in this SCC and print it out.
    const std::vector<BasicBlock *> &SCCBBs = *I;
    for (std::vector<BasicBlock *>::const_iterator BBI = SCCBBs.begin(),
                                                   BBIE = SCCBBs.end();
         BBI != BBIE; ++BBI) {
      curr_scc.components.push_back(*BBI);
    }

    topological_scc_order.insert(topological_scc_order.begin(), curr_scc);
  }

  return topological_scc_order;
}

void computeStoreSets(BasicBlock *bb) {

  struct store_sets *curr_ss;
  BasicBlock *curr_bb = bb;
  if (store_sets_map.find(curr_bb->getName()) != store_sets_map.end()) {
    curr_ss = store_sets_map.find(curr_bb->getName())->second;
  } else {
    errs() << "buildStoreSetsMap error: can't find bb\n";
  }

  // Clear the previous computed store sets
  curr_ss->in.clear();
  curr_ss->out.clear();

  // Add each bb's parents out set to current in set
  for (pred_iterator pred_it = pred_begin(curr_bb);
       pred_it != pred_end(curr_bb); ++pred_it) {
    if (store_sets_map.find((*pred_it)->getName()) != store_sets_map.end()) {

      struct store_sets *parent_ss;
      parent_ss = store_sets_map.find((*pred_it)->getName())->second;

      // Calculate the current set store by unioning it with
      // all its parents
      curr_ss->in = storeSetUnion(curr_ss->in, parent_ss->out);
    } else {
      errs() << "buildStoreSetsMap error: can't find bb's parent\n";
    }
  }
  // Add all stores in the BB to the out set
  for (BasicBlock::iterator inst = curr_bb->begin(); inst != curr_bb->end();
       ++inst) {
    if (StoreInst *si = dyn_cast<StoreInst>(&*inst)) {
      if (si->getOperand(1)->getName().str() != "") {
        BBStoreInsert(&(curr_ss->out), si);
      }
    }
  }

  // Add all the stores from the inset (that dont get killed) to the out set
  bool var_conflicts;
  std::vector<StoreInst *> will_add;

  // For each store in the in set
  for (int j = 0; j < curr_ss->in.size(); j++) {
    var_conflicts = false;
    // For each store in the out set
    for (int k = 0; k < curr_ss->out.size(); k++) {

      std::string in_var_name;
      in_var_name = curr_ss->in[j]->getOperand(1)->getName().str();
      std::string out_var_name;
      out_var_name = curr_ss->out[k]->getOperand(1)->getName().str();

      // If the variable being stored to in the two different store instructions
      // is the same the store from the in set is killed
      if (in_var_name == out_var_name) {
        var_conflicts = true;
        break;
      }
    }
    // If the store from the inset is not killed
    if (!var_conflicts) {
      // Add the bb to the out set
      will_add.push_back(curr_ss->in[j]);
    }
  }

  // Update the out set
  curr_ss->out.insert(curr_ss->out.end(), will_add.begin(), will_add.end());
}

void buildStoreSetsMap() {
  for (Module::iterator func = mod_ptr->begin(), func_e = mod_ptr->end();
       func != func_e; ++func) {
    if (func->isDeclaration() == false) {

      // Get the function's SCCs in a topological sort
      std::vector<struct SCC> topological_scc_order;
      topological_scc_order = getTopologicalSort(&*func);

      // Initialize the entrys for each basic block
      initStoreSetsMap(topological_scc_order);

      // Iterate through in topological order
      for (int i = 0; i < topological_scc_order.size(); i++) {

        // If the SCC is just 1 BB
        if (topological_scc_order[i].components.size() == 1) {
          computeStoreSets(topological_scc_order[i].components[0]);
        }
        // If the SCC has more than 1 BB (loop)
        else {
          std::vector<BasicBlock *> scc_queue;
          BasicBlock *curr_bb;
          struct store_sets *curr_ss;
          int out_size;

          // Insert the first BB of the SCC into the queue
          SCCQueueInsert(&scc_queue, topological_scc_order[i].components[0]);

          // While the queue is not empty
          while (scc_queue.size() != 0) {

            // Pop the front of the queue
            curr_bb = scc_queue[0];
            scc_queue.erase(scc_queue.begin());

            // Find the current BB's store set
            if (store_sets_map.find(curr_bb->getName()) !=
                store_sets_map.end()) {
              curr_ss = store_sets_map.find(curr_bb->getName())->second;
            } else {
              errs() << "buildStoreSetsMap error: can't find bb\n";
            }

            // Get the size of the bb's out set before computation
            out_size = curr_ss->out.size();

            // Compute the most recent store sets
            computeStoreSets(curr_bb);

            // Compare the size of the out set to the original size to
            // see if the update resulted in a change
            if (curr_ss->out.size() != out_size) {
              // Add each successor to the queue as their sets need to be
              // computed or re-computed
              for (succ_iterator succ_it = succ_begin(curr_bb);
                   succ_it != succ_end(curr_bb); ++succ_it) {
                SCCQueueInsert(&scc_queue, *succ_it);
              }
            }
          }
        }
      }
    }
  }
}

void handleVarConds(std::vector<struct var_condition> var_cons) {

  AllocaInst *curr_ai;
  LoadInst *curr_li;

  // For each variable conditional found during previous analysis
  for (int i = 0; i < var_cons.size(); i++) {


    // Get the cmp instruction and reaching stores for the var_condition
    CmpInst *curr_cmp = var_cons[i].ci;
	curr_cmp->getParent()->dump();
    std::vector<StoreInst *> reaching_stores = var_cons[i].reaching_stores;

    // Get the operator and constant int value
    CmpInst::Predicate op = getOperator(curr_cmp);
    int val = getValue(curr_cmp);

    // Create the per-cmp variable and it's corresponding load for use in
    // the conditional
    curr_ai = new AllocaInst(
        curr_cmp->getType(), "test_var",
        curr_cmp->getParent()->getParent()->getEntryBlock().begin());
    curr_li = new LoadInst(curr_ai, "new_load", curr_cmp);

    std::vector<std::pair<int, int> > ranges;
    // For each store that reaches
    for (int j = 0; j < reaching_stores.size(); j++) {

      // Get the instruction that corresponds to the index of the array
      // read
      Instruction *idx_val = getIndex(reaching_stores[j]);

      // If the store was an array read
      if (idx_val != NULL) {
	      errs() << "idx_val is not null\n";

              LoadInst *li_2;
	      std::string array_name;

              // Get the instruction that is being stored into the variable
              if (isa<LoadInst>(reaching_stores[j]->getOperand(0))) {
                li_2 = dyn_cast<LoadInst>(reaching_stores[j]->getOperand(0));
              } else if (SExtInst *sei = dyn_cast<SExtInst>(
                             reaching_stores[j]->getOperand(0))) {
                if (LoadInst *li_3 = dyn_cast<LoadInst>(sei->getOperand(0))) {
                  li_2 = li_3;
                }
              } else {

	        errs() << "REACHING STORE DOES NOT ACCESS ARRAY!\n";
	        reaching_stores[j]->getOperand(0)->dump();
	      }
              if (GetElementPtrInst *gep =
                      dyn_cast<GetElementPtrInst>(li_2->getOperand(0))) {
	        array_name = gep->getOperand(0)->getName().str();
	      }
	      
        // Get the indexes and corresponding ranges to rewrite the conditional
        std::vector<bool> indexes =
            computeValidIndexes(reaching_stores[j], array_name, op, val);
        ranges = computeRanges(indexes);
        rewriteVarCondition(curr_cmp, curr_ai, reaching_stores[j], idx_val,
                            ranges);
      } else {
	      errs() << "idx_val is null\n";
        // If the reaching store is not an array access
        rewriteVarCondition(curr_cmp, curr_ai, reaching_stores[j], NULL,
                            ranges);
      }
    }

    // Replace the original conditonal with the load of
    // the corresponding variable
    curr_cmp->replaceAllUsesWith(curr_li);
  }
}

namespace {
// Hello2 - The second implementation with getAnalysisUsage implemented.
struct Hello2 : public ModulePass {
  static char ID; // Pass identification, replacement for typeid
  Hello2() : ModulePass(ID) {}

  bool runOnModule(Module &m) override {
    mod_ptr = &m;

    nameBBs();
    buildStoreSetsMap();
    buildArrayMap();

    std::vector<struct var_condition> var_cons;
    var_cons = getArrayVarConditions(input_array);
    handleVarConds(var_cons);

    errs() << var_cons.size() << "\n";

    std::vector<Instruction *> conditions = getArrayConditions(input_array);
    errs() << conditions.size() << "\n";
    for (int i = 0; i < conditions.size(); i++) {

      CmpInst::Predicate op = getOperator(conditions[i]);
      int val = getValue(conditions[i]);
      Instruction *idx_val = getIndex(conditions[i]);

      errs() << "OPT: " << op << "\n";
      errs() << "VAL: " << val << "\n";
      errs() << "IDX:";
      idx_val->dump();

      std::string array_name;

      if(LoadInst *li = dyn_cast<LoadInst>(conditions[i]->getOperand(0))) {
	      if(GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(li->getOperand(0))) {
	      	array_name = gep->getOperand(0)->getName().str();
	      }
	      
      }
      else if(LoadInst *li = dyn_cast<LoadInst>(conditions[i]->getOperand(1))) {
	      if(GetElementPtrInst *gep = dyn_cast<GetElementPtrInst>(li->getOperand(0))) {
	      	array_name = gep->getOperand(0)->getName().str();
	      }
      }

      std::vector<bool> indexMask =
          computeValidIndexes(conditions[i], array_name, op, val);
      debugPrintValidIndexesMask(indexMask);
      std::vector<std::pair<int, int> > ranges = computeRanges(indexMask);
      
      debugPrintRanges(ranges);

      rewriteCondition(conditions[i], idx_val, ranges);
    }

    return true;
  }

  // We don't modify the program, so we preserve all analyses.
  void getAnalysisUsage(AnalysisUsage &AU) const override {
    // AU.setPreservesAll();
  }
};
}

char Hello2::ID = 0;
static RegisterPass<Hello2>
Y("hello2", "Hello World Pass (with getAnalysisUsage implemented)");
