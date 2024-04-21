; file: stack_basic_with_subroutine.asm
; description: A simple stack implementation in x86-64 assembly with subroutines for pushing and popping characters
;              An improved version of ./stack_basic.asm

; compile and run:
; nasm -f elf64 -o stack_basic.o stack_basic.asm
; gcc -o stack_basic.out stack_basic.o -no-pie

extern printf

section .data
    formatStringPop  DB "Popped char: %c", 0x0A, 0x00   ; format string for printf with newline when popping
    formatStringPush DB "Pushed char: %c", 0x0A, 0x00   ; format string for printf with newline when pushing

section .bss
    stackSpace       RESB   16                          ; reserve 16 bytes for the stack
    stackPointer     RESQ   1                           ; reserve 8 bytes for the stack pointer (64-bit address)

section .text
    global main

main:
    sub rsp, 8                                          ; Align the stack to 16-byte boundary
                                                        ; .bss stackPointer RESQ 1 is 8 bytes, so we need to subtract 8 bytes from the stack pointer

    lea rax, [stackSpace]
    mov [stackPointer], rax                             ; Initialize stack pointer

    ; Push 'A'
    mov rdi, 'A'
    call do_push

    ; Push 'B'
    mov rdi, 'B'
    call do_push

    ; Push 'C'
    mov rdi, 'C'
    call do_push

    ; Pop all characters
    call do_pop
    call do_pop
    call do_pop

    exit:
        ; Exit program
        mov rax, 60                                     ; syscall number for exit
        xor rdi, rdi                                    ; exit code 0
        syscall                                         ; perform the system call

; Subroutine to push a character onto the stack
; parameter: 1th; rdi = character to push (actually dil, the lower 8 bits of RDI)
do_push:
    push rbp                                  
    mov rbp, rsp                                    
    sub rsp, 16                                     ; Stack alignement (16 * k bytes per function call)

    mov rcx, [stackPointer]                         ; Load stack pointer
    mov [rcx], dil                                  ; Move character (lower 8 bits of RDI) to stack
    add rcx, 1                                      ; Increment stack pointer
    mov [stackPointer], rcx                         ; Save updated stack pointer
                                                    ; Now, rcx points to the next available space in the stack

    mov BYTE [rsp+8], dil                           ; Save character to stack for printf()

    lea rdi, [formatStringPush]
    mov rsi, [rsp+8]                                ; Load character to RSI for printf
    xor rax, rax                                    
    call printf

    mov rsp, rbp                                    
    pop rbp                                         ; Clearing the subroutine stack
    ret

do_pop:
    push rbp                                        
    mov rbp, rsp                                    
    sub rsp, 16                                     ; Stack alignment (16 * k bytes per function)

    ; Check if stack is empty
    mov rcx, [stackPointer]                         ; Load stack pointer
    cmp rcx, [stackSpace]                           ; Compare stack pointer with stack start
    je exit                                         ; If equal, stack is empty

                                                    ; Because rcx points to the next available space in the stack, we need to decrement it first
    mov rcx, [stackPointer]                         ; Load stack pointer
    sub rcx, 1                                      ; Decrement stack pointer
    mov [stackPointer], rcx                         ; Save updated stack pointer
    movzx rax, BYTE [rcx]                           ; Load character from stack into RAX

    lea rdi, [formatStringPop]
    mov rsi, rax                                    ; Load character to RAX for printf
    xor rax, rax                                    
    call printf

    mov rsp, rbp                                    
    pop rbp                                         ; Clearing the subroutine stack
    ret

; Pushed char: A
; Pushed char: B
; Pushed char: C
; Popped char: C
; Popped char: B
; Popped char: A