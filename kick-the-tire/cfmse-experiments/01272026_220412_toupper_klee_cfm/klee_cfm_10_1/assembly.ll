; ModuleID = 'toupper_nosm.ll'
source_filename = "toupper.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [5 x i8] c"text\00", align 1
@cfmse.dci_gv = private global [8 x i8] zeroinitializer

; Function Attrs: noinline nounwind uwtable
define dso_local void @to_upper(i8* %text, i32 %n) #0 !dbg !8 {
entry:
  %cfmse.dci_gep = getelementptr [8 x i8], [8 x i8]* @cfmse.dci_gv, i64 0, i64 0
  br label %for.cond, !dbg !11, !sourceFile !12, !mergedLineNum !13

for.cond:                                         ; preds = %for.inc, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ], !dbg !14, !sourceFile !12, !mergedLineNum !15
  %cmp = icmp slt i32 %i.0, %n, !dbg !16, !sourceFile !12, !mergedLineNum !13
  br i1 %cmp, label %for.body, label %for.end, !dbg !17, !sourceFile !12, !mergedLineNum !13

for.body:                                         ; preds = %for.cond
  %idxprom = sext i32 %i.0 to i64, !dbg !18, !sourceFile !12, !mergedLineNum !19
  %arrayidx = getelementptr inbounds i8, i8* %text, i64 %idxprom, !dbg !18, !sourceFile !12, !mergedLineNum !19
  %0 = load i8, i8* %arrayidx, align 1, !dbg !18, !sourceFile !12, !mergedLineNum !19
  %conv = sext i8 %0 to i32, !dbg !18, !sourceFile !12, !mergedLineNum !19
  %cmp1 = icmp sge i32 %conv, 97, !dbg !20, !sourceFile !12, !mergedLineNum !19
  %conv2 = zext i1 %cmp1 to i32, !dbg !20, !sourceFile !12, !mergedLineNum !19
  %idxprom3 = sext i32 %i.0 to i64, !dbg !21, !sourceFile !12, !mergedLineNum !19
  %arrayidx4 = getelementptr inbounds i8, i8* %text, i64 %idxprom3, !dbg !21, !sourceFile !12, !mergedLineNum !19
  %1 = load i8, i8* %arrayidx4, align 1, !dbg !21, !sourceFile !12, !mergedLineNum !19
  %conv5 = sext i8 %1 to i32, !dbg !21, !sourceFile !12, !mergedLineNum !19
  %cmp6 = icmp sle i32 %conv5, 122, !dbg !22, !sourceFile !12, !mergedLineNum !19
  %conv7 = zext i1 %cmp6 to i32, !dbg !22, !sourceFile !12, !mergedLineNum !19
  %and = and i32 %conv2, %conv7, !dbg !23, !sourceFile !12, !mergedLineNum !19
  %tobool = icmp ne i32 %and, 0, !dbg !23, !sourceFile !12, !mergedLineNum !19
  %2 = sext i32 %i.0 to i64, !dbg !24, !sourceFile !12, !mergedLineNum !25
  %3 = getelementptr inbounds i8, i8* %text, i64 %2, !dbg !24, !sourceFile !12, !mergedLineNum !25
  %4 = load i8, i8* %3, align 1, !dbg !24, !sourceFile !12, !mergedLineNum !25
  %5 = sext i8 %4 to i32, !dbg !24, !sourceFile !12, !mergedLineNum !25
  %6 = sub nsw i32 %5, 97, !dbg !26, !sourceFile !12, !mergedLineNum !25
  %7 = add nsw i32 %6, 65, !dbg !27, !sourceFile !12, !mergedLineNum !25
  %8 = trunc i32 %7 to i8, !dbg !24, !sourceFile !12, !mergedLineNum !25
  %9 = sext i32 %i.0 to i64, !dbg !28, !sourceFile !12, !mergedLineNum !25
  %10 = getelementptr inbounds i8, i8* %text, i64 %9, !dbg !28, !sourceFile !12, !mergedLineNum !25
  %11 = load i8, i8* %10, align 1, !dbg !29
  %merged.select = select i1 %tobool, i8 %8, i8 %11, !dbg !29
  store i8 %merged.select, i8* %10, align 1, !dbg !29, !sourceFile !12, !mergedLineNum !25
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %inc = add nsw i32 %i.0, 1, !dbg !30, !sourceFile !12, !mergedLineNum !13
  br label %for.cond, !dbg !17, !llvm.loop !31, !sourceFile !12, !mergedLineNum !13

