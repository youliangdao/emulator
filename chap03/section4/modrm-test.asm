BITS 32
  org 0x7c00
  mov eax, 41
  mov ebp, esp
  mov dword [ebp+4], 5
  jmp 0