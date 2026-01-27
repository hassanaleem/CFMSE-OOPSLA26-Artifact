/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 18 "language.y" /* yacc.c:339  */

#include "config.h"
#include "array.h"
#include "system.h"
#include "memory.h"
#include "number.h"
#include "string.h"
#include "head.h"
#include "value.h"
#include "tuple.h"
#include "expression.h"
#include "summary.h"
#include "variable.h"
#include "relation.h"

#include "language.h"
#include "environment.h"

/* TODO: make line numbers reported in yyerror more accurate, especially
         for p_convert() which are currently called on
         function reduction */
extern void yyerror(const char *, ...);
extern int yylex();

static int gposition = 0;
static int gfunc_ret = 0;
static int gseq = 0;
static Func *gfunc = NULL;
static Env *genv = NULL;

static L_Attrs attr_empty();
static L_Attrs attr_name(const char *name);
static L_Attrs attr_decl(L_Attrs attrs, Type type);
static L_Attrs attr_rename(const char *from, const char *to);
static L_Attrs attr_extend(const char *name, L_Expr *e);
static L_Attrs attr_sum(const char *name, L_Sum sum);
static L_Attrs attr_merge(L_Attrs l, L_Attrs r);
static L_Attrs attr_arg(Rel *rexpr, L_Expr *pexpr);
static void attr_free(L_Attrs attrs);

static Head *rel_head(L_Attrs attrs);
static Head *inline_rel(const char *name, Head *head);

static Rel *r_load(const char *name);
static Rel *r_project(Rel *r, L_Attrs attrs);
static Rel *r_rename(Rel *r, L_Attrs attrs);
static Rel *r_select(Rel *r, L_Expr *expr);
static Rel *r_extend(Rel *r, L_Attrs attrs);
static Rel *r_sum(Rel *l, Rel *r, L_Attrs attrs);
static Rel *r_join(Rel *l, Rel *r);
static Rel *r_union(Rel *l, Rel *r);
static Rel *r_diff(Rel *l, Rel *r);
static Rel *r_call(const char *func, L_Attrs args);

static L_Expr *p_attr(const char *name);
static L_Expr *p_value(L_Value val, Type t);
static L_Expr *p_op(L_Expr *l, L_Expr *r, L_Expr_Type node_type);
static L_Expr *p_func(const char *pkg, const char *name, L_Expr *l, L_Expr *r);
static void p_free(L_Expr *e);
static int is_constant(L_Expr *e);

static void stmt_assign(const char *var, Rel *r);
static void stmt_temp(const char *var, Rel *r);
static void stmt_call(Rel *r);
static void stmt_return(Rel *r);

static L_Sum sum_create(const char *func, const char *attr, L_Expr *def);

static void add_head(const char *name, Head *head);
static void add_relvar(const char *rel, L_Attrs vars);
static void add_relvar_inline(Head *head, L_Attrs vars);

static void fn_start(const char *name);
static void fn_rel_params(L_Attrs names, Head *h);
static void fn_prim_params(L_Attrs attrs);
static void fn_result(Head *h);
static void fn_add();

#line 145 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TK_TYPE = 258,
    TK_VAR = 259,
    TK_FN = 260,
    TK_RETURN = 261,
    TK_INT = 262,
    TK_LONG = 263,
    TK_REAL = 264,
    TK_STRING = 265,
    TK_TIME = 266,
    TK_VOID = 267,
    TK_PROJECT = 268,
    TK_RENAME = 269,
    TK_SELECT = 270,
    TK_EXTEND = 271,
    TK_SUMMARY = 272,
    TK_JOIN = 273,
    TK_UNION = 274,
    TK_MINUS = 275,
    TK_EQ = 276,
    TK_NEQ = 277,
    TK_AND = 278,
    TK_OR = 279,
    TK_LTE = 280,
    TK_GTE = 281,
    TK_NAME = 282,
    TK_INT_VAL = 283,
    TK_LONG_VAL = 284,
    TK_REAL_VAL = 285,
    TK_STRING_VAL = 286
  };
#endif
/* Tokens.  */
#define TK_TYPE 258
#define TK_VAR 259
#define TK_FN 260
#define TK_RETURN 261
#define TK_INT 262
#define TK_LONG 263
#define TK_REAL 264
#define TK_STRING 265
#define TK_TIME 266
#define TK_VOID 267
#define TK_PROJECT 268
#define TK_RENAME 269
#define TK_SELECT 270
#define TK_EXTEND 271
#define TK_SUMMARY 272
#define TK_JOIN 273
#define TK_UNION 274
#define TK_MINUS 275
#define TK_EQ 276
#define TK_NEQ 277
#define TK_AND 278
#define TK_OR 279
#define TK_LTE 280
#define TK_GTE 281
#define TK_NAME 282
#define TK_INT_VAL 283
#define TK_LONG_VAL 284
#define TK_REAL_VAL 285
#define TK_STRING_VAL 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 97 "language.y" /* yacc.c:355  */

    char name[MAX_NAME];
    Head *head;

    L_Value val;
    L_Expr *expr;
    L_Attrs attrs;
    L_Sum sum;
    Rel *rel;

#line 258 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 273 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   286

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  122
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  234

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   286

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    43,     2,     2,     2,     2,     2,     2,
      36,    37,    41,    39,    34,    40,    42,    44,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    35,
      46,    38,    45,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   134,   134,   135,   136,   137,   141,   145,   146,   150,
     151,   155,   156,   160,   161,   162,   163,   167,   168,   172,
     177,   181,   182,   183,   187,   188,   189,   193,   195,   197,
     202,   203,   204,   205,   209,   210,   211,   212,   216,   220,
     221,   225,   227,   229,   231,   233,   238,   242,   246,   247,
     251,   253,   257,   258,   262,   264,   266,   268,   270,   272,
     274,   276,   278,   280,   282,   287,   288,   292,   293,   294,
     298,   299,   300,   304,   308,   309,   310,   314,   318,   319,
     320,   324,   328,   329,   330,   334,   338,   340,   342,   348,
     349,   350,   351,   355,   356,   357,   358,   359,   360,   362,
     367,   368,   369,   373,   374,   375,   376,   380,   381,   382,
     386,   387,   388,   392,   393,   394,   395,   396,   397,   398,
     402,   403,   404
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TK_TYPE", "TK_VAR", "TK_FN",
  "TK_RETURN", "TK_INT", "TK_LONG", "TK_REAL", "TK_STRING", "TK_TIME",
  "TK_VOID", "TK_PROJECT", "TK_RENAME", "TK_SELECT", "TK_EXTEND",
  "TK_SUMMARY", "TK_JOIN", "TK_UNION", "TK_MINUS", "TK_EQ", "TK_NEQ",
  "TK_AND", "TK_OR", "TK_LTE", "TK_GTE", "TK_NAME", "TK_INT_VAL",
  "TK_LONG_VAL", "TK_REAL_VAL", "TK_STRING_VAL", "'{'", "'}'", "','",
  "';'", "'('", "')'", "'='", "'+'", "'-'", "'*'", "'.'", "'!'", "'/'",
  "'>'", "'<'", "$accept", "program", "type_decl", "rel_head", "rel_attrs",
  "attr_names", "rel_attr", "relvar_decl", "func_decl", "func_name",
  "func_res", "func_params", "func_param", "func_body", "stmt_call_assign",
  "stmt_return", "stmt_call", "stmt_assign", "func_no_args",
  "func_with_args", "func_args", "func_arg", "rel_prim_expr",
  "rel_simple_expr", "rel_mul_expr", "rel_expr", "project_attrs",
  "project_attr", "rename_attrs", "rename_attr", "extend_attrs",
  "extend_attr", "sum_attrs", "sum_attr", "sum_func", "prim_const_expr",
  "prim_simple_expr", "prim_top_expr", "prim_unary_expr", "prim_mul_expr",
  "prim_add_expr", "prim_bool_cmp_expr", "prim_expr", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   123,   125,    44,    59,    40,    41,    61,    43,
      45,    42,    46,    33,    47,    62,    60
};
# endif

