BITS 32
  org 0x7c00
  extern main
  global start
  start
    call main
    jmp 0
