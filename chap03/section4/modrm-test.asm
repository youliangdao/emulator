BITS 32
  org 0x7c00
  mov eax, 2
  mov ebp, esp
  mov dword [ebp+4], 5
  add dword [ebp+4], eax
  mov esi, [ebp+4]
  jmp 0