#define YYPACT_NINF -144

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-144)))

#define YYTABLE_NINF -29

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -144,   195,  -144,   -17,    -9,     5,  -144,  -144,  -144,    10,
    -144,   193,  -144,    30,    -9,  -144,    47,    85,    -9,   206,
      88,  -144,  -144,  -144,    53,  -144,    22,  -144,  -144,    74,
    -144,  -144,  -144,  -144,  -144,    84,  -144,    -9,    72,  -144,
    -144,  -144,  -144,  -144,  -144,   111,    67,   105,    73,   100,
     130,    67,  -144,  -144,  -144,   161,   169,   148,    31,    81,
      83,   128,   138,   149,   149,   149,   131,    73,  -144,  -144,
    -144,  -144,   112,   162,  -144,  -144,  -144,  -144,  -144,    73,
     174,   214,   215,   131,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,    73,  -144,    31,    21,  -144,   216,    81,
     108,  -144,   164,     0,   152,   152,    83,  -144,  -144,  -144,
    -144,   187,    66,    24,   110,   217,   128,   118,  -144,   218,
     138,   139,  -144,   149,   149,   149,   190,    73,  -144,    73,
      73,   168,    73,    73,    73,  -144,   170,   198,   230,  -144,
     231,   199,   232,  -144,   233,   141,   141,   141,   172,    -2,
    -144,  -144,  -144,    83,    83,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,  -144,    83,   200,   234,  -144,
     151,   204,   235,   149,  -144,  -144,  -144,  -144,  -144,   112,
     112,  -144,   176,   178,   184,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,   185,   226,   227,   238,  -144,  -144,  -144,   187,
     187,    66,    66,    66,    66,    66,    66,    24,    24,   219,
    -144,  -144,  -144,   239,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,   141,   -14,   120,    83,  -144,  -144,
     236,    79,  -144,  -144
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,     0,     1,     0,     0,     0,     2,     3,     4,     0,
      11,     0,    20,     0,     0,     6,    12,     0,    26,     0,
       0,     9,    17,    18,     0,    27,     0,    24,     7,     0,
      13,    14,    15,    16,    12,    12,    29,     0,     0,     8,
      10,    25,    21,    22,    23,     0,    33,     0,     0,    46,
       0,    31,    30,    35,    34,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    46,     0,    52,    64,
      54,    65,    67,     0,    46,    89,    90,    91,    92,     0,
       0,     0,     0,    47,    48,    50,    51,    19,    32,    36,
      37,    39,    40,     0,    73,     0,     0,    70,     0,     0,
       0,    74,   101,     0,     0,     0,     0,    93,   100,   103,
     107,   110,   113,   120,     0,     0,     0,     0,    78,     0,
       0,     0,    82,     0,     0,     0,     0,     0,    38,     0,
       0,     0,     0,     0,     0,    49,     0,     0,     0,    57,
       0,     0,     0,    58,     0,     0,     0,     0,   101,     0,
     106,   105,   104,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    55,     0,     0,     0,    56,
       0,     0,     0,    62,    59,    60,    61,    53,    66,    68,
      69,    41,     0,     0,     0,    45,    72,    71,    77,    76,
      75,   102,     0,     0,     0,     0,    94,   108,   109,   111,
     112,   114,   115,   118,   119,   116,   117,   121,   122,    81,
      80,    79,    86,     0,    85,    84,    83,    63,    42,    43,
      44,    95,    97,    96,   102,     0,     0,     0,    87,    98,
       0,     0,    99,    88
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,  -144,    -5,  -144,     7,    12,  -144,  -144,  -144,
    -144,  -144,   237,  -144,  -144,   220,   221,   224,   133,   175,
    -144,   186,   -49,   140,   115,   -55,   173,   132,   177,   135,
     163,   113,   158,   114,  -144,   -29,   142,  -143,  -101,    93,
      32,    87,  -102
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     6,    15,    19,    20,    25,     7,     8,    13,
      45,    26,    27,    50,    51,    52,    53,    54,    68,    69,
      83,    84,    70,    71,    72,    73,    96,    97,   100,   101,
     117,   118,   121,   122,   214,   107,   108,   109,   110,   111,
     112,   113,   114
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      85,   149,   192,   193,   194,   152,    17,   145,   146,   147,
       9,    11,   126,   227,   123,   124,   125,    85,    10,    36,
      86,   163,   164,   228,   131,    24,    21,   148,    75,    76,
      77,    78,    12,    44,    85,   196,   103,    86,   136,   104,
     105,    40,    14,   106,    24,   157,   158,   139,    74,   159,
     160,   143,   197,   198,    86,   138,    37,    67,    94,    38,
      30,    31,    32,    33,   209,   165,    18,    95,   169,   161,
     162,    47,   173,    48,   174,   175,   176,   182,   183,   184,
      35,   226,    22,   230,    42,    14,    58,    59,    60,    61,
      62,    63,    64,    65,    49,    30,    31,    32,    33,    43,
      66,    10,   163,   164,    14,   155,   156,    39,    98,    67,
     102,    75,    76,    77,    78,    34,   233,    99,   -28,   103,
      23,   -28,   104,   105,   217,   231,   106,    74,    75,    76,
      77,    78,    57,   163,   164,    74,    67,    74,    79,    80,
      81,    82,   142,    46,    67,    74,    67,   102,    75,    76,
      77,    78,   168,   127,    67,   115,   103,   229,    74,    75,
      76,    77,    78,    87,   116,   119,    74,    67,   102,    75,
      76,    77,    78,   172,   120,    67,    74,   103,   212,    55,
      75,    76,    77,    78,    55,    67,    93,   213,   103,   201,
     202,   203,   204,   205,   206,     2,    91,   128,     3,     4,
       5,   129,   130,   181,    92,   185,   144,   129,   130,   129,
     130,   218,   132,   219,   195,   129,   130,   129,   130,   220,
      16,    56,   221,   129,   130,    14,    56,   177,   153,   129,
     130,   154,   138,   142,   168,   186,   189,   210,   172,    28,
      29,   215,   163,   164,   179,   180,   150,   151,   199,   200,
     207,   208,   133,   134,   140,   166,   170,    94,   188,    98,
     191,   115,   119,   222,   223,   224,   225,   178,   137,   135,
     187,    88,    89,   232,    41,    90,   141,   190,   171,   167,
       0,   211,     0,     0,     0,     0,   216
};

