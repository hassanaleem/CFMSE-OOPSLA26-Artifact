; ModuleID = 'toupper_sm.ll'
source_filename = "toupper.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [5 x i8] c"text\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @to_upper(i8* %text, i32 %n) #0 !dbg !8 {
entry:
  br label %for.cond, !dbg !11

for.cond:                                         ; preds = %if.end, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %if.end ], !dbg !12
  %cmp = icmp slt i32 %i.0, %n, !dbg !13
  br i1 %cmp, label %for.body, label %for.end, !dbg !14

for.body:                                         ; preds = %for.cond
  call void @klee_open_merge(), !dbg !15
  %idxprom = sext i32 %i.0 to i64, !dbg !16
  %arrayidx = getelementptr inbounds i8, i8* %text, i64 %idxprom, !dbg !16
  %0 = load i8, i8* %arrayidx, align 1, !dbg !16
  %conv = sext i8 %0 to i32, !dbg !16
  %cmp1 = icmp sge i32 %conv, 97, !dbg !17
  %conv2 = zext i1 %cmp1 to i32, !dbg !17
  %idxprom3 = sext i32 %i.0 to i64, !dbg !18
  %arrayidx4 = getelementptr inbounds i8, i8* %text, i64 %idxprom3, !dbg !18
  %1 = load i8, i8* %arrayidx4, align 1, !dbg !18
  %conv5 = sext i8 %1 to i32, !dbg !18
  %cmp6 = icmp sle i32 %conv5, 122, !dbg !19
  %conv7 = zext i1 %cmp6 to i32, !dbg !19
  %and = and i32 %conv2, %conv7, !dbg !20
  %tobool = icmp ne i32 %and, 0, !dbg !20
  br i1 %tobool, label %if.then, label %if.end, !dbg !21

if.then:                                          ; preds = %for.body
  %idxprom8 = sext i32 %i.0 to i64, !dbg !22
  %arrayidx9 = getelementptr inbounds i8, i8* %text, i64 %idxprom8, !dbg !22
  %2 = load i8, i8* %arrayidx9, align 1, !dbg !22
  %conv10 = sext i8 %2 to i32, !dbg !22
  %sub = sub nsw i32 %conv10, 97, !dbg !23
  %add = add nsw i32 %sub, 65, !dbg !24
  %conv11 = trunc i32 %add to i8, !dbg !22
  %idxprom12 = sext i32 %i.0 to i64, !dbg !25
  %arrayidx13 = getelementptr inbounds i8, i8* %text, i64 %idxprom12, !dbg !25
  store i8 %conv11, i8* %arrayidx13, align 1, !dbg !26
  br label %if.end, !dbg !27

if.end:                                           ; preds = %if.then, %for.body
  call void @klee_close_merge(), !dbg !28
  %inc = add nsw i32 %i.0, 1, !dbg !29
  br label %for.cond, !dbg !14, !llvm.loop !30

for.end:                                          ; preds = %for.cond
  ret void, !dbg !33
}

declare dso_local void @klee_open_merge() #1

declare dso_local void @klee_close_merge() #1

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !34 {
entry:
  %conv = sext i32 50 to i64, !dbg !35
  %mul = mul i64 %conv, 1, !dbg !36
  %call = call noalias align 16 i8* @malloc(i64 %mul) #3, !dbg !37
  %conv1 = sext i32 50 to i64, !dbg !38
  %mul2 = mul i64 %conv1, 1, !dbg !39
  call void @klee_make_symbolic(i8* %call, i64 %mul2, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0)), !dbg !40
  call void @to_upper(i8* %call, i32 50), !dbg !41
  ret i32 0, !dbg !42
}

; Function Attrs: nounwind
declare dso_local noalias align 16 i8* @malloc(i64) #2

declare dso_local void @klee_make_symbolic(i8*, i64, i8*) #1

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nounwind "frame-pointer"="all" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
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
!15 = !DILocation(line: 8, column: 5, scope: !8)
!16 = !DILocation(line: 10, column: 10, scope: !8)
!17 = !DILocation(line: 10, column: 18, scope: !8)
!18 = !DILocation(line: 10, column: 29, scope: !8)
!19 = !DILocation(line: 10, column: 37, scope: !8)
!20 = !DILocation(line: 10, column: 26, scope: !8)
!21 = !DILocation(line: 10, column: 9, scope: !8)
!22 = !DILocation(line: 11, column: 17, scope: !8)
!23 = !DILocation(line: 11, column: 25, scope: !8)
!24 = !DILocation(line: 11, column: 31, scope: !8)
!25 = !DILocation(line: 11, column: 7, scope: !8)
!26 = !DILocation(line: 11, column: 15, scope: !8)
!27 = !DILocation(line: 12, column: 5, scope: !8)
!28 = !DILocation(line: 14, column: 5, scope: !8)
!29 = !DILocation(line: 6, column: 27, scope: !8)
!30 = distinct !{!30, !14, !31, !32}
!31 = !DILocation(line: 16, column: 3, scope: !8)
!32 = !{!"llvm.loop.mustprogress"}
!33 = !DILocation(line: 17, column: 1, scope: !8)
!34 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 63, type: !9, scopeLine: 63, spFlags: DISPFlagDefinition, unit: !0)
!35 = !DILocation(line: 65, column: 30, scope: !34)
!36 = !DILocation(line: 65, column: 31, scope: !34)
!37 = !DILocation(line: 65, column: 23, scope: !34)
!38 = !DILocation(line: 67, column: 28, scope: !34)
!39 = !DILocation(line: 67, column: 29, scope: !34)
!40 = !DILocation(line: 67, column: 3, scope: !34)
!41 = !DILocation(line: 69, column: 3, scope: !34)
!42 = !DILocation(line: 78, column: 3, scope: !34)