for.end:                                          ; preds = %for.cond
  ret void, !dbg !34, !sourceFile !12, !mergedLineNum !35
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !36 {
entry:
  %conv = sext i32 10 to i64, !dbg !37, !sourceFile !12, !mergedLineNum !38
  %mul = mul i64 %conv, 1, !dbg !39, !sourceFile !12, !mergedLineNum !38
  %call = call noalias align 16 i8* @malloc(i64 %mul) #3, !dbg !40, !sourceFile !12, !mergedLineNum !38
  %conv1 = sext i32 10 to i64, !dbg !41, !sourceFile !12, !mergedLineNum !42
  %mul2 = mul i64 %conv1, 1, !dbg !43, !sourceFile !12, !mergedLineNum !42
  call void @klee_make_symbolic(i8* %call, i64 %mul2, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0)), !dbg !44, !sourceFile !12, !mergedLineNum !42
  call void @to_upper(i8* %call, i32 10), !dbg !45, !sourceFile !12, !mergedLineNum !46
  %cfmse.dci_gep = getelementptr [8 x i8], [8 x i8]* @cfmse.dci_gv, i64 0, i64 0
  ret i32 0, !dbg !47, !sourceFile !12, !mergedLineNum !48
}

; Function Attrs: nounwind
declare dso_local noalias align 16 i8* @malloc(i64) #1

declare dso_local void @klee_make_symbolic(i8*, i64, i8*) #2

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2, !3, !4, !5, !6}
!llvm.ident = !{!7}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 14.0.0 (git@github.com:charitha22/llvm-project-rocm.git 136e82d150fe486fc53a55cfeca53cb529c188d6)", isOptimized: false, runtimeVersion: 0, emissionKind: LineTablesOnly, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "toupper.c", directory: "/artifact/kick-the-tire/toupper")
!2 = !{i32 7, !"Dwarf Version", i32 4}
!3 = !{i32 2, !"Debug Info Version", i32 3}
!4 = !{i32 1, !"wchar_size", i32 4}
!5 = !{i32 7, !"uwtable", i32 1}
!6 = !{i32 7, !"frame-pointer", i32 2}
!7 = !{!"clang version 14.0.0 (git@github.com:charitha22/llvm-project-rocm.git 136e82d150fe486fc53a55cfeca53cb529c188d6)"}
!8 = distinct !DISubprogram(name: "to_upper", scope: !1, file: !1, line: 5, type: !9, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0)
!9 = !DISubroutineType(types: !10)
!10 = !{}
!11 = !DILocation(line: 6, column: 8, scope: !8)
!12 = !{!"toupper.c"}
!13 = !{!"6"}
!14 = !DILocation(line: 0, scope: !8)
!15 = !{!"0"}
!16 = !DILocation(line: 6, column: 21, scope: !8)
!17 = !DILocation(line: 6, column: 3, scope: !8)
!18 = !DILocation(line: 10, column: 10, scope: !8)
!19 = !{!"10"}
!20 = !DILocation(line: 10, column: 18, scope: !8)
!21 = !DILocation(line: 10, column: 29, scope: !8)
!22 = !DILocation(line: 10, column: 37, scope: !8)
!23 = !DILocation(line: 10, column: 26, scope: !8)
!24 = !DILocation(line: 11, column: 17, scope: !8)
!25 = !{!"-2,11"}
!26 = !DILocation(line: 11, column: 25, scope: !8)
!27 = !DILocation(line: 11, column: 31, scope: !8)
!28 = !DILocation(line: 11, column: 7, scope: !8)
!29 = !DILocation(line: 11, column: 15, scope: !8)
!30 = !DILocation(line: 6, column: 27, scope: !8)
!31 = distinct !{!31, !17, !32, !33}
!32 = !DILocation(line: 16, column: 3, scope: !8)
!33 = !{!"llvm.loop.mustprogress"}
!34 = !DILocation(line: 17, column: 1, scope: !8)
!35 = !{!"17"}
!36 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 63, type: !9, scopeLine: 63, spFlags: DISPFlagDefinition, unit: !0)
!37 = !DILocation(line: 65, column: 30, scope: !36)
!38 = !{!"65"}
!39 = !DILocation(line: 65, column: 31, scope: !36)
!40 = !DILocation(line: 65, column: 23, scope: !36)
!41 = !DILocation(line: 67, column: 28, scope: !36)
!42 = !{!"67"}
!43 = !DILocation(line: 67, column: 29, scope: !36)
!44 = !DILocation(line: 67, column: 3, scope: !36)
!45 = !DILocation(line: 69, column: 3, scope: !36)
!46 = !{!"69"}
!47 = !DILocation(line: 78, column: 3, scope: !36)
!48 = !{!"78"}
