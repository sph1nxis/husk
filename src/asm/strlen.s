.intel_syntax noprefix

.text

.global asm_strlen

asm_strlen:
    xor rax, rax

.loop:
    cmp BYTE PTR [rdi], 0
    je .done

    inc rdi
    inc rax
    jmp .loop

.done:
    ret

