	.file	"asm-impl.c"
	.text
	.globl	asm_add
	.type	asm_add, @function
asm_add:
.LFB11:
	.cfi_startproc
#APP
# 7 "asm-impl.c" 1
	addq %rdi,  %rsi
movq %rsi,  %rax

# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE11:
	.size	asm_add, .-asm_add
	.globl	asm_popcnt
	.type	asm_popcnt, @function
asm_popcnt:
.LFB12:
	.cfi_startproc
#APP
# 25 "asm-impl.c" 1
	movl     $0x0,     %ecx
jmp      .L_cmp
.L_loop: mov %rdi,   %rax
sub      $0x1,     %rax
and      %rax,    %rdi
addl     $0x1,     %ecx
.L_cmp:  test  %rdi, %rdi
jnz      .L_loop

# 0 "" 2
#NO_APP
	movl	%ecx, %eax
	ret
	.cfi_endproc
.LFE12:
	.size	asm_popcnt, .-asm_popcnt
	.globl	asm_memcpy
	.type	asm_memcpy, @function
asm_memcpy:
.LFB13:
	.cfi_startproc
	movq	%rdi, %rax
	movq	%rdx, %rcx
#APP
# 42 "asm-impl.c" 1
	.L_n_ZERO: test %rcx,  %rcx
je         .L_ret
mov        (%rsi),     %rdx
mov        %rdx,    (%rdi)
inc        %rdi
inc        %rsi
dec        %rcx
jmp        .L_n_ZERO
.L_ret:

# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE13:
	.size	asm_memcpy, .-asm_memcpy
	.globl	asm_setjmp
	.type	asm_setjmp, @function
asm_setjmp:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
#APP
# 71 "asm-impl.c" 1
	movq    %rbx,      0(%rdi)
movq    8(%rsp),   %rdx
movq    %rdx,      8(%rdi)
movq    %r12,      16(%rdi)
movq    %r13,      24(%rdi)
movq    %r14,      32(%rdi)
movq    %r15,      40(%rdi)
lea     0x10(%rsp),%rdx
movq    %rdx,      48(%rdi)
movq    0(%rsp),   %rdx
movq    %rdx,      56(%rdi)
mov     $0,         %eax

# 0 "" 2
#NO_APP
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE14:
	.size	asm_setjmp, .-asm_setjmp
	.globl	asm_longjmp
	.type	asm_longjmp, @function
asm_longjmp:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
#APP
# 106 "asm-impl.c" 1
	movq    (%rdi),    %rbx
movq    16(%rdi),  %r12
movq    24(%rdi),  %r13
movq    32(%rdi),  %r14
movq    40(%rdi),  %r15
movq    48(%rdi),  %rsp
movq    56(%rdi),  %rbp
movl    %esi,      %eax
jmpq    *8(%rdi)

# 0 "" 2
#NO_APP
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE15:
	.size	asm_longjmp, .-asm_longjmp
	.ident	"GCC: (Debian 7.4.0-6) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
