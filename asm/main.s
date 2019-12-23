	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"main.c"
.LC1:
	.string	"head->str != NULL"
.LC2:
	.string	"strcmp(head->str, str) == 0"
.LC3:
	.string	"head->value == value"
	.text
	.type	setjmp_log, @function
setjmp_log:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, %rax
	movq	head(%rip), %rbx
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	je	.L6
	movl	%esi, %ebp
	movq	%rax, %rsi
	call	strcmp@PLT
	testl	%eax, %eax
	jne	.L7
	cmpl	%ebp, 8(%rbx)
	jne	.L8
	addq	$16, %rbx
	movq	%rbx, head(%rip)
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L6:
	.cfi_restore_state
	leaq	__PRETTY_FUNCTION__.3614(%rip), %rcx
	movl	$64, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC1(%rip), %rdi
	call	__assert_fail@PLT
.L7:
	leaq	__PRETTY_FUNCTION__.3614(%rip), %rcx
	movl	$65, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC2(%rip), %rdi
	call	__assert_fail@PLT
.L8:
	leaq	__PRETTY_FUNCTION__.3614(%rip), %rcx
	movl	$66, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC3(%rip), %rdi
	call	__assert_fail@PLT
	.cfi_endproc
.LFE23:
	.size	setjmp_log, .-setjmp_log
	.section	.rodata.str1.1
.LC4:
	.string	"asm_add(1, 2) == 3"
.LC5:
	.string	"asm_add(123,456)== 579"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC6:
	.string	"asm_popcnt(0b1111111111000000000011111000000000000000111111111100000000001111) == 29"
	.align 8
.LC7:
	.string	"asm_popcnt(0xfffffffffffffff0ull) == 60"
	.align 8
.LC8:
	.string	"asm_popcnt(0xffffffffffffffffull) == 64"
	.align 8
.LC9:
	.string	"YEAH, PASS TEST ADD and POPCNT!"
	.section	.rodata.str1.1
.LC10:
	.string	"The first NJU!!!"
.LC11:
	.string	"NJU"
.LC12:
	.string	"strcmp(dest1,test1)==0"
.LC13:
	.string	"The first"
.LC14:
	.string	"strcmp(dest2,test2)==0"
	.section	.rodata.str1.8
	.align 8
.LC15:
	.string	"asm_memcpy(NULL, NULL, 0) == NULL"
	.section	.rodata.str1.1
.LC16:
	.string	"YEAH, PASS TEST MEMCPY!"
.LC17:
	.string	"A"
.LC18:
	.string	"B"
.LC19:
	.string	"YEAH, PASS JMP TEST0!"
.LC20:
	.string	"A1"
.LC21:
	.string	"B1"
.LC22:
	.string	"B2"
.LC23:
	.string	"B3"
.LC24:
	.string	"A2"
.LC25:
	.string	"A3"
.LC26:
	.string	"A4"
.LC27:
	.string	"head->str == NULL"
.LC28:
	.string	"YEAH, PASS JMP TEST1!"
