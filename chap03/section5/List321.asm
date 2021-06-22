
List321.o:	file format Mach-O 64-bit x86-64


Disassembly of section __TEXT,__text:

0000000000000000 _abs:
       0: 55                           	pushq	%rbp
       1: 48 89 e5                     	movq	%rsp, %rbp
       4: 89 7d f8                     	movl	%edi, -8(%rbp)
       7: 83 7d f8 00                  	cmpl	$0, -8(%rbp)
       b: 0f 8c 0b 00 00 00            	jl	11 <_abs+0x1c>
      11: 8b 45 f8                     	movl	-8(%rbp), %eax
      14: 89 45 fc                     	movl	%eax, -4(%rbp)
      17: e9 08 00 00 00               	jmp	8 <_abs+0x24>
      1c: 31 c0                        	xorl	%eax, %eax
      1e: 2b 45 f8                     	subl	-8(%rbp), %eax
      21: 89 45 fc                     	movl	%eax, -4(%rbp)
      24: 8b 45 fc                     	movl	-4(%rbp), %eax
      27: 5d                           	popq	%rbp
      28: c3                           	retq
      29: 0f 1f 80 00 00 00 00         	nopl	(%rax)

0000000000000030 _main:
      30: 55                           	pushq	%rbp
      31: 48 89 e5                     	movq	%rsp, %rbp
      34: 48 83 ec 10                  	subq	$16, %rsp
      38: c7 45 fc 00 00 00 00         	movl	$0, -4(%rbp)
      3f: bf 01 00 00 00               	movl	$1, %edi
      44: e8 00 00 00 00               	callq	0 <_main+0x19>
      49: 31 c9                        	xorl	%ecx, %ecx
      4b: 89 45 f8                     	movl	%eax, -8(%rbp)
      4e: 89 c8                        	movl	%ecx, %eax
      50: 48 83 c4 10                  	addq	$16, %rsp
      54: 5d                           	popq	%rbp
      55: c3                           	retq
