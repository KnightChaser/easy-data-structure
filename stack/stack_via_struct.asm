; file: stack_via_struct.asm
; description; A simple stack implementation using 
;              a structure in x86-64 assembly with subroutines

; compile and run
; nasm -f elf64 -o stack_via_struct.o stack_via_struct.asm
; gcc -o stack_via_struct.out stack_via_struct.o -no-pie

extern malloc
extern free
extern printf

section .data
    ; Define a structure for the stack
    struc stack
        align 16                                    ; Align to 16 bytes
        .stackArray                 RESQ    10      ; (80 bytes) stack array
        .stackPointer               RESQ    1       ; ( 8 bytes) stack pointer  (the address of the next available slot)
        .stackCount                 RESD    1       ; ( 4 bytes) stack count    (current size; how many elements are in the stack)
        .stackCapacity              RESD    1       ; ( 4 bytes) stack capacity (max size)
    endstruc

    ; Define format strings that will be used in printf
    formatStringPopped              DB     "Popped value: %d", 10, 0
    formatStringPushed              DB     "Pushed value: %d", 10, 0
    formatStringStackFull           DB     "Stack is full", 10, 0
    formatStringStackEmpty          DB     "Stack is empty", 10, 0
    formatStringMemoryAllocated     DB     "Memory allocated for stack", 10, 0
    formatStringMemoryFreed         DB     "Memory freed", 10, 0

section .bss
    align 16                                        ; Align to 16 bytes
    myStack                         RESQ    1       ; Pointer to stack structure       

section .text
    global main

main:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                     ; Align stack

    ; Allocating memory for the stack
    mov rdi, 96
    call malloc
    mov [myStack], rax                                ; Save pointer to stack structure in myStack

    ; Print memory allocated message
    lea rdi, [formatStringMemoryAllocated]
    xor rax, rax
    call printf

    ; Initialize stack (corrected dereferencing)
    mov rax, [myStack]
    lea rdx, [rax + stack.stackArray]                 ; Address of stackArray
    mov [rax + stack.stackPointer], rdx               ; Corrected: stackP->stackPointer = &stackP->stackArray
    mov DWORD [rax + stack.stackCount], 0
    mov DWORD [rax + stack.stackCapacity], 10

    ; Pushing 11 times (10 times normal + 1 time to test stack full)
    ; Push 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110
    mov QWORD [rsp+8], 10                             ; Storing iterated value
    .pushLoop:
        mov rdi, [rsp+8]                              ; rdi = value to push
        call stackPush
        add QWORD [rsp+8], 10
        cmp QWORD [rsp+8], 110
        jna .pushLoop

    ; Popping 11 times (10 times normal + 1 time to test stack empty)
    mov QWORD [rsp+8], 1
    .popLoop:
        call stackPop
        inc QWORD [rsp+8]
        cmp QWORD [rsp+8], 11
        jna .popLoop

    ; free(stackP);
    mov rdi, [myStack]
    call free

    ; Print memory freed message
    lea rdi, [formatStringMemoryFreed]
    xor rax, rax
    call printf

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
    sub rsp, 16

    ; Store the value to push
    mov QWORD [rsp+8], rdi

    ; Check if the stack is full
    ; if (stackP->stackCount >= stackP->stackCapacity) return stackFull();
    mov rax, [myStack]                             ; Load the address of the stack structure
    mov DWORD edx, [rax + stack.stackCount]        ; Load stackCount
    mov DWORD ecx, [rax + stack.stackCapacity]     ; Load stackCapacity
    cmp edx, ecx
    jae .stackFull

    ; Push value onto the stack
    ; stackP->stackArray[stackP->stackPointer] = value;
    ; stackP->stackPointer += 8;
    ; stackP->stackCount++;
    mov rsi, [rax + stack.stackPointer]            ; Load stackPointer
    mov rdi, [rsp + 8]
    mov QWORD [rsi], rdi                           ; Push value onto the stack
    add QWORD [rax + stack.stackPointer], 8        ; Increment stackPointer
    inc DWORD [rax + stack.stackCount]             ; Increment stackCount

    ; Print pushed value
    lea rdi, [formatStringPushed]
    mov QWORD rsi, [rsp + 8]                       ; Value to print
    xor rax, rax                                   ; Zero rax before calling printf
    call printf

    ; Clean up and return
    mov rsp, rbp
    pop rbp
    ret

    .stackFull:
        lea rdi, [formatStringStackFull]
        xor rax, rax
        call printf
        mov rsp, rbp
        pop rbp
        ret

; Subroutine to pop a value from the stack
; Return value; rax = popped value, size 8 bytes
stackPop:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                     ; Stack alignment

    ; Check if stack is empty
    ; if (stackP->stackCount == 0) return stackEmpty();
    mov rax, [myStack]                             ; Load the address of the stack structure
    mov edx, DWORD [rax + stack.stackCount]         ; Load stackCount
    cmp edx, 0
    je .stackEmpty

    ; Pop value from the stack
    ; QWORD ret = stackP->stackArray;
    ; stackP->stackPointer -= 8;
    ; stackP->stackCount--;
    mov rsi, [rax + stack.stackPointer]            ; Load stackPointer
    sub rsi, 8                                     ; Decrement stackPointer (Since it is a pointer to the next available slot)
    mov [rax + stack.stackPointer], rsi            ; Update stackPointer
    mov rdi, [rsi]                                 ; Load value to pop ($rsi is a pointer to the value to pop)
    dec DWORD [rax + stack.stackCount]             ; Decrement stackCount
    mov rax, rdi                                   ; Return value

    ; Print popped value
    lea rdi, [formatStringPopped]
    mov rsi, rax                                   ; Value to print
    xor rax, rax
    call printf

    ; Exit
    mov rsp, rbp
    pop rbp
    ret

    .stackEmpty:
        lea rdi, [formatStringStackEmpty]
        xor rax, rax
        call printf

        mov rsp, rbp
        pop rbp
        ret

; Memory allocated for stack
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
; Memory freed