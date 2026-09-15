.intel_syntax noprefix

.text

.global asm_memset

asm_memset:
    mov rax, rdi
    mov rcx, rdx
    and esi, 0xff

.loop:
    test rcx, rcx
    je .done

    mov BYTE PTR [rdi], sil
    inc rdi
    dec rcx
    jmp .loop

.done:
    ret

