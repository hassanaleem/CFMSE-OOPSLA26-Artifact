; ModuleID = 'toupper.c'
source_filename = "toupper.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [5 x i8] c"text\00", align 1
@.str.1 = private unnamed_addr constant [39 x i8] c"!((text[i] >= 'a') & (text[i] <= 'z'))\00", align 1
@.str.2 = private unnamed_addr constant [10 x i8] c"toupper.c\00", align 1
@__PRETTY_FUNCTION__.main = private unnamed_addr constant [11 x i8] c"int main()\00", align 1
@.str.3 = private unnamed_addr constant [10 x i8] c"verified\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @to_upper(i8* %text, i32 %n) #0 !dbg !12 {
entry:
  %text.addr = alloca i8*, align 8
  %n.addr = alloca i32, align 4
  %i = alloca i32, align 4
  store i8* %text, i8** %text.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %text.addr, metadata !16, metadata !DIExpression()), !dbg !17
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !18, metadata !DIExpression()), !dbg !19
  call void @llvm.dbg.declare(metadata i32* %i, metadata !20, metadata !DIExpression()), !dbg !22
  store i32 0, i32* %i, align 4, !dbg !22
  br label %for.cond, !dbg !23

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !24
  %1 = load i32, i32* %n.addr, align 4, !dbg !26
  %cmp = icmp slt i32 %0, %1, !dbg !27
  br i1 %cmp, label %for.body, label %for.end, !dbg !28

for.body:                                         ; preds = %for.cond
  call void @klee_open_merge(), !dbg !29
  %2 = load i8*, i8** %text.addr, align 8, !dbg !31
  %3 = load i32, i32* %i, align 4, !dbg !33
  %idxprom = sext i32 %3 to i64, !dbg !31
  %arrayidx = getelementptr inbounds i8, i8* %2, i64 %idxprom, !dbg !31
  %4 = load i8, i8* %arrayidx, align 1, !dbg !31
  %conv = sext i8 %4 to i32, !dbg !31
  %cmp1 = icmp sge i32 %conv, 97, !dbg !34
  %conv2 = zext i1 %cmp1 to i32, !dbg !34
  %5 = load i8*, i8** %text.addr, align 8, !dbg !35
  %6 = load i32, i32* %i, align 4, !dbg !36
  %idxprom3 = sext i32 %6 to i64, !dbg !35
  %arrayidx4 = getelementptr inbounds i8, i8* %5, i64 %idxprom3, !dbg !35
  %7 = load i8, i8* %arrayidx4, align 1, !dbg !35
  %conv5 = sext i8 %7 to i32, !dbg !35
  %cmp6 = icmp sle i32 %conv5, 122, !dbg !37
  %conv7 = zext i1 %cmp6 to i32, !dbg !37
  %and = and i32 %conv2, %conv7, !dbg !38
  %tobool = icmp ne i32 %and, 0, !dbg !38
  br i1 %tobool, label %if.then, label %if.end, !dbg !39

if.then:                                          ; preds = %for.body
  %8 = load i8*, i8** %text.addr, align 8, !dbg !40
  %9 = load i32, i32* %i, align 4, !dbg !42
  %idxprom8 = sext i32 %9 to i64, !dbg !40
  %arrayidx9 = getelementptr inbounds i8, i8* %8, i64 %idxprom8, !dbg !40
  %10 = load i8, i8* %arrayidx9, align 1, !dbg !40
  %conv10 = sext i8 %10 to i32, !dbg !40
  %sub = sub nsw i32 %conv10, 97, !dbg !43
  %add = add nsw i32 %sub, 65, !dbg !44
  %conv11 = trunc i32 %add to i8, !dbg !40
  %11 = load i8*, i8** %text.addr, align 8, !dbg !45
  %12 = load i32, i32* %i, align 4, !dbg !46
  %idxprom12 = sext i32 %12 to i64, !dbg !45
  %arrayidx13 = getelementptr inbounds i8, i8* %11, i64 %idxprom12, !dbg !45
  store i8 %conv11, i8* %arrayidx13, align 1, !dbg !47
  br label %if.end, !dbg !48

