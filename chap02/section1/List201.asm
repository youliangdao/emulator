
List201.o:	file format Mach-O 64-bit x86-64


Disassembly of section __TEXT,__text:

0000000000000000 _main:
; {
       0: 55                           	pushq	%rbp
       1: 48 89 e5                     	movq	%rsp, %rbp
       4: c7 45 fc 00 00 00 00         	movl	$0, -4(%rbp)
;   int sum = 0;
       b: c7 45 f8 00 00 00 00         	movl	$0, -8(%rbp)
;   for (int i = 0; i < 10; i++)
      12: c7 45 f4 00 00 00 00         	movl	$0, -12(%rbp)
      19: 83 7d f4 0a                  	cmpl	$10, -12(%rbp)
      1d: 0f 8d 17 00 00 00            	jge	23 <_main+0x3a>
;     sum += 1;
      23: 8b 45 f8                     	movl	-8(%rbp), %eax
      26: 83 c0 01                     	addl	$1, %eax
      29: 89 45 f8                     	movl	%eax, -8(%rbp)
;   for (int i = 0; i < 10; i++)
      2c: 8b 45 f4                     	movl	-12(%rbp), %eax
      2f: 83 c0 01                     	addl	$1, %eax
      32: 89 45 f4                     	movl	%eax, -12(%rbp)
      35: e9 df ff ff ff               	jmp	-33 <_main+0x19>
      3a: 31 c0                        	xorl	%eax, %eax
;   return 0;
      3c: 5d                           	popq	%rbp
      3d: c3                           	retq
