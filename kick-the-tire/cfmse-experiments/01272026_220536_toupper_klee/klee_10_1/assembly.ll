; ModuleID = 'toupper_nosm.ll'
source_filename = "toupper.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [5 x i8] c"text\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @to_upper(i8* %text, i32 %n) #0 !dbg !8 {
entry:
  br label %for.cond, !dbg !11

for.cond:                                         ; preds = %for.inc, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ], !dbg !12
  %cmp = icmp slt i32 %i.0, %n, !dbg !13
  br i1 %cmp, label %for.body, label %for.end, !dbg !14

for.body:                                         ; preds = %for.cond
  %idxprom = sext i32 %i.0 to i64, !dbg !15
  %arrayidx = getelementptr inbounds i8, i8* %text, i64 %idxprom, !dbg !15
  %0 = load i8, i8* %arrayidx, align 1, !dbg !15
  %conv = sext i8 %0 to i32, !dbg !15
  %cmp1 = icmp sge i32 %conv, 97, !dbg !16
  %conv2 = zext i1 %cmp1 to i32, !dbg !16
  %idxprom3 = sext i32 %i.0 to i64, !dbg !17
  %arrayidx4 = getelementptr inbounds i8, i8* %text, i64 %idxprom3, !dbg !17
  %1 = load i8, i8* %arrayidx4, align 1, !dbg !17
  %conv5 = sext i8 %1 to i32, !dbg !17
  %cmp6 = icmp sle i32 %conv5, 122, !dbg !18
  %conv7 = zext i1 %cmp6 to i32, !dbg !18
  %and = and i32 %conv2, %conv7, !dbg !19
  %tobool = icmp ne i32 %and, 0, !dbg !19
  br i1 %tobool, label %if.then, label %for.inc, !dbg !20

if.then:                                          ; preds = %for.body
  %idxprom8 = sext i32 %i.0 to i64, !dbg !21
  %arrayidx9 = getelementptr inbounds i8, i8* %text, i64 %idxprom8, !dbg !21
  %2 = load i8, i8* %arrayidx9, align 1, !dbg !21
  %conv10 = sext i8 %2 to i32, !dbg !21
  %sub = sub nsw i32 %conv10, 97, !dbg !22
  %add = add nsw i32 %sub, 65, !dbg !23
  %conv11 = trunc i32 %add to i8, !dbg !21
  %idxprom12 = sext i32 %i.0 to i64, !dbg !24
  %arrayidx13 = getelementptr inbounds i8, i8* %text, i64 %idxprom12, !dbg !24
  store i8 %conv11, i8* %arrayidx13, align 1, !dbg !25
  br label %for.inc, !dbg !26

for.inc:                                          ; preds = %for.body, %if.then
  %inc = add nsw i32 %i.0, 1, !dbg !27
  br label %for.cond, !dbg !14, !llvm.loop !28

for.end:                                          ; preds = %for.cond
  ret void, !dbg !31
}

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !32 {
entry:
  %conv = sext i32 10 to i64, !dbg !33
  %mul = mul i64 %conv, 1, !dbg !34
  %call = call noalias align 16 i8* @malloc(i64 %mul) #3, !dbg !35
  %conv1 = sext i32 10 to i64, !dbg !36
  %mul2 = mul i64 %conv1, 1, !dbg !37
  call void @klee_make_symbolic(i8* %call, i64 %mul2, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0)), !dbg !38
  call void @to_upper(i8* %call, i32 10), !dbg !39
  ret i32 0, !dbg !40
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
!12 = !DILocation(line: 0, scope: !8)
!13 = !DILocation(line: 6, column: 21, scope: !8)
!14 = !DILocation(line: 6, column: 3, scope: !8)
!15 = !DILocation(line: 10, column: 10, scope: !8)
!16 = !DILocation(line: 10, column: 18, scope: !8)
!17 = !DILocation(line: 10, column: 29, scope: !8)
!18 = !DILocation(line: 10, column: 37, scope: !8)
!19 = !DILocation(line: 10, column: 26, scope: !8)
!20 = !DILocation(line: 10, column: 9, scope: !8)
!21 = !DILocation(line: 11, column: 17, scope: !8)
!22 = !DILocation(line: 11, column: 25, scope: !8)
!23 = !DILocation(line: 11, column: 31, scope: !8)
!24 = !DILocation(line: 11, column: 7, scope: !8)
!25 = !DILocation(line: 11, column: 15, scope: !8)
!26 = !DILocation(line: 12, column: 5, scope: !8)
!27 = !DILocation(line: 6, column: 27, scope: !8)
!28 = distinct !{!28, !14, !29, !30}
!29 = !DILocation(line: 16, column: 3, scope: !8)
!30 = !{!"llvm.loop.mustprogress"}
!31 = !DILocation(line: 17, column: 1, scope: !8)
!32 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 63, type: !9, scopeLine: 63, spFlags: DISPFlagDefinition, unit: !0)
!33 = !DILocation(line: 65, column: 30, scope: !32)
!34 = !DILocation(line: 65, column: 31, scope: !32)
!35 = !DILocation(line: 65, column: 23, scope: !32)
!36 = !DILocation(line: 67, column: 28, scope: !32)
!37 = !DILocation(line: 67, column: 29, scope: !32)
!38 = !DILocation(line: 67, column: 3, scope: !32)
!39 = !DILocation(line: 69, column: 3, scope: !32)
!40 = !DILocation(line: 78, column: 3, scope: !32)