if.end:                                           ; preds = %if.then, %for.body
  call void @klee_close_merge(), !dbg !49
  br label %for.inc, !dbg !50

for.inc:                                          ; preds = %if.end
  %13 = load i32, i32* %i, align 4, !dbg !51
  %inc = add nsw i32 %13, 1, !dbg !51
  store i32 %inc, i32* %i, align 4, !dbg !51
  br label %for.cond, !dbg !52, !llvm.loop !53

for.end:                                          ; preds = %for.cond
  ret void, !dbg !56
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local void @klee_open_merge() #2

declare dso_local void @klee_close_merge() #2

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !57 {
entry:
  %retval = alloca i32, align 4
  %n = alloca i32, align 4
  %text = alloca i8*, align 8
  %i = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  call void @llvm.dbg.declare(metadata i32* %n, metadata !60, metadata !DIExpression()), !dbg !61
  store i32 100, i32* %n, align 4, !dbg !61
  call void @llvm.dbg.declare(metadata i8** %text, metadata !62, metadata !DIExpression()), !dbg !63
  %0 = load i32, i32* %n, align 4, !dbg !64
  %conv = sext i32 %0 to i64, !dbg !64
  %mul = mul i64 %conv, 1, !dbg !65
  %call = call noalias align 16 i8* @malloc(i64 %mul) #4, !dbg !66
  store i8* %call, i8** %text, align 8, !dbg !63
  %1 = load i8*, i8** %text, align 8, !dbg !67
  %2 = load i32, i32* %n, align 4, !dbg !68
  %conv1 = sext i32 %2 to i64, !dbg !68
  %mul2 = mul i64 %conv1, 1, !dbg !69
  call void @klee_make_symbolic(i8* %1, i64 %mul2, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0)), !dbg !70
  %3 = load i8*, i8** %text, align 8, !dbg !71
  %4 = load i32, i32* %n, align 4, !dbg !72
  call void @to_upper(i8* %3, i32 %4), !dbg !73
  call void @llvm.dbg.declare(metadata i32* %i, metadata !74, metadata !DIExpression()), !dbg !76
  store i32 0, i32* %i, align 4, !dbg !76
  br label %for.cond, !dbg !77

for.cond:                                         ; preds = %for.inc, %entry
  %5 = load i32, i32* %i, align 4, !dbg !78
  %6 = load i32, i32* %n, align 4, !dbg !80
  %cmp = icmp slt i32 %5, %6, !dbg !81
  br i1 %cmp, label %for.body, label %for.end, !dbg !82

for.body:                                         ; preds = %for.cond
  %7 = load i8*, i8** %text, align 8, !dbg !83
  %8 = load i32, i32* %i, align 4, !dbg !83
  %idxprom = sext i32 %8 to i64, !dbg !83
  %arrayidx = getelementptr inbounds i8, i8* %7, i64 %idxprom, !dbg !83
  %9 = load i8, i8* %arrayidx, align 1, !dbg !83
  %conv4 = sext i8 %9 to i32, !dbg !83
  %cmp5 = icmp sge i32 %conv4, 97, !dbg !83
  %conv6 = zext i1 %cmp5 to i32, !dbg !83
  %10 = load i8*, i8** %text, align 8, !dbg !83
  %11 = load i32, i32* %i, align 4, !dbg !83
  %idxprom7 = sext i32 %11 to i64, !dbg !83
  %arrayidx8 = getelementptr inbounds i8, i8* %10, i64 %idxprom7, !dbg !83
  %12 = load i8, i8* %arrayidx8, align 1, !dbg !83
  %conv9 = sext i8 %12 to i32, !dbg !83
  %cmp10 = icmp sle i32 %conv9, 122, !dbg !83
  %conv11 = zext i1 %cmp10 to i32, !dbg !83
  %and = and i32 %conv6, %conv11, !dbg !83
  %tobool = icmp ne i32 %and, 0, !dbg !83
  br i1 %tobool, label %cond.false, label %cond.true, !dbg !83

