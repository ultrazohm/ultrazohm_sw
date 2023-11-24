; ModuleID = '/home/hufnagelde/ultrazohm_sw/ip_cores/uz_Matrix_Multi/HLS_Project/solution1/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

; Function Attrs: inaccessiblemem_or_argmemonly noinline
define void @apatb_MatrixMultiplication_ir(float* noalias nocapture nonnull readonly "fpga.decayed.dim.hint"="5" %A, float* noalias nocapture nonnull readonly "fpga.decayed.dim.hint"="25" %B, float* noalias nocapture nonnull "fpga.decayed.dim.hint"="5" %C_out, i64 %A_rows, i64 %B_rows, i64 %B_columns) local_unnamed_addr #0 {
entry:
  %A_copy = alloca [5 x float], align 512
  %B_copy = alloca [25 x float], align 512
  %C_out_copy = alloca [5 x float], align 512
  %0 = bitcast float* %A to [5 x float]*
  %1 = bitcast float* %B to [25 x float]*
  %2 = bitcast float* %C_out to [5 x float]*
  call fastcc void @copy_in([5 x float]* nonnull %0, [5 x float]* nonnull align 512 %A_copy, [25 x float]* nonnull %1, [25 x float]* nonnull align 512 %B_copy, [5 x float]* nonnull %2, [5 x float]* nonnull align 512 %C_out_copy)
  %3 = getelementptr inbounds [5 x float], [5 x float]* %A_copy, i32 0, i32 0
  %4 = getelementptr inbounds [25 x float], [25 x float]* %B_copy, i32 0, i32 0
  %5 = getelementptr inbounds [5 x float], [5 x float]* %C_out_copy, i32 0, i32 0
  call void @apatb_MatrixMultiplication_hw(float* %3, float* %4, float* %5, i64 %A_rows, i64 %B_rows, i64 %B_columns)
  call void @copy_back([5 x float]* %0, [5 x float]* %A_copy, [25 x float]* %1, [25 x float]* %B_copy, [5 x float]* %2, [5 x float]* %C_out_copy)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_in([5 x float]* noalias readonly, [5 x float]* noalias align 512, [25 x float]* noalias readonly, [25 x float]* noalias align 512, [5 x float]* noalias readonly, [5 x float]* noalias align 512) unnamed_addr #1 {
entry:
  call fastcc void @onebyonecpy_hls.p0a5f32([5 x float]* align 512 %1, [5 x float]* %0)
  call fastcc void @onebyonecpy_hls.p0a25f32([25 x float]* align 512 %3, [25 x float]* %2)
  call fastcc void @onebyonecpy_hls.p0a5f32([5 x float]* align 512 %5, [5 x float]* %4)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a5f32([5 x float]* noalias align 512, [5 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [5 x float]* %0, null
  %3 = icmp eq [5 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [5 x float], [5 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [5 x float], [5 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 5
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a25f32([25 x float]* noalias align 512, [25 x float]* noalias readonly) unnamed_addr #2 {
entry:
  %2 = icmp eq [25 x float]* %0, null
  %3 = icmp eq [25 x float]* %1, null
  %4 = or i1 %2, %3
  br i1 %4, label %ret, label %copy

copy:                                             ; preds = %entry
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %copy
  %for.loop.idx1 = phi i64 [ 0, %copy ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [25 x float], [25 x float]* %0, i64 0, i64 %for.loop.idx1
  %src.addr = getelementptr [25 x float], [25 x float]* %1, i64 0, i64 %for.loop.idx1
  %5 = load float, float* %src.addr, align 4
  store float %5, float* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx1, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, 25
  br i1 %exitcond, label %for.loop, label %ret

ret:                                              ; preds = %for.loop, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_out([5 x float]* noalias, [5 x float]* noalias readonly align 512, [25 x float]* noalias, [25 x float]* noalias readonly align 512, [5 x float]* noalias, [5 x float]* noalias readonly align 512) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0a5f32([5 x float]* %0, [5 x float]* align 512 %1)
  call fastcc void @onebyonecpy_hls.p0a25f32([25 x float]* %2, [25 x float]* align 512 %3)
  call fastcc void @onebyonecpy_hls.p0a5f32([5 x float]* %4, [5 x float]* align 512 %5)
  ret void
}

declare void @apatb_MatrixMultiplication_hw(float*, float*, float*, i64, i64, i64)

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @copy_back([5 x float]* noalias, [5 x float]* noalias readonly align 512, [25 x float]* noalias, [25 x float]* noalias readonly align 512, [5 x float]* noalias, [5 x float]* noalias readonly align 512) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0a5f32([5 x float]* %4, [5 x float]* align 512 %5)
  ret void
}

define void @MatrixMultiplication_hw_stub_wrapper(float*, float*, float*, i64, i64, i64) #4 {
entry:
  %6 = bitcast float* %0 to [5 x float]*
  %7 = bitcast float* %1 to [25 x float]*
  %8 = bitcast float* %2 to [5 x float]*
  call void @copy_out([5 x float]* null, [5 x float]* %6, [25 x float]* null, [25 x float]* %7, [5 x float]* null, [5 x float]* %8)
  %9 = bitcast [5 x float]* %6 to float*
  %10 = bitcast [25 x float]* %7 to float*
  %11 = bitcast [5 x float]* %8 to float*
  call void @MatrixMultiplication_hw_stub(float* %9, float* %10, float* %11, i64 %3, i64 %4, i64 %5)
  call void @copy_in([5 x float]* null, [5 x float]* %6, [25 x float]* null, [25 x float]* %7, [5 x float]* null, [5 x float]* %8)
  ret void
}

declare void @MatrixMultiplication_hw_stub(float*, float*, float*, i64, i64, i64)

attributes #0 = { inaccessiblemem_or_argmemonly noinline "fpga.wrapper.func"="wrapper" }
attributes #1 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyin" }
attributes #2 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #3 = { argmemonly noinline norecurse "fpga.wrapper.func"="copyout" }
attributes #4 = { "fpga.wrapper.func"="stub" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
