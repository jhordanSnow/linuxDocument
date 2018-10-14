section .data
message: db "Hello, World", 10

global line
extern plot

section .text

; rdi = x0
; rsi = y0
; rdx = x1
; rcx = y1

; diffX = r15
; diffY = r14
; movX = r13
; movY = r12
; err = r11
; errTmp = r10

line:

; ------------- DiffX y MovX-------------------
  cmp rdi, rdx
  jae diffXNegativo
  mov r15, rdx
  sub r15, rdi

  mov r13, 1
  jmp endIfDiffX

diffXNegativo:
  mov r15, rdi
  sub r15, rdx

  mov r13, -1
endIfDiffX:

; ------------- DiffY y MovY ------------------

  cmp rsi, rcx
  jae diffYNegativo
  mov r14, rcx
  sub r14, rsi

  mov r12, 1
  jmp endIfDiffY

diffYNegativo:
  mov r14, rsi
  sub r14, rcx

  mov r12, -1
endIfDiffY:

; ------------- errVar ------------------

  cmp r15, r14
  jl errDffY
  mov r11, r15

  jmp endIfErr

errDffY:
  push rax
  push rdx

  mov rax, -1
  mul r14

  mov r11, rax

  pop rdx
  pop rax
endIfErr:

;---------------------------------

  xor r10, r10
  shl r15, 1
  shl r14, 1

startLoop:

  cmp rdx, rdi
  jne bodyLoop

  cmp rcx, rsi
  je endLoop
bodyLoop:
  ; ------------- plot--------------

  push r12
  push r11
  push r10
  push rdx
  push rcx
  push rdi
  push rsi

  call plot

  pop rsi
  pop rdi
  pop rcx
  pop rdx
  pop r10
  pop r11
  pop r12

  mov r10, r11

; ---------------------------------------------
  cmp r10, r14
  jg endIfErrY

  add r11, r15
  add rsi, r12

endIfErrY:
; -------------------------------------------------

; ---------------------------------------------
  push rax
  push rdx
  mov rax, -1
  mul r10
  mov r10, rax
  pop rdx
  pop rax

  cmp r10, r15
  jg endIfErrX

  sub r11, r14
  add rdi, r13

endIfErrX:
; -------------------------------------------------

  jmp startLoop
endLoop:

  push r12
  push r11
  push r10
  push rdx
  push rcx
  push rdi
  push rsi

  call plot

  pop rsi
  pop rdi
  pop rcx
  pop rdx
  pop r10
  pop r11
  pop r12

  ret
