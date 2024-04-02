section .data
X dq 2.0

section .text
bits 64
Default rel
global stencil_kernel_asm


stencil_kernel_asm:
    mov r10, rax      
    mov r9, rax     

loop:
    
    cmp r9, r8
    ja end          

    xorps xmm0, xmm0   ; Reset xmm0 to 0
    movsd xmm1, [rcx + r10 * 8 - 8] ; Load num[i - 3] to xmm1
    movsd xmm2, [rcx + r10 * 8]     ; Load num[i - 2] to xmm2
    movsd xmm3, [rcx + r10 * 8 + 8] ; Load num[i - 1] to xmm3
    movsd xmm4, [rcx + r10 * 8 + 16]; Load num[i] to xmm4
    movsd xmm5, [rcx + r10 * 8 + 24]; Load num[i + 1] to xmm5
    movsd xmm6, [rcx + r10 * 8 + 32]; Load num[i + 2] to xmm6
    movsd xmm7, [rcx + r10 * 8 + 40]; Load num[i + 3] to xmm7
    
    

    ; Accumulate sum
    addsd xmm0, xmm1   ; xmm0 = xmm0 + xmm1
    addsd xmm0, xmm2   ; xmm0 = xmm0 + xmm2
    addsd xmm0, xmm3   ; xmm0 = xmm0 + xmm3
    addsd xmm0, xmm4   ; xmm0 = xmm0 + xmm4
    addsd xmm0, xmm5   ; xmm0 = xmm0 + xmm5
    addsd xmm0, xmm6   ; xmm0 = xmm0 + xmm6
    addsd xmm0, xmm7   ; xmm0 = xmm0 + xmm7
    
    ; Store result back to memory
    ;movsd [rdx + r9 * 8 - 8], 32

    movsd [rdx + r9 * 8 - 8], xmm0  

    ; Increment loop counters
              
    inc r10            ; Increment index for storing result
    inc r9          ; Increment loop counter
    
    jmp loop           ; Repeat loop

end:
    ret                ; Return
