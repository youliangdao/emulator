
List216.o:	file format Mach-O 64-bit x86-64


Disassembly of section __TEXT,__text:

0000000000000000 _func:
       0: 55                           	pushq	%rbp
       1: 48 89 e5                     	movq	%rsp, %rbp
       4: b8 00 01 00 00               	movl	$256, %eax
       9: 48 89 45 f8                  	movq	%rax, -8(%rbp)
       d: 48 8b 45 f8                  	movq	-8(%rbp), %rax
      11: c7 00 29 00 00 00            	movl	$41, (%rax)
      17: 5d                           	popq	%rbp
      18: c3                           	retq
