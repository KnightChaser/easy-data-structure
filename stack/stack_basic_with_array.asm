; file: stack_basic_with_array.asm
; description: A simple stack implementation in x86-64 assembly with subroutines,
;              using an array structure to store the stack elements.

; compile and run:
; nasm -f elf64 -o stack_basic_with_array.o stack_basic_with_array.asm
; gcc -o stack_basic_with_array.out stack_basic_with_array.o -no-pie

extern printf

section .data
    stackArray              DQ 10 dup(0)                    ; stack array
    stackPointer            DQ 0                            ; stack pointer
    stackCount              DQ 0                            ; number of elements in the stack
    stackCapacity           DQ 10                           ; number of elements the stack can hold
    formatStringPop         DB "Popped value: %d", 10, 0
    formatStringPush        DB "Pushed value: %d", 10, 0
    formatStringStackFull   DB "Stack is full", 10, 0
    formatStringStackEmpty  DB "Stack is empty", 10, 0

section .text
    global main

main:
    push rbp
    mov rbp, rsp
    sub rsp, 16                          ; stack alignment

    ; Initialize stack
    lea rax, [stackArray]
    mov [stackPointer], rax

    ; Push values onto stack
    mov rdi, 10
    call stackPush

    mov rdi, 20
    call stackPush

    mov rdi, 30
    call stackPush

    mov rdi, 40
    call stackPush

    mov rdi, 50
    call stackPush

    mov rdi, 60
    call stackPush

    mov rdi, 70
    call stackPush

    mov rdi, 80
    call stackPush

    mov rdi, 90
    call stackPush

    mov rdi, 100
    call stackPush

    ; Tries to push a value onto a full stack
    mov rdi, 110
    call stackPush

    ; Pop values from stack
    call stackPop
    call stackPop
    call stackPop
    call stackPop
    call stackPop
    call stackPop
    call stackPop
    call stackPop
    call stackPop
    call stackPop

    ; Tries to pop a value from an empty stack
    call stackPop

    ; Exit
    exit:
        mov rax, 60
        xor rdi, rdi
        syscall

; Subroutine to push a value onto the stack
; Parameter 1th; rdi = value to push, size 8 bytes
stackPush:
    push rbp
    mov rbp, rsp
    sub rsp, 16                          ; stack alignment

    mov QWORD [rsp+8], rdi               ; Store subroutine parameter value to stack

    ; Check if stack is full
    ; if (stackCount == stackCapacity) { stack is full; return; }
    mov r10, [stackCount]
    mov r11, [stackCapacity]
    cmp r10, r11
    je .stackFull

    ; Push value onto stack
    xor rcx, rcx                         ; rcx = 0
    mov rcx, [stackPointer]              ; Bring stack pointer to rcx
    mov rax, [rsp+8]                     ; Store subroutine parameter value to rax
    mov [rcx], rax                       ; Push value onto stack
    add rcx, 8                           ; Increment stack pointer
    mov [stackPointer], rcx              ; Update stack pointer

    ; Increment stack count
    mov r10, [stackCount]
    inc r10
    mov [stackCount], r10

    ; Alert user that value was pushed onto stack
    lea rdi, [formatStringPush]
    mov rsi, [rsp+8]
    xor rax, rax
    call printf
    
    mov rsp, rbp
    pop rbp
    ret    

    ; Only reached if stack is full
    .stackFull:
        ; Stack is full
        lea rdi, [formatStringStackFull]
        xor rax, rax
        call printf

        mov rsp, rbp
        pop rbp
        ret

; Subroutine to pop a value from the stack
stackPop:
    push rbp
    mov rbp, rsp
    sub rsp, 16                          ; stack alignment

    ; Check if stack is empty
    ; if (stackCount == 0) { stack is empty; return; }
    mov r10, [stackCount]
    cmp r10, 0
    je .stackEmpty

    ; Pop value from stack
    ; It decrements the stack pointer first because the stack pointer points to the next available position
    mov rcx, [stackPointer]              ; Bring stack pointer to rcx
    sub rcx, 8                           ; Decrement stack pointer
    mov rax, [rcx]                       ; Pop value from stack
    mov [stackPointer], rcx              ; Update stack pointer

    ; Decrement stack count
    mov r10, [stackCount]
    dec r10
    mov [stackCount], r10

    ; Alert user that value was popped from stack
    lea rdi, [formatStringPop]
    mov rsi, rax                         ; It contains the popped value
    xor rax, rax
    call printf

    mov rsp, rbp
    pop rbp
    ret

    ; Only reached if stack is empty
    .stackEmpty:
        ; Stack is empty
        lea rdi, [formatStringStackEmpty]
        xor rax, rax
        call printf

        mov rsp, rbp
        pop rbp
        ret

; Pushed value: 10
; Pushed value: 20
; Pushed value: 30
; Pushed value: 40
; Pushed value: 50
; Pushed value: 60
; Pushed value: 70
; Pushed value: 80
; Pushed value: 90
; Pushed value: 100
; Stack is full
; Popped value: 100
; Popped value: 90
; Popped value: 80
; Popped value: 70
; Popped value: 60
; Popped value: 50
; Popped value: 40
; Popped value: 30
; Popped value: 20
; Popped value: 10
; Stack is empty