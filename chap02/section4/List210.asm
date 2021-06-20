
List210.o:	file format Mach-O 64-bit x86-64


Disassembly of section __TEXT,__text:

0000000000000000 _func:
       0: 55                           	pushq	%rbp
       1: 48 89 e5                     	movq	%rsp, %rbp
       4: 48 8d 45 fc                  	leaq	-4(%rbp), %rax
       8: 48 89 45 f0                  	movq	%rax, -16(%rbp)
       c: 48 8b 45 f0                  	movq	-16(%rbp), %rax
      10: c7 00 29 00 00 00            	movl	$41, (%rax)
      16: 5d                           	popq	%rbp
      17: c3                           	retq
