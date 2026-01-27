; ModuleID = '<stdin>'
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
  call void @llvm.dbg.value(metadata i8* %text, metadata !16, metadata !DIExpression()), !dbg !17
  call void @llvm.dbg.value(metadata i32 %n, metadata !18, metadata !DIExpression()), !dbg !17
  call void @llvm.dbg.value(metadata i32 0, metadata !19, metadata !DIExpression()), !dbg !21
  br label %for.cond, !dbg !22

for.cond:                                         ; preds = %for.inc, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ], !dbg !21
  call void @llvm.dbg.value(metadata i32 %i.0, metadata !19, metadata !DIExpression()), !dbg !21
  %cmp = icmp slt i32 %i.0, %n, !dbg !23
  br i1 %cmp, label %for.body, label %for.end, !dbg !25

for.body:                                         ; preds = %for.cond
  call void @klee_open_merge(), !dbg !26
  %idxprom = sext i32 %i.0 to i64, !dbg !28
  %arrayidx = getelementptr inbounds i8, i8* %text, i64 %idxprom, !dbg !28
  %0 = load i8, i8* %arrayidx, align 1, !dbg !28
  %conv = sext i8 %0 to i32, !dbg !28
  %cmp1 = icmp sge i32 %conv, 97, !dbg !30
  %conv2 = zext i1 %cmp1 to i32, !dbg !30
  %idxprom3 = sext i32 %i.0 to i64, !dbg !31
  %arrayidx4 = getelementptr inbounds i8, i8* %text, i64 %idxprom3, !dbg !31
  %1 = load i8, i8* %arrayidx4, align 1, !dbg !31
  %conv5 = sext i8 %1 to i32, !dbg !31
  %cmp6 = icmp sle i32 %conv5, 122, !dbg !32
  %conv7 = zext i1 %cmp6 to i32, !dbg !32
  %and = and i32 %conv2, %conv7, !dbg !33
  %tobool = icmp ne i32 %and, 0, !dbg !33
  br i1 %tobool, label %if.then, label %if.end, !dbg !34

if.then:                                          ; preds = %for.body
  %idxprom8 = sext i32 %i.0 to i64, !dbg !35
  %arrayidx9 = getelementptr inbounds i8, i8* %text, i64 %idxprom8, !dbg !35
  %2 = load i8, i8* %arrayidx9, align 1, !dbg !35
  %conv10 = sext i8 %2 to i32, !dbg !35
  %sub = sub nsw i32 %conv10, 97, !dbg !37
  %add = add nsw i32 %sub, 65, !dbg !38
  %conv11 = trunc i32 %add to i8, !dbg !35
  %idxprom12 = sext i32 %i.0 to i64, !dbg !39
  %arrayidx13 = getelementptr inbounds i8, i8* %text, i64 %idxprom12, !dbg !39
  store i8 %conv11, i8* %arrayidx13, align 1, !dbg !40
  br label %if.end, !dbg !41

if.end:                                           ; preds = %if.then, %for.body
  call void @klee_close_merge(), !dbg !42
  br label %for.inc, !dbg !43

for.inc:                                          ; preds = %if.end
  %inc = add nsw i32 %i.0, 1, !dbg !44
  call void @llvm.dbg.value(metadata i32 %inc, metadata !19, metadata !DIExpression()), !dbg !21
  br label %for.cond, !dbg !45, !llvm.loop !46

for.end:                                          ; preds = %for.cond
  ret void, !dbg !49
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare dso_local void @klee_open_merge() #2