static const yytype_int16 yycheck[] =
{
      49,   103,   145,   146,   147,   106,    11,     7,     8,     9,
      27,     4,    67,    27,    63,    64,    65,    66,    27,    24,
      49,    23,    24,    37,    79,    18,    14,    27,    28,    29,
      30,    31,    27,    38,    83,    37,    36,    66,    93,    39,
      40,    29,    32,    43,    37,    21,    22,    96,    27,    25,
      26,   100,   153,   154,    83,    34,    34,    36,    27,    37,
       7,     8,     9,    10,   166,   114,    36,    36,   117,    45,
      46,     4,   121,     6,   123,   124,   125,   132,   133,   134,
      27,   224,    35,   226,    12,    32,    13,    14,    15,    16,
      17,    18,    19,    20,    27,     7,     8,     9,    10,    27,
      27,    27,    23,    24,    32,    39,    40,    33,    27,    36,
      27,    28,    29,    30,    31,    27,    37,    36,    34,    36,
      35,    37,    39,    40,   173,   227,    43,    27,    28,    29,
      30,    31,    27,    23,    24,    27,    36,    27,    38,    39,
      40,    41,    34,    32,    36,    27,    36,    27,    28,    29,
      30,    31,    34,    41,    36,    27,    36,    37,    27,    28,
      29,    30,    31,    33,    36,    27,    27,    36,    27,    28,
      29,    30,    31,    34,    36,    36,    27,    36,    27,    46,
      28,    29,    30,    31,    51,    36,    38,    36,    36,   157,
     158,   159,   160,   161,   162,     0,    35,    35,     3,     4,
       5,    39,    40,    35,    35,    35,    42,    39,    40,    39,
      40,    35,    38,    35,    42,    39,    40,    39,    40,    35,
      27,    46,    37,    39,    40,    32,    51,    37,    41,    39,
      40,    44,    34,    34,    34,    37,    37,    37,    34,    33,
      34,    37,    23,    24,   129,   130,   104,   105,   155,   156,
     163,   164,    38,    38,    38,    38,    38,    27,    27,    27,
      27,    27,    27,    37,    37,    27,    27,   127,    95,    83,
     138,    51,    51,    37,    37,    51,    99,   142,   120,   116,
      -1,   168,    -1,    -1,    -1,    -1,   172
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    48,     0,     3,     4,     5,    49,    54,    55,    27,
      27,    52,    27,    56,    32,    50,    27,    50,    36,    51,
      52,    53,    35,    35,    52,    53,    58,    59,    33,    34,
       7,     8,     9,    10,    27,    27,    50,    34,    37,    33,
      53,    59,    12,    27,    50,    57,    32,     4,     6,    27,
      60,    61,    62,    63,    64,    65,    66,    27,    13,    14,
      15,    16,    17,    18,    19,    20,    27,    36,    65,    66,
      69,    70,    71,    72,    27,    28,    29,    30,    31,    38,
      39,    40,    41,    67,    68,    69,    82,    33,    62,    63,
      64,    35,    35,    38,    27,    36,    73,    74,    27,    36,
      75,    76,    27,    36,    39,    40,    43,    82,    83,    84,
      85,    86,    87,    88,    89,    27,    36,    77,    78,    27,
      36,    79,    80,    69,    69,    69,    72,    41,    35,    39,
      40,    72,    38,    38,    38,    68,    72,    73,    34,    69,
      38,    75,    34,    69,    42,     7,     8,     9,    27,    89,
      83,    83,    85,    41,    44,    39,    40,    21,    22,    25,
      26,    45,    46,    23,    24,    69,    38,    77,    34,    69,
      38,    79,    34,    69,    69,    69,    69,    37,    70,    71,
      71,    35,    72,    72,    72,    35,    37,    74,    27,    37,
      76,    27,    84,    84,    84,    42,    37,    85,    85,    86,
      86,    87,    87,    87,    87,    87,    87,    88,    88,    89,
      37,    78,    27,    36,    81,    37,    80,    69,    35,    35,
      35,    37,    37,    37,    27,    27,    84,    27,    37,    37,
      84,    89,    37,    37
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    47,    48,    48,    48,    48,    49,    50,    50,    51,
      51,    52,    52,    53,    53,    53,    53,    54,    54,    55,
      56,    57,    57,    57,    58,    58,    58,    59,    59,    59,
      60,    60,    60,    60,    61,    61,    61,    61,    62,    63,
      63,    64,    64,    64,    64,    64,    65,    66,    67,    67,
      68,    68,    69,    69,    70,    70,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    71,    71,    72,    72,    72,
      73,    73,    73,    74,    75,    75,    75,    76,    77,    77,
      77,    78,    79,    79,    79,    80,    81,    81,    81,    82,
      82,    82,    82,    83,    83,    83,    83,    83,    83,    83,
      84,    84,    84,    85,    85,    85,    85,    86,    86,    86,
      87,    87,    87,    88,    88,    88,    88,    88,    88,    88,
      89,    89,    89
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     2,     0,     3,     3,     4,     1,
       3,     1,     2,     2,     2,     2,     2,     4,     4,     9,
       1,     1,     1,     1,     1,     3,     0,     1,     2,     2,
       1,     1,     2,     0,     1,     1,     2,     2,     3,     2,
       2,     4,     5,     5,     5,     5,     1,     2,     1,     2,
       1,     1,     1,     3,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     4,     1,     1,     3,     1,     3,     3,
       1,     3,     3,     1,     1,     3,     3,     3,     1,     3,
       3,     3,     1,     3,     3,     3,     1,     3,     5,     1,
       1,     1,     1,     1,     3,     4,     4,     4,     6,     7,
       1,     1,     3,     1,     2,     2,     2,     1,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 6:
#line 141 "language.y" /* yacc.c:1646  */
    { add_head((yyvsp[-1].name), (yyvsp[0].head)); }
#line 1529 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 145 "language.y" /* yacc.c:1646  */
    { (yyval.head) = rel_head((yyvsp[-1].attrs)); }
#line 1535 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 146 "language.y" /* yacc.c:1646  */
    { (yyval.head) = rel_head((yyvsp[-2].attrs)); }
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 150 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = (yyvsp[0].attrs); }
#line 1547 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 151 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_merge((yyvsp[-2].attrs), (yyvsp[0].attrs));}
#line 1553 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 155 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_name((yyvsp[0].name)); }
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 156 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_merge((yyvsp[-1].attrs), attr_name((yyvsp[0].name))); }
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 160 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_decl((yyvsp[-1].attrs), Int); }
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 161 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_decl((yyvsp[-1].attrs), Long); }
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 162 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_decl((yyvsp[-1].attrs), Real); }
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 163 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_decl((yyvsp[-1].attrs), String); }
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 167 "language.y" /* yacc.c:1646  */
    { add_relvar((yyvsp[-1].name), (yyvsp[-2].attrs)); }
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 168 "language.y" /* yacc.c:1646  */
    { add_relvar_inline((yyvsp[-1].head), (yyvsp[-2].attrs)); }
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 173 "language.y" /* yacc.c:1646  */
    { fn_add(); }
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 177 "language.y" /* yacc.c:1646  */
    { fn_start((yyvsp[0].name)); }
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 181 "language.y" /* yacc.c:1646  */
    { fn_result(inline_rel(NULL, NULL)); }
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 182 "language.y" /* yacc.c:1646  */
    { fn_result(inline_rel((yyvsp[0].name), NULL)); }
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 183 "language.y" /* yacc.c:1646  */
    { fn_result(inline_rel(NULL, (yyvsp[0].head))); }
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 194 "language.y" /* yacc.c:1646  */
    { fn_prim_params((yyvsp[0].attrs)); }
#line 1637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 196 "language.y" /* yacc.c:1646  */
    { fn_rel_params((yyvsp[-1].attrs), inline_rel((yyvsp[0].name), NULL)); }
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 198 "language.y" /* yacc.c:1646  */
    { fn_rel_params((yyvsp[-1].attrs), inline_rel(NULL, (yyvsp[0].head))); }
#line 1649 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 216 "language.y" /* yacc.c:1646  */
    { stmt_return((yyvsp[-1].rel)); }
#line 1655 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 220 "language.y" /* yacc.c:1646  */
    { stmt_call((yyvsp[-1].rel)); }
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 221 "language.y" /* yacc.c:1646  */
    { stmt_call((yyvsp[-1].rel)); }
#line 1667 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 226 "language.y" /* yacc.c:1646  */
    { stmt_assign((yyvsp[-3].name), (yyvsp[-1].rel)); }
