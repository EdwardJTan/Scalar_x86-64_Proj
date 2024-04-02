section .text
bits 64
Default rel
global stencil_kernel_asm

stencil_kernel_asm:
    mov     rsi, rdi        ; Copy the address of X to RSI
    mov     rdx, rcx        ; Copy the address of Y to RDX
    mov     rcx, rsi        ; Copy the address of X to RCX for loop control
    add     rcx, 3 * 4      ; Move the pointer to X[3]

loop_start:
    movss   xmm0, [rcx-3 * 4 * 4] ; Load X[i-3] to XMM0
    movss   xmm1, [rcx-2 * 4 * 4] ; Load X[i-2] to XMM1
    movss   xmm2, [rcx-1 * 4 * 4] ; Load X[i-1] to XMM2
    movss   xmm3, [rcx]           ; Load X[i] to XMM3
    movss   xmm4, [rcx+1 * 4 * 4] ; Load X[i+1] to XMM4
    movss   xmm5, [rcx+2 * 4 * 4] ; Load X[i+2] to XMM5
    movss   xmm6, [rcx+3 * 4 * 4] ; Load X[i+3] to XMM6
    addss   xmm3, xmm2            ; X[i] + X[i-1]
    addss   xmm3, xmm1            ; X[i] + X[i-1] + X[i-2]
    addss   xmm3, xmm0            ; X[i] + X[i-1] + X[i-2] + X[i-3]
    addss   xmm3, xmm4            ; X[i] + X[i-1] + X[i-2] + X[i-3] + X[i+1]
    addss   xmm3, xmm5            ; X[i] + X[i-1] + X[i-2] + X[i-3] + X[i+1] + X[i+2]
    addss   xmm3, xmm6            ; X[i] + X[i-1] + X[i-2] + X[i-3] + X[i+1] + X[i+2] + X[i+3]
    movss   [rdx], xmm3           ; Store the result in Y[i]

    add     rcx, 4                ; Move to the next element of X
    add     rdx, 4                ; Move to the next element of Y
    cmp     rcx, rsi              ; Compare the current pointer with the end pointer of X
    jne     loop_start            ; Jump to loop_start if not at the end


    ret