.LC29:
	.string	"YEAH, FINISH THE TEST!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$72, %rsp
	.cfi_def_cfa_offset 96
	movl	$2, %esi
	movl	$1, %edi
	call	asm_add@PLT
	cmpq	$3, %rax
	jne	.L26
	movl	$456, %esi
	movl	$123, %edi
	call	asm_add@PLT
	cmpq	$579, %rax
	jne	.L27
	movabsq	$-17997356062490609, %rdi
	call	asm_popcnt@PLT
	cmpl	$29, %eax
	jne	.L28
	movq	$-16, %rdi
	call	asm_popcnt@PLT
	cmpl	$60, %eax
	jne	.L29
	movq	$-1, %rdi
	call	asm_popcnt@PLT
	cmpl	$64, %eax
	jne	.L30
	leaq	.LC9(%rip), %rdi
	call	puts@PLT
	leaq	32(%rsp), %rbx
	movl	$3, %edx
	leaq	10+.LC10(%rip), %rsi
	movq	%rbx, %rdi
	call	asm_memcpy@PLT
	movq	%rsp, %rdi
	movl	$9, %edx
	leaq	.LC10(%rip), %rsi
	call	asm_memcpy@PLT
	movb	$0, 35(%rsp)
	movb	$0, 9(%rsp)
	movl	$4, %ecx
	leaq	.LC11(%rip), %rdi
	movq	%rbx, %rsi
	repz cmpsb
	seta	%al
	sbbb	$0, %al
	testb	%al, %al
	jne	.L31
	movq	%rsp, %rsi
	movl	$10, %ecx
	leaq	.LC13(%rip), %rdi
	repz cmpsb
	seta	%al
	sbbb	$0, %al
	testb	%al, %al
	jne	.L32
	movq	%rsp, %rdi
	call	puts@PLT
	leaq	32(%rsp), %rdi
	call	puts@PLT
	leaq	.LC10(%rip), %rdi
	call	puts@PLT
	movl	$0, %edx
	movl	$0, %esi
	movl	$0, %edi
	call	asm_memcpy@PLT
	testq	%rax, %rax
	jne	.L33
	leaq	.LC16(%rip), %rdi
	call	puts@PLT
	leaq	buf(%rip), %rdi
	call	asm_setjmp@PLT
	movl	%eax, %ebx
	testl	%eax, %eax
	je	.L34
.L18:
	movl	%ebx, %esi
	leaq	.LC18(%rip), %rdi
	call	setjmp_log
	leaq	.LC19(%rip), %rdi
	call	puts@PLT
	movl	$0, %esi
	leaq	.LC20(%rip), %rdi
	call	setjmp_log
	leaq	bufferA(%rip), %rdi
	call	asm_setjmp@PLT
	movl	%eax, %ebx
	testl	%eax, %eax
	je	.L35
.L19:
	movl	%ebx, %esi
	leaq	.LC24(%rip), %rdi
	call	setjmp_log
	leaq	bufferA(%rip), %rdi
	call	asm_setjmp@PLT
	movl	%eax, %ebx
	testl	%eax, %eax
	je	.L36
.L22:
	movl	%ebx, %esi
	leaq	.LC25(%rip), %rdi
	call	setjmp_log
	leaq	bufferA(%rip), %rdi
	call	asm_setjmp@PLT
	movl	%eax, %ebx
	testl	%eax, %eax
	je	.L37