#line 1673 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 228 "language.y" /* yacc.c:1646  */
    { stmt_assign((yyvsp[-4].name), r_union(r_load((yyvsp[-4].name)), (yyvsp[-1].rel))); }
#line 1679 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 230 "language.y" /* yacc.c:1646  */
    { stmt_assign((yyvsp[-4].name), r_diff(r_load((yyvsp[-4].name)), (yyvsp[-1].rel))); }
#line 1685 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 232 "language.y" /* yacc.c:1646  */
    { stmt_assign((yyvsp[-4].name), r_join(r_load((yyvsp[-4].name)), (yyvsp[-1].rel))); }
#line 1691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 234 "language.y" /* yacc.c:1646  */
    { stmt_temp((yyvsp[-3].name), (yyvsp[-1].rel)); }
#line 1697 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 238 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_call((yyvsp[0].name), attr_empty()); }
#line 1703 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 242 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_call((yyvsp[-1].name), (yyvsp[0].attrs)); }
#line 1709 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 246 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = (yyvsp[0].attrs); }
#line 1715 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 247 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_merge((yyvsp[-1].attrs), (yyvsp[0].attrs)); }
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 251 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_arg((yyvsp[0].rel), NULL); }
#line 1727 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 253 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_arg(NULL, (yyvsp[0].expr)); }
#line 1733 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 257 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = (yyvsp[0].rel); }
#line 1739 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 258 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = (yyvsp[-1].rel); }
#line 1745 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 263 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = (yyvsp[0].rel); }
#line 1751 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 265 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_select((yyvsp[0].rel), (yyvsp[-1].expr)); }
#line 1757 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 267 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_extend((yyvsp[0].rel), (yyvsp[-1].attrs)); }
#line 1763 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 269 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_project((yyvsp[0].rel), (yyvsp[-1].attrs)); }
#line 1769 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 271 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_rename((yyvsp[0].rel), (yyvsp[-1].attrs)); }
#line 1775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 273 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_join((yyvsp[-1].rel), (yyvsp[0].rel)); }
#line 1781 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 275 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_union((yyvsp[-1].rel), (yyvsp[0].rel)); }
#line 1787 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 277 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_diff((yyvsp[-1].rel), (yyvsp[0].rel)); }
#line 1793 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 279 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_sum((yyvsp[0].rel), NULL, (yyvsp[-1].attrs)); }
#line 1799 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 281 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_sum((yyvsp[-1].rel), (yyvsp[0].rel), (yyvsp[-2].attrs)); }
#line 1805 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 283 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = (yyvsp[0].rel); }
#line 1811 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 287 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = (yyvsp[0].rel); }
#line 1817 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 288 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_join((yyvsp[-2].rel), (yyvsp[0].rel)); }
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 292 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = (yyvsp[0].rel); }
#line 1829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 293 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_union((yyvsp[-2].rel), (yyvsp[0].rel)); }
#line 1835 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 294 "language.y" /* yacc.c:1646  */
    { (yyval.rel) = r_diff((yyvsp[-2].rel), (yyvsp[0].rel)); }
#line 1841 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 298 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = (yyvsp[0].attrs); }
#line 1847 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 299 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_merge((yyvsp[-2].attrs), (yyvsp[0].attrs)); }
#line 1853 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 300 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = (yyvsp[-1].attrs); }
#line 1859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 304 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_name((yyvsp[0].name)); }
#line 1865 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 308 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = (yyvsp[0].attrs); }
#line 1871 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 309 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_merge((yyvsp[-2].attrs), (yyvsp[0].attrs)); }
#line 1877 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 310 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = (yyvsp[-1].attrs); }
#line 1883 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 314 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_rename((yyvsp[0].name), (yyvsp[-2].name)); }
#line 1889 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 318 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = (yyvsp[0].attrs); }
#line 1895 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 319 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_merge((yyvsp[-2].attrs), (yyvsp[0].attrs)); }
#line 1901 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 320 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = (yyvsp[-1].attrs); }
#line 1907 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 324 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_extend((yyvsp[-2].name), (yyvsp[0].expr)); }
#line 1913 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 328 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = (yyvsp[0].attrs); }
#line 1919 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 329 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_merge((yyvsp[-2].attrs), (yyvsp[0].attrs)); }
#line 1925 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 330 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = (yyvsp[-1].attrs); }
#line 1931 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 334 "language.y" /* yacc.c:1646  */
    { (yyval.attrs) = attr_sum((yyvsp[-2].name), (yyvsp[0].sum)); }
#line 1937 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 339 "language.y" /* yacc.c:1646  */
    { (yyval.sum) = sum_create((yyvsp[0].name), "", NULL); }
#line 1943 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 341 "language.y" /* yacc.c:1646  */
    { (yyval.sum) = sum_create((yyvsp[-1].name), "", NULL); }
#line 1949 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 343 "language.y" /* yacc.c:1646  */
    { (yyval.sum) = sum_create((yyvsp[-3].name), (yyvsp[-2].name), (yyvsp[-1].expr)); }
#line 1955 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 348 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_value((yyvsp[0].val), Int); }
#line 1961 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 349 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_value((yyvsp[0].val), Long); }
#line 1967 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 350 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_value((yyvsp[0].val), Real); }
#line 1973 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 351 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_value((yyvsp[0].val), String); }
#line 1979 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 355 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 1985 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 356 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 1991 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 357 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_func("", "int", (yyvsp[-1].expr), NULL); }
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 358 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_func("", "real", (yyvsp[-1].expr), NULL); }
#line 2003 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 359 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_func("", "long", (yyvsp[-1].expr), NULL); }
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 361 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_func((yyvsp[-4].name), (yyvsp[-2].name), (yyvsp[-1].expr), NULL); }
#line 2015 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 363 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_func((yyvsp[-5].name), (yyvsp[-3].name), (yyvsp[-2].expr), (yyvsp[-1].expr)); }
#line 2021 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 367 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 368 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_attr((yyvsp[0].name)); }
#line 2033 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 369 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_func((yyvsp[-2].name), (yyvsp[0].name), NULL, NULL); }
#line 2039 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 373 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2045 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 374 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[0].expr), NULL, NOT); }
#line 2051 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 375 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[0].expr), NULL, NEG); }
#line 2057 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 376 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2063 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 380 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2069 "y.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 381 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), MUL); }
#line 2075 "y.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 382 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), DIV); }
#line 2081 "y.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 386 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2087 "y.tab.c" /* yacc.c:1646  */
    break;

  case 111:
#line 387 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), SUM); }
#line 2093 "y.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 388 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), SUB); }
#line 2099 "y.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 392 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2105 "y.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 393 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), EQ); }
#line 2111 "y.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 394 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), NEQ); }
#line 2117 "y.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 395 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), GT); }
#line 2123 "y.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 396 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), LT); }
#line 2129 "y.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 397 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), LTE); }
#line 2135 "y.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 398 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), GTE); }
#line 2141 "y.tab.c" /* yacc.c:1646  */
    break;

  case 120:
#line 402 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2147 "y.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 403 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), AND); }
#line 2153 "y.tab.c" /* yacc.c:1646  */
    break;

  case 122:
#line 404 "language.y" /* yacc.c:1646  */
    { (yyval.expr) = p_op((yyvsp[-2].expr), (yyvsp[0].expr), OR); }
#line 2159 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2163 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 407 "language.y" /* yacc.c:1906  */


