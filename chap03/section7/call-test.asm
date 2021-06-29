BITS 32
  org 0x7c00
start:
  mov eax, 0x0001
  mov ebx, 0x0009
  call add_routine
  jmp 0
add_routine
  mov ecx, eax
  add ecx, ebx
  ret