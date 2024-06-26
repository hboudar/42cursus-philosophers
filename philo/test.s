	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 6
	.globl	_thread_routine         ## -- Begin function thread_routine
	.p2align	4, 0x90
_thread_routine:                        ## @thread_routine
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	%rax, -16(%rbp)
	movl	$0, -20(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	cmpl	$21000, -20(%rbp)       ## imm = 0x5208
	jae	LBB0_3
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-16(%rbp), %rdi
	callq	_pthread_mutex_lock
	movq	-16(%rbp), %rcx
	movl	64(%rcx), %edx
	addl	$1, %edx
	movl	%edx, 64(%rcx)
	movq	-16(%rbp), %rdi
	movl	%eax, -24(%rbp)         ## 4-byte Spill
	callq	_pthread_mutex_unlock
	movl	-20(%rbp), %edx
	addl	$1, %edx
	movl	%edx, -20(%rbp)
	jmp	LBB0_1
LBB0_3:
	movq	-16(%rbp), %rdi
	callq	_pthread_mutex_lock
	movq	-16(%rbp), %rdi
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	callq	_pthread_mutex_unlock
	xorl	%ecx, %ecx
	movl	%ecx, %edx
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	movq	%rdx, %rax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$128, %rsp
	xorl	%eax, %eax
	movl	%eax, %esi
	leaq	-80(%rbp), %rdi
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	%rcx, -8(%rbp)
	movl	$0, -84(%rbp)
	movl	$0, -16(%rbp)
	callq	_pthread_mutex_init
	xorl	%edx, %edx
	movl	%edx, %esi
	leaq	-80(%rbp), %rcx
	leaq	-96(%rbp), %rdi
	leaq	_thread_routine(%rip), %rdx
	movl	%eax, -108(%rbp)        ## 4-byte Spill
	callq	_pthread_create
	xorl	%r8d, %r8d
	movl	%r8d, %esi
	leaq	-80(%rbp), %rcx
	leaq	-104(%rbp), %rdi
	leaq	_thread_routine(%rip), %rdx
	movl	%eax, -112(%rbp)        ## 4-byte Spill
	callq	_pthread_create
	xorl	%r8d, %r8d
	movl	%r8d, %esi
	movq	-96(%rbp), %rdi
	movl	%eax, -116(%rbp)        ## 4-byte Spill
	callq	_pthread_join
	xorl	%r8d, %r8d
	movl	%r8d, %esi
	movq	-104(%rbp), %rdi
	movl	%eax, -120(%rbp)        ## 4-byte Spill
	callq	_pthread_join
	movl	-16(%rbp), %esi
	leaq	L_.str(%rip), %rdi
	movl	%eax, -124(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	-80(%rbp), %rdi
	movl	%eax, -128(%rbp)        ## 4-byte Spill
	callq	_pthread_mutex_destroy
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rdx
	cmpq	%rdx, %rcx
	jne	LBB1_2
## %bb.1:
	xorl	%eax, %eax
	addq	$128, %rsp
	popq	%rbp
	retq
LBB1_2:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Main: OK. Total count is %u\n"

.subsections_via_symbols