extern void env_free(Env *env)
{
    for (int i = 0; i < env->vars.len; ++i) {
        mem_free(env->vars.names[i]);
        mem_free(env->vars.heads[i]);
    }

    for (int i = 0; i < env->types.len; ++i) {
        mem_free(env->types.names[i]);
        mem_free(env->types.heads[i]);
    }

    for (int i = 0; i < env->fns.len; ++i) {
        Func *fn = env->fns.funcs[i];
        for (int j = 0; j < fn->slen; ++j)
            rel_free(fn->stmts[j]);
        for (int j = 0; j < fn->r.len; ++j)
            mem_free(fn->r.names[j]);
        for (int j = 0; j < fn->w.len; ++j)
            mem_free(fn->w.names[j]);
        for (int j = 0; j < fn->pp.len; ++j)
            mem_free(fn->pp.names[j]);
        for (int j = 0; j < fn->t.len; ++j) {
            mem_free(fn->t.names[j]);
            mem_free(fn->t.heads[j]);
        }
        if (fn->rp.name != NULL) {
            mem_free(fn->rp.name);
            mem_free(fn->rp.head);
        }
        if (fn->ret != NULL)
            mem_free(fn->ret);

        mem_free(fn);
    }

    mem_free(env);
}

extern Env *grammar_init()
{
    genv = mem_alloc(sizeof(Env));
    genv->types.len = 0;
    genv->vars.len = 0;
    genv->fns.len = 0;

    return genv;
}

extern Head *env_head(Env *env, const char *var)
{
    int i = array_scan(env->vars.names, env->vars.len, var);
    if (i < 0)
        return NULL;

    return env->vars.heads[i];
}

extern Func *env_func(Env *env, const char *name)
{
    int idx = array_scan(env->fns.names, env->fns.len, name);
    return idx < 0 ? NULL : env->fns.funcs[idx];
}

extern Func **env_funcs(Env *env, const char *name, int *cnt)
{
    int len = str_len(name);
    if (len == 0)
        *cnt = env->fns.len;
    else
        *cnt = array_freq(env->fns.names, env->fns.len, name);

    if (*cnt == 0)
        return NULL;

    Func **res = mem_alloc(sizeof(Func*) * (*cnt));
    for (int j = 0, i = 0; i < env->fns.len; ++i)
        if (len == 0 || str_cmp(name, env->fns.names[i]) == 0)
            res[j++] = env->fns.funcs[i];

    return res;
}

static L_Attrs attr_empty()
{
    L_Attrs res = {.len = 0,
                   .names[0] = NULL,
                   .renames[0] = NULL,
                   .types[0] = -1,
                   .pexprs[0] = NULL,
                   .rexprs[0] = NULL,
                   .sums[0].def = NULL};
    return res;
}

static L_Attrs attr_name(const char *name)
{
    L_Attrs res = attr_empty();
    res.len = 1;
    res.names[0] = str_dup(name);

    return res;
}

static L_Attrs attr_decl(L_Attrs attrs, Type type)
{
    for (int i = 0; i < attrs.len; ++i)
        attrs.types[i] = type;

    return attrs;
}

static L_Attrs attr_rename(const char *from, const char *to)
{
    L_Attrs res = attr_name(from);
    res.renames[0] = str_dup(to);
    return res;
}

static L_Attrs attr_extend(const char *name, L_Expr *e)
{
    L_Attrs res = attr_name(name);
    res.pexprs[0] = e;
    return res;
}

static L_Attrs attr_sum(const char *name, L_Sum sum)
{
    L_Attrs res = attr_name(name);
    res.types[0] = sum.def->type;
    res.sums[0] = sum;
    return res;
}

static L_Attrs attr_arg(Rel *rexpr, L_Expr *pexpr)
{
    /* generate a unique name to avoid errors coming from attr_merge */
    char name[MAX_NAME];
    str_print(name, "%d", gseq++);

    L_Attrs res = attr_name(name);
    res.rexprs[0] = rexpr;
    res.pexprs[0] = pexpr;
    return res;
}

static L_Attrs attr_merge(L_Attrs l, L_Attrs r)
{
    if (l.len + r.len > MAX_ATTRS)
        yyerror("number of attributes exceeds the maximum (%d)", MAX_ATTRS);

    for (int i = 0; i < r.len && l.len < MAX_ATTRS; ++i) {
        if (array_scan(l.names, l.len, r.names[i]) > -1)
            yyerror("attribute '%s' is already used", r.names[i]);

        l.names[l.len] = r.names[i];
        l.renames[l.len] = r.renames[i];
        l.types[l.len] = r.types[i];
        l.pexprs[l.len] = r.pexprs[i];
        l.rexprs[l.len] = r.rexprs[i];
        l.sums[l.len] = r.sums[i];

        l.len++;
    }

    return l;
}

static L_Sum sum_create(const char *func, const char *attr, L_Expr *def)
{
    L_Sum res;
    if (str_cmp(func, "cnt") == 0) {
        res.sum_type = CNT;
        L_Value v = {.v_int = 0};
        def = p_value(v, Int);
    } else if (str_cmp(func, "avg") == 0)
        res.sum_type = AVG;
    else if (str_cmp(func, "max") == 0)
        res.sum_type = MAX;
    else if (str_cmp(func, "min") == 0)
        res.sum_type = MIN;
    else if (str_cmp(func, "add") == 0)
        res.sum_type = ADD;
    else
        yyerror("unkown function in summary operator '%s'", func);

    if (def == NULL)
        yyerror("missing default value for the summary operator '%s'", func);

    str_cpy(res.attr, attr);
    res.def = def;

    return res;
}

static void attr_free(L_Attrs a) {
    for (int i = 0; i < a.len; ++i) {
        mem_free(a.names[i]);
        if (a.renames[i] != NULL)
            mem_free(a.renames[i]);
        if (a.pexprs[i] != NULL)
            p_free(a.pexprs[i]);
        if (a.sums[i].def != NULL)
            mem_free(a.sums[i].def);
    }
}

static Head *rel_head(L_Attrs attrs)
{
    Head *res = head_new(attrs.names, attrs.types, attrs.len);
    attr_free(attrs);

    return res;
}

static void add_head(const char *name, Head *head)
{
    if (array_scan(genv->types.names, genv->types.len, name) > -1)
        yyerror("type '%s' is already defined", name);
    else if (genv->types.len == MAX_TYPES)
        yyerror("number of type declarations "
                "exceeds the maximum (%d)", MAX_TYPES);
    else {
        int i = genv->types.len++;
        genv->types.names[i] = str_dup(name);
        genv->types.heads[i] = head;
    }
}

static void add_relvar_inline(Head *head, L_Attrs vars)
{
    for (int i = 0; i < vars.len; ++i) {
        const char *var = vars.names[i];
        if (array_scan(genv->vars.names, genv->vars.len, var) > -1)
            yyerror("variable '%s' is already defined", var);
        else if (array_scan(genv->types.names, genv->types.len, var) > -1)
            yyerror("type '%s' cannot be used as a variable name", var);
        else if (genv->vars.len == MAX_VARS)
            yyerror("number of global variables exceeds the maximum (%d)",
                    MAX_VARS);
        else {
            int j = genv->vars.len++;
            genv->vars.names[j] = str_dup(var);
            genv->vars.heads[j] = head_cpy(head);
        }
    }
    mem_free(head);
    attr_free(vars);
}

static void add_relvar(const char *rel, L_Attrs vars)
{
    int i = array_scan(genv->types.names, genv->types.len, rel);
    if (i < 0) {
        attr_free(vars);
        yyerror("unknown type '%s'", rel);
    } else
        add_relvar_inline(head_cpy(genv->types.heads[i]), vars);
}

static int func_param(Func *fn, char *name, int *pos, Type *type) {
    int res = 0;
    *pos = array_scan(fn->pp.names, fn->pp.len, name);

    if (*pos > -1) {
        res = 1;
        *type = fn->pp.types[*pos];
    }

    return res;
}