.L23:
	movl	%ebx, %esi
	leaq	.LC26(%rip), %rdi
	call	setjmp_log
	movq	head(%rip), %rax
	cmpq	$0, (%rax)
	jne	.L38
	leaq	.LC28(%rip), %rdi
	call	puts@PLT
	leaq	.LC29(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L26:
	.cfi_restore_state
	leaq	__PRETTY_FUNCTION__.3597(%rip), %rcx
	movl	$12, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC4(%rip), %rdi
	call	__assert_fail@PLT
.L27:
	leaq	__PRETTY_FUNCTION__.3597(%rip), %rcx
	movl	$13, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC5(%rip), %rdi
	call	__assert_fail@PLT
.L28:
	leaq	__PRETTY_FUNCTION__.3597(%rip), %rcx
	movl	$14, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC6(%rip), %rdi
	call	__assert_fail@PLT
.L29:
	leaq	__PRETTY_FUNCTION__.3597(%rip), %rcx
	movl	$15, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC7(%rip), %rdi
	call	__assert_fail@PLT
.L30:
	leaq	__PRETTY_FUNCTION__.3597(%rip), %rcx
	movl	$16, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC8(%rip), %rdi
	call	__assert_fail@PLT
.L31:
	leaq	__PRETTY_FUNCTION__.3597(%rip), %rcx
	movl	$29, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC12(%rip), %rdi
	call	__assert_fail@PLT
.L32:
	leaq	__PRETTY_FUNCTION__.3597(%rip), %rcx
	movl	$30, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC14(%rip), %rdi
	call	__assert_fail@PLT
.L33:
	leaq	__PRETTY_FUNCTION__.3597(%rip), %rcx
	movl	$34, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC15(%rip), %rdi
	call	__assert_fail@PLT
.L34:
	movl	$0, %esi
	leaq	.LC17(%rip), %rdi
	call	setjmp_log
	movl	$999, %esi
	leaq	buf(%rip), %rdi
	call	asm_longjmp@PLT
	jmp	.L18
.L35:
	movl	$0, %esi
	leaq	.LC21(%rip), %rdi
	call	setjmp_log
	leaq	bufferB(%rip), %rdi
	call	asm_setjmp@PLT
	movl	%eax, %ebp
	testl	%eax, %eax
	je	.L39
.L20:
	movl	%ebp, %esi
	leaq	.LC22(%rip), %rdi
	call	setjmp_log
	leaq	bufferB(%rip), %rdi
	call	asm_setjmp@PLT
	movl	%eax, %ebp
	testl	%eax, %eax
	je	.L40
.L21:
	movl	%ebp, %esi
	leaq	.LC23(%rip), %rdi
	call	setjmp_log
	leaq	bufferB(%rip), %rdi
	call	asm_setjmp@PLT
	testl	%eax, %eax
	jne	.L19
	movl	$10003, %esi
	leaq	bufferA(%rip), %rdi
	call	asm_longjmp@PLT
	jmp	.L19
.L39:
	movl	$10001, %esi
	leaq	bufferA(%rip), %rdi
	call	asm_longjmp@PLT
	jmp	.L20
.L40:
	movl	$10002, %esi
	leaq	bufferA(%rip), %rdi
	call	asm_longjmp@PLT
	jmp	.L21
.L36:
	movl	$20001, %esi
	leaq	bufferB(%rip), %rdi
	call	asm_longjmp@PLT
	jmp	.L22
.L37:
	movl	$20002, %esi
	leaq	bufferB(%rip), %rdi
	call	asm_longjmp@PLT
	jmp	.L23
.L38:
	leaq	__PRETTY_FUNCTION__.3619(%rip), %rcx
	movl	$86, %edx
	leaq	.LC0(%rip), %rsi
	leaq	.LC27(%rip), %rdi
	call	__assert_fail@PLT
	.cfi_endproc
.LFE22:
	.size	main, .-main
	.section	.rodata
	.align 8
	.type	__PRETTY_FUNCTION__.3619, @object
	.size	__PRETTY_FUNCTION__.3619, 13
__PRETTY_FUNCTION__.3619:
	.string	"setjmp_test1"
	.align 8
	.type	__PRETTY_FUNCTION__.3614, @object
	.size	__PRETTY_FUNCTION__.3614, 11
__PRETTY_FUNCTION__.3614:
	.string	"setjmp_log"
	.type	__PRETTY_FUNCTION__.3597, @object
	.size	__PRETTY_FUNCTION__.3597, 5
__PRETTY_FUNCTION__.3597:
	.string	"main"
	.local	buf
	.comm	buf,64,32
	.section	.data.rel.local,"aw",@progbits
	.align 8
	.type	head, @object
	.size	head, 8
head:
	.quad	expected
	.align 32
	.type	expected, @object
	.size	expected, 160
expected:
	.quad	.LC17
	.long	0
	.zero	4
	.quad	.LC18
	.long	999
	.zero	4
	.quad	.LC20
	.long	0
	.zero	4
	.quad	.LC21
	.long	0
	.zero	4
	.quad	.LC24
	.long	10001
	.zero	4
	.quad	.LC22
	.long	20001
	.zero	4
	.quad	.LC25
	.long	10002
	.zero	4
	.quad	.LC23
	.long	20002
	.zero	4
	.quad	.LC26
	.long	10003
	.zero	4
	.quad	0
	.long	0
	.zero	4
	.local	bufferB
	.comm	bufferB,64,32
	.local	bufferA
	.comm	bufferA,64,32
	.ident	"GCC: (Debian 7.4.0-6) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
