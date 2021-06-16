BITS 32
  org 0x7c00
start:              ; プログラムの開始
  mov esi, msg
  call puts         ; サブルーチンを呼び出す
  jmp 0
puts:
  mov al, [esi]      ; １文字読み込む
  inc esi
  cmp al, 0
  je puts_end
  mov ah, 0x5e
  mov ebx, 15
  int 0x10          ; BIOSを呼び出す
  jmp puts
puts_end:
  ret               ; サブルーチンから抜ける

msg:
  db "hello, world", 0x0d, 0x0a, 0