static Expr *p_convert(Head *h, Func *fn, L_Expr *e, L_Expr_Type parent_type)
{
    char hstr[MAX_HEAD_STR];
    head_to_str(hstr, h);

    Expr *res = NULL, *l = NULL, *r = NULL;
    L_Expr_Type t = e->node_type;

    if (e->left != NULL)
        l = p_convert(h, fn, e->left, t);
    if (e->right != NULL)
        r = p_convert(h, fn, e->right, t);

    if (t == ATTR) {
        int pos;
        Type type;
        if (!head_attr(h, e->name, &pos, &type)) {
            if (!func_param(fn, e->name, &pos, &type))
                yyerror("unknown attribute '%s' in %s", e->name, hstr);

            res = expr_param(pos, type);
        } else {
            res = expr_attr(pos, type);
        }
    } else if (t == VALUE && e->type == Int) {
        int i = e->val.v_int;
        if (int_overflow((parent_type == NEG ? -1 : 1), i))
            yyerror("int constant value overflow %u", i);

        res = expr_int(i);
    } else if (t == VALUE && e->type == Long) {
        long long l = e->val.v_long;
        if (long_overflow((parent_type == NEG ? -1 : 1), l))
            yyerror("long constant value overflow %llu", l);
    
        res = expr_long(l);
    } else if (t == VALUE && e->type == Real)
        res = expr_real(e->val.v_real);
    else if (t == VALUE && e->type == String)
        res = expr_str(e->val.v_str);
    else if (t == NOT) {
        if (l->type != Int)
            yyerror("expressions must be of type 'int', found '%s'",
                    type_to_str(l->type));
        res = expr_not(l);
    } else if (t == NEG) {
        if (l->type == Int)
            res = expr_mul(l, expr_int(-1));
        else if (l->type == Real)
            res = expr_mul(l, expr_real(-1));
        else if (l->type == Long)
            res = expr_mul(l, expr_long(-1));
        else
            yyerror("NEG operator does not support '%s' type",
                    type_to_str(l->type));
    } else if (t == FUNC && str_cmp("Time", e->pkg) == 0
                         && str_cmp("Now", e->name) == 0) {
        res = expr_time();
    } else if (t == FUNC && str_cmp("String", e->pkg) == 0
                         && str_cmp("Index", e->name) == 0) {
        if (l == NULL || r == NULL)
            yyerror("missing parameter(s) to call String.Index function");

        Type t = l->type;
        if (t != String || (t = r->type) != String)
            yyerror("String.Index function expects string but found %s",
                type_to_str(t));

        res = expr_str_index(l, r);
    } else if (t == FUNC) {
        Type to = 0;
        if (str_cmp("int", e->name) == 0 && str_len(e->pkg) == 0)
            to = Int;
        else if (str_cmp("real", e->name) == 0 && str_len(e->pkg) == 0)
            to = Real;
        else if (str_cmp("long", e->name) == 0 && str_len(e->pkg) == 0)
            to = Long;
        else
            yyerror("unknown function '%s.%s' in primitive expression",
                e->pkg, e->name);

        if (l->type == String)
            yyerror("conversion from string is not supported");

        res = expr_conv(l, to);
    } else {
        if (l->type != r->type)
            yyerror("expressions must be of the same type, found '%s' and '%s'",
                    type_to_str(l->type), type_to_str(r->type));

        if (t == EQ) {
            res = expr_eq(l, r);
        } else if (t == NEQ) {
            res = expr_not(expr_eq(l, r));
        } else if (t == AND) {
            if (l->type != Int)
                yyerror("AND operator expects int but found %s",
                        type_to_str(l->type));
            res = expr_and(l, r);
        } else if (t == OR) {
            if (l->type != Int)
                yyerror("OR operator expects int but found %s",
                        type_to_str(l->type));
            res = expr_or(l, r);
        } else if (t == GT) {
            res = expr_gt(l, r);
        } else if (t == LT) {
            res = expr_lt(l, r);
        } else if (t == GTE) {
            res = expr_gte(l, r);
        } else if (t == LTE) {
            res = expr_lte(l, r);
        } else if (t == SUM) {
            if (l->type == String)
                yyerror("SUM operator does not support String type");
            res = expr_sum(l, r);
        } else if (t == SUB) {
            if (l->type == String)
                yyerror("SUB operator does not support String type");
            res = expr_sub(l, r);
        } else if (t == MUL) {
            if (l->type == String)
                yyerror("MUL operator does not support String type");
            res = expr_mul(l, r);
        } else if (t == DIV) {
            if (l->type == String)
                yyerror("DIV operator does not support String type");
            res = expr_div(l, r);
        }
    }

    return res;
}

static void stmt_assign(const char *var, Rel *r)
{
    if (gfunc->slen >= MAX_STMTS)
        yyerror("number of statements exceeds the maximum (%d)", MAX_STMTS);

    int idx = array_scan(genv->vars.names, genv->vars.len, var);
    if (idx < 0)
        yyerror("unknown variable '%s'", var);

    Head *wh = genv->vars.heads[idx];
    char wstr[MAX_HEAD_STR], bstr[MAX_HEAD_STR];
    head_to_str(wstr, wh);
    head_to_str(bstr, r->head);

    if (!head_eq(r->head, wh))
        yyerror("invalid type in assignment, expects %s, found %s",
                wstr, bstr);

    idx = array_scan(gfunc->w.names, gfunc->w.len, var);
    if (idx < 0)
        gfunc->w.names[gfunc->w.len++] = str_dup(var);

    gfunc->stmts[gfunc->slen++] = rel_store(var, r);
}

static int var_exists(const char *var)
{
    return (gfunc->rp.head != NULL && str_cmp(gfunc->rp.name, var) == 0) ||
           (array_scan(gfunc->t.names, gfunc->t.len, var) > -1) ||
           (array_scan(genv->vars.names, genv->vars.len, var) > -1);
}

static void stmt_temp(const char *var, Rel *r)
{
    if (gfunc->slen >= MAX_STMTS)
        yyerror("number of statements exceeds the maximum (%d)", MAX_STMTS);

    if (var_exists(var))
        yyerror("identifier '%s' is already defined", var);

    gfunc->t.names[gfunc->t.len] = str_dup(var);
    gfunc->t.heads[gfunc->t.len++] = head_cpy(r->head);
    gfunc->stmts[gfunc->slen++] = rel_store(var, r);
}

static void stmt_call(Rel *r)
{
    if (gfunc->slen >= MAX_STMTS)
        yyerror("number of statements exceeds the maximum (%d)", MAX_STMTS);

    /* if a function return value is ignored, we create a temporary variable
       to garbage collect the unused tuples */
    if (r->head != NULL) {
        char var[MAX_NAME];
        str_print(var, "%d", gseq++);
        stmt_temp(var, r);
    } else
        gfunc->stmts[gfunc->slen++] = r;
}

static void stmt_return(Rel *r)
{
    if (gfunc->slen >= MAX_STMTS)
        yyerror("number of statements exceeds the maximum (%d)", MAX_STMTS);

    if (gfunc->ret == NULL)
        yyerror("unexpected return in function with void result type");

    Head *h = r->head;

    char hstr[MAX_HEAD_STR], res_str[MAX_HEAD_STR];
    head_to_str(hstr, h);
    head_to_str(res_str, gfunc->ret);

    int pos;
    Type t;
    for (int i = 0; i < gfunc->ret->len; ++i)
        if (!head_attr(h, gfunc->ret->names[i], &pos, &t) ||
            t != gfunc->ret->types[i])
            yyerror("invalid type in return, expects %s, found %s",
                    res_str, hstr);

    r = rel_project(r, gfunc->ret->names, gfunc->ret->len);
    gfunc->stmts[gfunc->slen++] = r;
    gfunc_ret = 1;
}