declare dso_local void @klee_close_merge() #2

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 !dbg !50 {
entry:
  call void @llvm.dbg.value(metadata i32 100, metadata !53, metadata !DIExpression()), !dbg !54
  %conv = sext i32 100 to i64, !dbg !55
  %mul = mul i64 %conv, 1, !dbg !56
  %call = call noalias align 16 i8* @malloc(i64 %mul) #4, !dbg !57
  call void @llvm.dbg.value(metadata i8* %call, metadata !58, metadata !DIExpression()), !dbg !54
  %conv1 = sext i32 100 to i64, !dbg !59
  %mul2 = mul i64 %conv1, 1, !dbg !60
  call void @klee_make_symbolic(i8* %call, i64 %mul2, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0)), !dbg !61
  call void @to_upper(i8* %call, i32 100), !dbg !62
  call void @llvm.dbg.value(metadata i32 0, metadata !63, metadata !DIExpression()), !dbg !65
  br label %for.cond, !dbg !66

for.cond:                                         ; preds = %for.inc, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ], !dbg !65
  call void @llvm.dbg.value(metadata i32 %i.0, metadata !63, metadata !DIExpression()), !dbg !65
  %cmp = icmp slt i32 %i.0, 100, !dbg !67
  br i1 %cmp, label %for.body, label %for.end, !dbg !69

for.body:                                         ; preds = %for.cond
  %idxprom = sext i32 %i.0 to i64, !dbg !70
  %arrayidx = getelementptr inbounds i8, i8* %call, i64 %idxprom, !dbg !70
  %0 = load i8, i8* %arrayidx, align 1, !dbg !70
  %conv4 = sext i8 %0 to i32, !dbg !70
  %cmp5 = icmp sge i32 %conv4, 97, !dbg !70
  %conv6 = zext i1 %cmp5 to i32, !dbg !70
  %idxprom7 = sext i32 %i.0 to i64, !dbg !70
  %arrayidx8 = getelementptr inbounds i8, i8* %call, i64 %idxprom7, !dbg !70
  %1 = load i8, i8* %arrayidx8, align 1, !dbg !70
  %conv9 = sext i8 %1 to i32, !dbg !70
  %cmp10 = icmp sle i32 %conv9, 122, !dbg !70
  %conv11 = zext i1 %cmp10 to i32, !dbg !70
  %and = and i32 %conv6, %conv11, !dbg !70
  %tobool = icmp ne i32 %and, 0, !dbg !70
  br i1 %tobool, label %cond.false, label %cond.true, !dbg !70

cond.true:                                        ; preds = %for.body
  br label %cond.end, !dbg !70

cond.false:                                       ; preds = %for.body
  %call12 = call i32 (i8*, i8*, i32, i8*, ...) bitcast (i32 (...)* @__assert_fail to i32 (i8*, i8*, i32, i8*, ...)*)(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.1, i64 0, i64 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.2, i64 0, i64 0), i32 74, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @__PRETTY_FUNCTION__.main, i64 0, i64 0)), !dbg !70
  br label %cond.end, !dbg !70

cond.end:                                         ; preds = %cond.false, %cond.true
  br label %for.inc, !dbg !70

for.inc:                                          ; preds = %cond.end
  %inc = add nsw i32 %i.0, 1, !dbg !71
  call void @llvm.dbg.value(metadata i32 %inc, metadata !63, metadata !DIExpression()), !dbg !65
  br label %for.cond, !dbg !72, !llvm.loop !73

for.end:                                          ; preds = %for.cond
  %call13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.3, i64 0, i64 0)), !dbg !75
  ret i32 0, !dbg !76
}

; Function Attrs: nounwind
declare dso_local noalias align 16 i8* @malloc(i64) #3

declare dso_local void @klee_make_symbolic(i8*, i64, i8*) #2

declare dso_local i32 @__assert_fail(...) #2

