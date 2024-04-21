; file: stack_basic.asm
; description: A simple stack implementation in NASM, Ubuntu, with push and pop notifications using loops

extern printf

section .data
    formatStringPop  DB "Popped char: %c", 0x0A, 0x00   ; format string for printf with newline when popping
    formatStringPush DB "Pushed char: %c", 0x0A, 0x00   ; format string for printf with newline when pushing
    charsToPush      DB 'A', 'B', 'C'                   ; Characters to push onto the stack
    numChars         EQU 3                              ; Number of characters to push

section .bss
    stackSpace      RESB 16                             ; reserve 16 bytes for the stack
    stackPointer    RESQ 1                              ; reserve 8 bytes for the stack pointer (64-bit address)

section .text
    global main

    main:
        sub rsp, 8                                      ; Align the stack to 16-byte boundary

        lea rax, [stackSpace]
        mov [stackPointer], rax
        mov r12, 0                                      ; Initialize index for loop

    push_loop:
        cmp r12, numChars                               ; Compare loop index with number of characters
        je pop_init                                     ; Jump to pop initialization if done pushing

        movzx rax, byte [charsToPush + r12]             ; Load character from data section
        mov rcx, [stackPointer]                         ; Load stack pointer
        mov [rcx], al                                   ; Move character to stack (al = 1 byte)
        inc rcx                                         ; Increment stack pointer
        mov [stackPointer], rcx                         ; Save updated stack pointer

        ; Print the character
        lea rdi, [formatStringPush]
        mov rsi, rax
        xor rax, rax
        call printf

        inc r12                                         ; Increment index
        jmp push_loop                                   ; Loop back

    pop_init:
        mov r12, numChars                               ; Initialize counter for popping

    pop_loop:
        cmp r12, 0
        je exit                                         ; Exit if count reaches 0

        mov rcx, [stackPointer]                         ; Load stack pointer
        sub rcx, 1                                      ; Decrement stack pointer
        mov [stackPointer], rcx                         ; Save updated stack pointer
        movzx rax, byte [rcx]                           ; Load character from stack

        ; Print the character
        lea rdi, [formatStringPop]
        mov rsi, rax
        xor rax, rax
        call printf

        dec r12                                         ; Decrement counter
        jmp pop_loop                                    ; Loop back

    exit:
        mov rax, 60                                     ; syscall number for exit
        xor rdi, rdi                                    ; exit code 0
        syscall                                         ; perform the system call
