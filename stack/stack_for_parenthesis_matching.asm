; file: stack_for_parenthesis_matching.asm
; description: Checking if the parenthesis are balanced or not, using stack
;              Written in x86_64 assembly langauge and subroutines.

; compile and run
; nasm -f elf64 -o stack_for_parenthesis_matching.o stack_for_parenthesis_matching.asm
; gcc -o stack_for_parenthesis_matching.out stack_for_parenthesis_matching.o -no-pie

extern malloc
extern free
extern printf

%define SYS_EXIT                                    60
%define STACK_ELEMENT_COUNT                         100
%define CALCULATE_STACK_SIZE(stackLength, elementSize, stackPointerQty, stackPointerSize, variableQty, variableSize) \
    (stackLength * elementSize + stackPointerQty * stackPointerSize + variableQty * variableSize)

section .data
    ; Define a strructure for the stack, containing bunch of char(RESB 1)
    struc stack
        align 16, DB 0                                                      ; Align the stack to 16 bytes
        .stackArray                         RESB    STACK_ELEMENT_COUNT     ; (XXX bytes) Array to store the elements of the stack
        .stackPointer                       RESQ    1                       ; (  8 bytes) Pointer to the top of the stack
        .stackCount                         RESD    1                       ; (  4 bytes) Number of elements in the stack
        .stackCapacity                      RESD    1                       ; (  4 bytes) Capacity of the stack (max number of elements)
    endstruc

    ; Define format strings for alerting the user
    formatStringPopped                      DB     "Popped: %c", 10, 0
    formatStringPushed                      DB     "Pushed: %c", 10, 0
    formatStringStackFull                   DB     "Stack is full", 10, 0
    formatStringStackEmpty                  DB     "Stack is empty", 10, 0
    formatStringMemoryAllocated             DB     "Memory allocated", 10, 0
    formatStringMemoryDeallocated           DB     "Memory deallocated", 10, 0
    formatStringParenthesisBalanced         DB     "Parenthesis are balanced", 10, 0
    formatStringParenthesisNotBalanced      DB     "Parenthesis are not balanced", 10, 0
    formatStringNumberOfCharactersNotEqual  DB     "Number of characters are not equal", 10, 0

    ; Define examples of balanced and not balanced parenthesis
    formatStringShowingExample              DB     10, "Example: %s", 10, 0
    parenthesisBalancedExample              DB     "(a+(b+(c/d)+e))", 0
    parenthesisNotBalancedExample           DB     "(a+(b+(c/d)+e)))", 0

section .bss
    align 16                                                                ; Align the stack to 16 bytes
    parenthesisStack                        RESQ   1                        ; (  8 bytes) Stack to store the parenthesis

section .text
    global main

main:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                                             ; Stack alignment

    ; Allocate memory for the stack after calculating the size
    mov rdi, CALCULATE_STACK_SIZE(STACK_ELEMENT_COUNT, 1, 1, 8, 2, 4)       ; Calculate the size of the stack
    call malloc
    mov [parenthesisStack], rax

    ; Print memory allocated message
    lea rdi, [formatStringMemoryAllocated]
    xor rax, rax
    call printf

    ; Initialize the stack
    mov rax, [parenthesisStack]
    lea rdx, [rax + stack.stackArray]                                       ; Load the address of the stackArray
    mov [rax + stack.stackPointer], rdx                                     ; Initialize the stack pointer
    mov DWORD [rax + stack.stackCount], 0                                   ; Initialize the count of the stack
    mov DWORD [rax + stack.stackCapacity], STACK_ELEMENT_COUNT              ; Initialize the capacity of the stack

    ; Check if the parenthesis are balanced or not
    lea rdi, [formatStringShowingExample]
    lea rsi, [parenthesisBalancedExample]
    xor rax, rax
    call printf

    lea rdi, [parenthesisBalancedExample]
    call checkParenthesisMatching

    lea rdi, [formatStringShowingExample]
    lea rsi, [parenthesisNotBalancedExample]
    xor rax, rax
    call printf

    lea rdi, [parenthesisNotBalancedExample]
    call checkParenthesisMatching

    ; Deallocate memory for the stack
    mov rdi, [parenthesisStack]
    call free

    ; Print memory deallocated message
    lea rdi, [formatStringMemoryDeallocated]
    xor rax, rax
    call printf

    ; Exit
    exit:
        mov rax, SYS_EXIT
        xor rdi, rdi
        syscall