cond.true:                                        ; preds = %for.body
  br label %cond.end, !dbg !83

cond.false:                                       ; preds = %for.body
  %call12 = call i32 (i8*, i8*, i32, i8*, ...) bitcast (i32 (...)* @__assert_fail to i32 (i8*, i8*, i32, i8*, ...)*)(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.1, i64 0, i64 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 74, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)), !dbg !83
  br label %cond.end, !dbg !83

cond.end:                                         ; preds = %cond.false, %cond.true
  br label %for.inc, !dbg !83

for.inc:                                          ; preds = %cond.end
  %13 = load i32, i32* %i, align 4, !dbg !84
  %inc = add nsw i32 %13, 1, !dbg !84
  store i32 %inc, i32* %i, align 4, !dbg !84
  br label %for.cond, !dbg !85, !llvm.loop !86

for.end:                                          ; preds = %for.cond
  %call13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3, i64 0, i64 0)), !dbg !88
  ret i32 0, !dbg !89
}

; Function Attrs: nounwind
declare dso_local noalias align 16 i8* @malloc(i64) #3

declare dso_local void @klee_make_symbolic(i8*, i64, i8*) #2

declare dso_local i32 @__assert_fail(...) #2

declare dso_local i32 @printf(i8*, ...) #2

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!6, !7, !8, !9, !10}
!llvm.ident = !{!11}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 14.0.0 (git@github.com:charitha22/llvm-project-rocm.git 136e82d150fe486fc53a55cfeca53cb529c188d6)", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, enums: !2, retainedTypes: !3, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "toupper.c", directory: "/artifact/kick-the-tire/toupper")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64)
!5 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!6 = !{i32 7, !"Dwarf Version", i32 4}
!7 = !{i32 2, !"Debug Info Version", i32 3}
!8 = !{i32 1, !"wchar_size", i32 4}
!9 = !{i32 7, !"uwtable", i32 1}
!10 = !{i32 7, !"frame-pointer", i32 2}
!11 = !{!"clang version 14.0.0 (git@github.com:charitha22/llvm-project-rocm.git 136e82d150fe486fc53a55cfeca53cb529c188d6)"}
!12 = distinct !DISubprogram(name: "to_upper", scope: !1, file: !1, line: 5, type: !13, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!13 = !DISubroutineType(types: !14)
!14 = !{null, !4, !15}
!15 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!16 = !DILocalVariable(name: "text", arg: 1, scope: !12, file: !1, line: 5, type: !4)
!17 = !DILocation(line: 5, column: 21, scope: !12)
!18 = !DILocalVariable(name: "n", arg: 2, scope: !12, file: !1, line: 5, type: !15)
!19 = !DILocation(line: 5, column: 31, scope: !12)
!20 = !DILocalVariable(name: "i", scope: !21, file: !1, line: 6, type: !15)
!21 = distinct !DILexicalBlock(scope: !12, file: !1, line: 6, column: 3)
!22 = !DILocation(line: 6, column: 12, scope: !21)
!23 = !DILocation(line: 6, column: 8, scope: !21)
!24 = !DILocation(line: 6, column: 19, scope: !25)
!25 = distinct !DILexicalBlock(scope: !21, file: !1, line: 6, column: 3)
!26 = !DILocation(line: 6, column: 23, scope: !25)
!27 = !DILocation(line: 6, column: 21, scope: !25)
!28 = !DILocation(line: 6, column: 3, scope: !21)
!29 = !DILocation(line: 8, column: 5, scope: !30)
!30 = distinct !DILexicalBlock(scope: !25, file: !1, line: 6, column: 31)
!31 = !DILocation(line: 10, column: 10, scope: !32)
!32 = distinct !DILexicalBlock(scope: !30, file: !1, line: 10, column: 9)
!33 = !DILocation(line: 10, column: 15, scope: !32)
!34 = !DILocation(line: 10, column: 18, scope: !32)
!35 = !DILocation(line: 10, column: 29, scope: !32)
!36 = !DILocation(line: 10, column: 34, scope: !32)
!37 = !DILocation(line: 10, column: 37, scope: !32)
!38 = !DILocation(line: 10, column: 26, scope: !32)
!39 = !DILocation(line: 10, column: 9, scope: !30)
!40 = !DILocation(line: 11, column: 17, scope: !41)
!41 = distinct !DILexicalBlock(scope: !32, file: !1, line: 10, column: 46)
!42 = !DILocation(line: 11, column: 22, scope: !41)
!43 = !DILocation(line: 11, column: 25, scope: !41)
!44 = !DILocation(line: 11, column: 31, scope: !41)
!45 = !DILocation(line: 11, column: 7, scope: !41)
!46 = !DILocation(line: 11, column: 12, scope: !41)
!47 = !DILocation(line: 11, column: 15, scope: !41)
!48 = !DILocation(line: 12, column: 5, scope: !41)
!49 = !DILocation(line: 14, column: 5, scope: !30)
!50 = !DILocation(line: 16, column: 3, scope: !30)
!51 = !DILocation(line: 6, column: 27, scope: !25)
!52 = !DILocation(line: 6, column: 3, scope: !25)
!53 = distinct !{!53, !28, !54, !55}
!54 = !DILocation(line: 16, column: 3, scope: !21)
!55 = !{!"llvm.loop.mustprogress"}
!56 = !DILocation(line: 17, column: 1, scope: !12)
!57 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 63, type: !58, scopeLine: 63, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!58 = !DISubroutineType(types: !59)
!59 = !{!15}
!60 = !DILocalVariable(name: "n", scope: !57, file: !1, line: 64, type: !15)
!61 = !DILocation(line: 64, column: 7, scope: !57)
!62 = !DILocalVariable(name: "text", scope: !57, file: !1, line: 65, type: !4)
!63 = !DILocation(line: 65, column: 9, scope: !57)
!64 = !DILocation(line: 65, column: 30, scope: !57)
!65 = !DILocation(line: 65, column: 31, scope: !57)
!66 = !DILocation(line: 65, column: 23, scope: !57)
!67 = !DILocation(line: 67, column: 22, scope: !57)
!68 = !DILocation(line: 67, column: 28, scope: !57)
!69 = !DILocation(line: 67, column: 29, scope: !57)
!70 = !DILocation(line: 67, column: 3, scope: !57)
!71 = !DILocation(line: 69, column: 12, scope: !57)
!72 = !DILocation(line: 69, column: 18, scope: !57)
!73 = !DILocation(line: 69, column: 3, scope: !57)
!74 = !DILocalVariable(name: "i", scope: !75, file: !1, line: 73, type: !15)
!75 = distinct !DILexicalBlock(scope: !57, file: !1, line: 73, column: 3)
!76 = !DILocation(line: 73, column: 12, scope: !75)
!77 = !DILocation(line: 73, column: 8, scope: !75)
!78 = !DILocation(line: 73, column: 19, scope: !79)
!79 = distinct !DILexicalBlock(scope: !75, file: !1, line: 73, column: 3)
!80 = !DILocation(line: 73, column: 23, scope: !79)
!81 = !DILocation(line: 73, column: 21, scope: !79)
!82 = !DILocation(line: 73, column: 3, scope: !75)
!83 = !DILocation(line: 74, column: 5, scope: !79)
!84 = !DILocation(line: 73, column: 27, scope: !79)
!85 = !DILocation(line: 73, column: 3, scope: !79)
!86 = distinct !{!86, !82, !87, !55}
!87 = !DILocation(line: 74, column: 5, scope: !75)
!88 = !DILocation(line: 75, column: 3, scope: !57)
!89 = !DILocation(line: 78, column: 3, scope: !57)