declare dso_local i32 @printf(i8*, ...) #2

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

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
!17 = !DILocation(line: 0, scope: !12)
!18 = !DILocalVariable(name: "n", arg: 2, scope: !12, file: !1, line: 5, type: !15)
!19 = !DILocalVariable(name: "i", scope: !20, file: !1, line: 6, type: !15)
!20 = distinct !DILexicalBlock(scope: !12, file: !1, line: 6, column: 3)
!21 = !DILocation(line: 0, scope: !20)
!22 = !DILocation(line: 6, column: 8, scope: !20)
!23 = !DILocation(line: 6, column: 21, scope: !24)
!24 = distinct !DILexicalBlock(scope: !20, file: !1, line: 6, column: 3)
!25 = !DILocation(line: 6, column: 3, scope: !20)
!26 = !DILocation(line: 8, column: 5, scope: !27)
!27 = distinct !DILexicalBlock(scope: !24, file: !1, line: 6, column: 31)
!28 = !DILocation(line: 10, column: 10, scope: !29)
!29 = distinct !DILexicalBlock(scope: !27, file: !1, line: 10, column: 9)
!30 = !DILocation(line: 10, column: 18, scope: !29)
!31 = !DILocation(line: 10, column: 29, scope: !29)
!32 = !DILocation(line: 10, column: 37, scope: !29)
!33 = !DILocation(line: 10, column: 26, scope: !29)
!34 = !DILocation(line: 10, column: 9, scope: !27)
!35 = !DILocation(line: 11, column: 17, scope: !36)
!36 = distinct !DILexicalBlock(scope: !29, file: !1, line: 10, column: 46)
!37 = !DILocation(line: 11, column: 25, scope: !36)
!38 = !DILocation(line: 11, column: 31, scope: !36)
!39 = !DILocation(line: 11, column: 7, scope: !36)
!40 = !DILocation(line: 11, column: 15, scope: !36)
!41 = !DILocation(line: 12, column: 5, scope: !36)
!42 = !DILocation(line: 14, column: 5, scope: !27)
!43 = !DILocation(line: 16, column: 3, scope: !27)
!44 = !DILocation(line: 6, column: 27, scope: !24)
!45 = !DILocation(line: 6, column: 3, scope: !24)
!46 = distinct !{!46, !25, !47, !48}
!47 = !DILocation(line: 16, column: 3, scope: !20)
!48 = !{!"llvm.loop.mustprogress"}
!49 = !DILocation(line: 17, column: 1, scope: !12)
!50 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 63, type: !51, scopeLine: 63, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!51 = !DISubroutineType(types: !52)
!52 = !{!15}
!53 = !DILocalVariable(name: "n", scope: !50, file: !1, line: 64, type: !15)
!54 = !DILocation(line: 0, scope: !50)
!55 = !DILocation(line: 65, column: 30, scope: !50)
!56 = !DILocation(line: 65, column: 31, scope: !50)
!57 = !DILocation(line: 65, column: 23, scope: !50)
!58 = !DILocalVariable(name: "text", scope: !50, file: !1, line: 65, type: !4)
!59 = !DILocation(line: 67, column: 28, scope: !50)
!60 = !DILocation(line: 67, column: 29, scope: !50)
!61 = !DILocation(line: 67, column: 3, scope: !50)
!62 = !DILocation(line: 69, column: 3, scope: !50)
!63 = !DILocalVariable(name: "i", scope: !64, file: !1, line: 73, type: !15)
!64 = distinct !DILexicalBlock(scope: !50, file: !1, line: 73, column: 3)
!65 = !DILocation(line: 0, scope: !64)
!66 = !DILocation(line: 73, column: 8, scope: !64)
!67 = !DILocation(line: 73, column: 21, scope: !68)
!68 = distinct !DILexicalBlock(scope: !64, file: !1, line: 73, column: 3)
!69 = !DILocation(line: 73, column: 3, scope: !64)
!70 = !DILocation(line: 74, column: 5, scope: !68)
!71 = !DILocation(line: 73, column: 27, scope: !68)
!72 = !DILocation(line: 73, column: 3, scope: !68)
!73 = distinct !{!73, !69, !74, !48}
!74 = !DILocation(line: 74, column: 5, scope: !64)
!75 = !DILocation(line: 75, column: 3, scope: !50)
!76 = !DILocation(line: 78, column: 3, scope: !50)