static Head *inline_rel(const char *name, Head *head)
{
    Head *res = NULL;
    if (name == NULL && head != NULL) {
        res = head;
    } else if (name != NULL) {
        int idx = array_scan(genv->types.names, genv->types.len, name);
        if (idx < 0)
            yyerror("unknown type '%s'", name);

        res = head_cpy(genv->types.heads[idx]);
    }

    return res;
}

static void fn_result(Head *h)
{
    gfunc->ret = h;
}

static void fn_rel_params(L_Attrs names, Head *h)
{
    if (names.len > 1 || gfunc->rp.name != NULL)
        yyerror("only one relational parameter is supported");

    if (array_scan(genv->vars.names, genv->vars.len, names.names[0]) > -1)
        yyerror("identifier '%s' is already used for a global variable",
                names.names[0]);

    gfunc->rp.name = str_dup(names.names[0]);
    gfunc->rp.head = head_cpy(h);
    gfunc->rp.position = ++gposition;
    mem_free(h); /* FIXME: it is duplicated in rel_param */
    attr_free(names);
}

static void fn_prim_params(L_Attrs attrs)
{
    if (gfunc->pp.len + attrs.len > MAX_ATTRS)
        yyerror("number of primitive parameters exceeds the maximum (%d)",
                MAX_ATTRS);

    for (int i = 0; i < attrs.len; ++i) {
        if (array_scan(gfunc->pp.names, gfunc->pp.len, attrs.names[i]) > -1)
            yyerror("primitive parameter '%s' is already defined",
                    attrs.names[i]);

        int pos = gfunc->pp.len++;
        gfunc->pp.types[pos] = attrs.types[i];
        gfunc->pp.names[pos] = str_dup(attrs.names[i]);
        gfunc->pp.positions[pos] = ++gposition;
    }
    attr_free(attrs);
}

static void fn_start(const char *name)
{
    if (array_scan(genv->fns.names, genv->fns.len, name) > -1)
        yyerror("function '%s' is already defined", name);

    gposition = 0;
    gfunc = mem_alloc(sizeof(Func));
    str_cpy(gfunc->name, name);
    gfunc->ret = NULL;
    gfunc->slen = 0;
    gfunc->r.len = 0;
    gfunc->w.len = 0;
    gfunc->t.len = 0;
    gfunc->pp.len = 0;
    gfunc->rp.name = NULL;
    gfunc->rp.head = NULL;
    gfunc->rp.position = 0;
}

static void fn_add()
{
    if (gfunc->ret != NULL && !gfunc_ret)
        yyerror("function '%s' is missing a return statement", gfunc->name);

    if (genv->fns.len + 1 >= MAX_VARS)
        yyerror("number of functions exceeds maximum (%d)", MAX_VARS);

    int len = genv->fns.len++;
    genv->fns.names[len] = gfunc->name;
    genv->fns.funcs[len] = gfunc;

    gfunc = NULL;
    gfunc_ret = 0;
}

static Rel *r_load(const char *name)
{
    int i = -1;
    Rel *res = NULL;
    if (gfunc->rp.name != NULL && str_cmp(gfunc->rp.name, name) == 0)
        res = rel_load(gfunc->rp.head, name);
    else if ((i = array_scan(gfunc->t.names, gfunc->t.len, name)) > -1)
        res = rel_load(gfunc->t.heads[i], name);
    else if ((i = array_scan(genv->vars.names, genv->vars.len, name)) > -1) {
        if (array_scan(gfunc->r.names, gfunc->r.len, name) < 0)
            gfunc->r.names[gfunc->r.len++] = str_dup(name);

        res = rel_load(genv->vars.heads[i], name);
    } else
        yyerror("unknown variable '%s'", name);

    return res;
}

static Rel *r_project(Rel *r, L_Attrs attrs)
{
    char hstr[MAX_HEAD_STR];
    head_to_str(hstr, r->head);

    for (int i = 0; i < attrs.len; ++i)
        if (!head_find(r->head, attrs.names[i]))
            yyerror("unknown attribute '%s' in %s", attrs.names[i], hstr);

    Rel *res = rel_project(r, attrs.names, attrs.len);
    attr_free(attrs);

    return res;
}

static Rel *r_rename(Rel *r, L_Attrs attrs)
{
    char hstr[MAX_HEAD_STR];
    head_to_str(hstr, r->head);

    char **renames = attrs.renames;

    for (int i = 0; i < attrs.len; ++i) {
        int j = array_scan(renames, attrs.len, renames[i]);

        /* TODO: below checks are too strict, we should be able to do
                  x { a, b, c } - x rename(a = b, b = c, c = d); */
        if (!head_find(r->head, attrs.names[i]))
            yyerror("unknown attribute '%s' in %s", attrs.names[i], hstr);
        if (head_find(r->head, renames[i]) || (j > -1 && j != i))
            yyerror("attribute '%s' already exists in %s",
                    renames[i], hstr);
    }

    Rel *res = rel_rename(r, attrs.names, renames, attrs.len);
    attr_free(attrs);

    return res;
}

static Rel *r_select(Rel *r, L_Expr *expr)
{
    Rel *res = rel_select(r, p_convert(r->head, gfunc, expr, POS));
    p_free(expr);

    return res;
}

static Rel *r_extend(Rel *r, L_Attrs attrs)
{
    char hstr[MAX_HEAD_STR];
    head_to_str(hstr, r->head);

    Expr *extends[MAX_ATTRS];
    for (int i = 0; i < attrs.len; ++i) {
        if (head_find(r->head, attrs.names[i]))
            yyerror("attribute '%s' already exists in %s",
                    attrs.names[i], hstr);

        extends[i] = p_convert(r->head, gfunc, attrs.pexprs[i], POS);
    }

    if (r->head->len + attrs.len > MAX_ATTRS)
        yyerror("extend result type exceeds the maximum number "
                "of attributes (%d)", MAX_ATTRS);

    Rel *res = rel_extend(r, attrs.names, extends, attrs.len);
    attr_free(attrs);

    return res;
}

static Rel *r_sum(Rel *l, Rel *r, L_Attrs attrs)
{
    char lhstr[MAX_HEAD_STR], rhstr[MAX_HEAD_STR];
    head_to_str(lhstr, l->head);
    if (r != NULL)
        head_to_str(rhstr, r->head);

    Rel *res = NULL;
    Sum *sums[MAX_ATTRS];
    for (int i = 0; i < attrs.len; ++i) {
        L_Sum s = attrs.sums[i];

        int lpos[MAX_ATTRS], rpos[MAX_ATTRS];
        if (r != NULL) {
            if (head_common(l->head, r->head, lpos, rpos) == 0)
                yyerror("use of summary with no commmon attributes "
                        "(%s and %s)", lhstr, rhstr);

            if (head_find(r->head, attrs.names[i]))
                yyerror("attribute '%s' already exists in per %s",
                        attrs.names[i], rhstr);
        }

        if (s.sum_type == CNT)
            sums[i] = sum_cnt();
        else {
            if (!is_constant(s.def))
                yyerror("only constant expressions are allowed for "
                        "default values");
            int pos;
            Type stype;
            if (!head_attr(l->head, s.attr, &pos, &stype))
                yyerror("unknown attribute '%s' in %s", s.attr, lhstr);

            Type exp_type = stype;
            if (s.sum_type == AVG)
                exp_type = Real;

            Expr *def = p_convert(l->head, gfunc, s.def, POS);
            if (def->type != exp_type)
                yyerror("invalid type of default value, expected '%s', "
                        "found %s",
                        type_to_str(exp_type),
                        type_to_str(def->type));

            if (def->type == String || stype == String)
                yyerror("invalid type of default value: string");

            Value v = expr_new_val(def, NULL, NULL);
            if (s.sum_type == AVG)
                sums[i] = sum_avg(pos, stype, v);
            else if (s.sum_type == MIN)
                sums[i] = sum_min(pos, stype, v);
            else if (s.sum_type == MAX)
                sums[i] = sum_max(pos, stype, v);
            else if (s.sum_type == ADD)
                sums[i] = sum_add(pos, stype, v);

            expr_free(def);
        }
    }

    if (r == NULL)
        res = rel_sum_unary(l, attrs.names, attrs.types, sums, attrs.len);
    else {
        if (r->head->len + attrs.len > MAX_ATTRS)
            yyerror("summary result type exceeds the maximum number "
                    "of attributes (%d)", MAX_ATTRS);

        res = rel_sum(l, r, attrs.names, attrs.types, sums, attrs.len);
    }
    attr_free(attrs);

    return res;
}