; Subroutine to read the given string and push the parenthesis into the stack
; Parameter 1st(RDI): a string pointer to read, size 8 bytes(RESQ 1)
checkParenthesisMatching:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                             ; Stack alignment

    ; Read the given string and push the parenthesis into the stack
    mov QWORD [rsp + 8], rdi                                ; Store the string pointer
    mov QWORD [rsp + 16], 0                                 ; Initialize the index of the string

    .readParenthesis:
        xor r11, r11                                        ; Initialize the character of the string
        
        mov rax, [rsp + 8]                                  ; Load the string pointer
        mov r10, [rsp + 16]                                 ; Load the index of the string
        movzx r11, BYTE [rax + r10]                         ; Load the character of the string
        inc r10                                             ; Increment the index of the string
        mov [rsp + 16], r10                                 ; Store the index of the string
        cmp r11, 0                                          ; Check if the character is null
        je .endReadParenthesis                              ; If the character is null, end reading the string

        ; Check if the character is a parenthesis
        cmp r11, '('
        je .pushParenthesis
        cmp r11, ')'
        je .popParenthesis

        jmp .readParenthesis                                ; If the character is not a parenthesis, read the next character

        .pushParenthesis:
            mov dil, r11b                                   ; Load the character into the register (1 byte)
            call stackPush                                  ; Push the character into the stack
            jmp .readParenthesis

        .popParenthesis:
            call stackPop                                   ; Pop the character from the stack
            cmp rax, -1                                     ; Check if stack exception occurs
            je .parenthesisNotBalanced                      ; Immediately decide that the parenthesis are not balanced
            
            jmp .readParenthesis                            ; Continue only if the stack is not empty during checking string

    .endReadParenthesis:
        ; If the stack is empty, the parenthesis are balanced
        mov rax, [parenthesisStack]
        mov DWORD edx, [rax + stack.stackCount]             ; Load the count of the stack
        cmp edx, 0
        je .parenthesisBalanced

        .parenthesisNotBalanced:
            ; If the stack is not empty, the parenthesis are not balanced
            lea rdi, [formatStringParenthesisNotBalanced]
            xor rax, rax
            call printf
            jmp exit                                        ; Exit to main routine

    .numberOfCharactersNotEqual:
        lea rdi, [formatStringNumberOfCharactersNotEqual]
        xor rax, rax
        call printf
        jmp exit                                            ; Exit to main routine

    .parenthesisBalanced:
        lea rdi, [formatStringParenthesisBalanced]
        xor rax, rax
        call printf

    ; Exiting
    leave
    ret

; Subroutine to push a value onto the stack
; Parameter 1st(RDI): a value to push, size 1 byte(RESB 1)
; In the stack, the parenthesises are pushed to check if they are balanced or not
stackPush:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                             ; Stack alignment

    ; Store the value to push into the stack
    mov BYTE [rsp+8], dil

    ; Check if the stack is full
    mov rax, [parenthesisStack]
    mov DWORD edx, [rax + stack.stackCount]                 ; Load the count of the stack
    mov DWORD ecx, [rax + stack.stackCapacity]              ; Load the capacity of the stack
    cmp edx, ecx
    jae .stackFull                                          ; If the count is greater than or equal to the capacity, the stack is full

    ; Push value onto the stack
    ; stackPointer->stackArray[stackPointer->stackCount] = value
    mov rsi, [rax + stack.stackPointer]
    mov BYTE dil, [rsp + 8]
    mov BYTE [rsi], dil                                     ; Push the value onto the stack
    inc DWORD [rax + stack.stackPointer]                    ; Increment the pointer of the stack
    inc DWORD [rax + stack.stackCount]                      ; Increment the count of the stack

    ; Print pushed value
    lea rdi, [formatStringPushed]
    mov QWORD rsi, [rsp + 8]
    xor rax, rax
    call printf

    ; Leave
    leave
    ret

    .stackFull:
        lea rdi, [formatStringStackFull]
        xor rax, rax
        call printf

        leave
        ret

; Subroutine to pop a value from the stack
; Returning value; rax = popped value. size 1 byte (RESB 1)
stackPop:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                             ; Stack alignment

    ; Check if stack is empty
    ; if (stackP->stackCount == 0) return stackEmpty();
    mov rax, [parenthesisStack]
    mov DWORD edx, [rax + stack.stackCount]                 ; Load the count of the stack
    cmp edx, 0
    je .stackEmpty                                          ; If the count is 0, the stack is empty

    ; Pop value from the stack
    ; stackPointer->stackPointer--;
    ; BYTE value = stackPointer->stackArray;
    ; stackPointer->stackCount--;                           
    mov rsi, [rax + stack.stackPointer]                     ; Load the pointer of the stack
    dec rsi                                                 ; Decrement the pointer of the stack
    mov [rax + stack.stackPointer], rsi                     ; Store the pointer of the stack
    movzx r10, BYTE [rsi]                                   ; Pop the value from the stack
    dec DWORD [rax + stack.stackCount]                      ; Decrement the count of the stack

    ; Print popped value
    lea rdi, [formatStringPopped]
    mov rsi, r10
    xor rax, rax
    call printf

    ; Thus, the popped value will be returned via $rax
    mov rax, r10

    ; Exiting
    leave
    ret

    .stackEmpty:
        lea rdi, [formatStringStackEmpty]
        xor rax, rax
        call printf

        mov rax, -1                                         ; An invalid value to indicate the stack is empty

        leave
        ret

; Memory allocated
; 
; Example: (a+(b+(c/d)+e))
; Pushed: (
; Pushed: (
; Pushed: (
; Popped: (
; Popped: (
; Popped: (
; Parenthesis are balanced
; 
; Example: (a+(b+(c/d)+e)
; Pushed: (
; Pushed: (
; Pushed: (
; Popped: (
; Popped: (
; Parenthesis are not balanced