static Rel *r_join(Rel *l, Rel *r)
{
    char lhstr[MAX_HEAD_STR];
    head_to_str(lhstr, l->head);
    int num_attrs = l->head->len + r->head->len;

    for (int i = 0; i < l->head->len; ++i) {
        char *n = l->head->names[i];
        Type t; int pos;
        if (head_attr(r->head, n, &pos, &t)) {
            num_attrs--;

            if (t != l->head->types[i])
                yyerror("attribute '%s' is of different type in right %s",
                        n, lhstr);
        }
    }

    if (num_attrs > MAX_ATTRS)
        yyerror("join result type exceeds the maximum number "
                "of attributes (%d)", MAX_ATTRS);

    return rel_join(l, r);
}

static Rel *r_union(Rel *l, Rel *r)
{
    char lhstr[MAX_HEAD_STR], rhstr[MAX_HEAD_STR];
    head_to_str(lhstr, l->head);
    head_to_str(rhstr, r->head);

    if (!head_eq(l->head, r->head))
        yyerror("use of union with different types (%s and %s)",
                lhstr, rhstr);

    return rel_union(l, r);
}

static Rel *r_diff(Rel *l, Rel *r)
{
    char lhstr[MAX_HEAD_STR], rhstr[MAX_HEAD_STR];
    head_to_str(lhstr, l->head);
    head_to_str(rhstr, r->head);

    int lpos[MAX_ATTRS], rpos[MAX_ATTRS];
    if (head_common(l->head, r->head, lpos, rpos) == 0)
        yyerror("use of semidiff with no commmon attributes (%s and %s)",
                lhstr, rhstr);

    return rel_diff(l, r);
}

static int merge_vars(char **dest, int dlen, char **src, int slen)
{
    for (int i = 0; i < slen; ++i) {
        int pos = array_scan(dest, dlen, src[i]);
        if (pos > -1)
            continue;

        if (dlen + 1 > MAX_VARS)
            yyerror("number of variables exceeds the maximum (%d)", MAX_VARS);

        dest[dlen] = str_dup(src[i]);
        dlen++;
    }

    return dlen;
}

static Rel *r_call(const char *func, L_Attrs args)
{
    Rel *res = NULL;

    /* gramatically there is no difference between a variable load and
       a function call hence we first check if it is a load instruction */
    if (var_exists(func)) {
        res = r_load(func);
        goto exit;
    }

    int idx = array_scan(genv->fns.names, genv->fns.len, func);
    if (idx < 0)
        yyerror("unknown identifier '%s' neither function call nor variable "
                "declared with this name", func);

    Func *fn = genv->fns.funcs[idx];
    int cnt = fn->pp.len;
    cnt += (fn->rp.head == NULL) ? 0 : 1;

    if (args.len != cnt)
        yyerror("invalid number of arguments, expected %d found %d",
                cnt, args.len);

    if (fn->rp.head != NULL) {
        int pos = fn->rp.position;
        if (args.rexprs[pos - 1] == NULL)
            yyerror("expected a relational argument at position %d", pos);

        if (!head_eq(fn->rp.head, args.rexprs[pos - 1]->head))
            yyerror("invalid relational argument at position %d", pos);
    }

    for (int i = 0; i < fn->pp.len; ++i) {
        int pos = fn->pp.positions[i];
        if (args.pexprs[pos - 1] == NULL)
            yyerror("expected a primitive argument at position %d", pos);

        if (args.pexprs[pos - 1]->type != fn->pp.types[i])
            yyerror("invalid primitive argument at position %d", pos);

        mem_free(args.names[pos - 1]);
        args.names[pos - 1] = str_dup(fn->pp.names[i]);
    }

    Rel *rexpr = NULL;
    Expr *pexprs[MAX_ATTRS];
    int plen = 0;
    for (int i = 0; i < args.len; ++i) {
        if (args.rexprs[i] != NULL)
            rexpr = args.rexprs[i];

        if (args.pexprs[i] != NULL) {
            /* empty head due to constant expression */
            Head *empty = head_new(NULL, NULL, 0);
            pexprs[plen++] = p_convert(empty, gfunc, args.pexprs[i], POS);
            mem_free(empty);
        }
    }

    res = rel_call(fn->r.names, fn->r.len,
                   fn->w.names, fn->w.len,
                   fn->t.names, fn->t.len,
                   fn->stmts, fn->slen,
                   pexprs, plen,
                   rexpr, fn->rp.name,
                   fn->ret);

    gfunc->r.len = merge_vars(gfunc->r.names, gfunc->r.len,
                              fn->r.names, fn->r.len);
    gfunc->w.len = merge_vars(gfunc->w.names, gfunc->w.len,
                              fn->w.names, fn->w.len);

exit:
    attr_free(args);
    return res;
}

static void p_free(L_Expr *e)
{
    if (e->left != NULL)
        p_free(e->left);
    if (e->right != NULL)
        p_free(e->right);

    mem_free(e);
}

static L_Expr *p_alloc(L_Expr_Type t)
{
    L_Expr *res = mem_alloc(sizeof(L_Expr));
    res->node_type = t;
    res->type = 0;
    res->left = NULL;
    res->right = NULL;
    res->val.v_long = 0;
    res->pkg[0] = '\0';
    res->name[0] = '\0';
    res->is_const = 1;

    return res;
}

static L_Expr *p_attr(const char *name)
{
    L_Expr *res = p_alloc(ATTR);
    str_cpy(res->name, name);
    res->is_const = 0;

    return res;
}

static L_Expr *p_func(const char *pkg, const char *name, L_Expr *l, L_Expr *r)
{
    L_Expr *res = p_alloc(FUNC);
    str_cpy(res->pkg, pkg);
    str_cpy(res->name, name);
    res->is_const = 0;
    res->left = l;
    res->right = r;

    return res;
}

static L_Expr *p_value(L_Value val, Type t)
{
    L_Expr *res = p_alloc(VALUE);
    res->type = t;
    res->val = val;

    return res;
}

static L_Expr *p_op(L_Expr *l, L_Expr *r, L_Expr_Type node_type)
{
    L_Expr *res = p_alloc(node_type);
    res->left = l;
    res->right = r;
    res->type = l->type;

    return res;
}

static int is_constant(L_Expr *e)
{
    int res = e->is_const;

    if (e->left != NULL)
        res = res && is_constant(e->left);
    if (e->right != NULL)
        res = res && is_constant(e->right);
        
    return res;    
}

extern int env_compat(Env *old, Env *new)
{
    for (int i = 0; i < old->vars.len; ++i) {
        Head *h = env_head(new, old->vars.names[i]);
        if (h != NULL && !head_eq(h, old->vars.heads[i]))
            return 0;
    }

    return 1;
}
