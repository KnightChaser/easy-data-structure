; file: stack_via_struct_double.asm
; description: A simple stack implementation using 
;              a structure in x86-64 assembly with subroutines for double precision floating point numbers
;              Plus, summing and averaging all elements in the stack
;              You can get how to use double precision floating point numbers in x86-64 assembly >_<

; compile and run
; nasm -f elf64 -o stack_via_struct_double.o stack_via_struct_double.asm
; gcc -o stack_via_struct_double.out stack_via_struct_double.o -no-pie

extern malloc
extern free
extern printf

%define SYS_EXIT                            60
%define STACK_ELEMENT_COUNT                 100
%define STACK_ELEMENT_SIZE(stackArrayElementSize, stackArrayElementCount) \
        (stackArrayElementSize * stackArrayElementCount + 1 + 8 * 2 + 8)
        ; stackArrayElement (8 bytes) * stackArrayElementCount + stackPointer (8 bytes) + stackCount (4 bytes) + stackCapacity (4 bytes

section .data
    struc stack
        align 16
        .stackArray                     RESQ    STACK_ELEMENT_COUNT                 ; Stack array for double (80 bytes)
        .stackPointer                   RESQ    1                                   ; Stack pointer (address of the next available slot)
        .stackCount                     RESD    1                                   ; Current size (how many elements are in the stack)
        .stackCapacity                  RESD    1                                   ; Max size (capacity of the stack)
    endstruc

    formatStringPopped                  DB     "Popped value: %lf", 10, 0
    formatStringPushed                  DB     "Pushed value: %lf", 10, 0
    formatStringStackFull               DB     "Stack is full", 10, 0
    formatStringStackEmpty              DB     "Stack is empty", 10, 0
    formatStringMemoryAllocated         DB     "Memory allocated for stack", 10, 0
    formatStringMemoryFreed             DB     "Memory freed", 10, 0
    formatStringSum                     DB     "Sum of all elements: %lf", 10, 0
    formatStringAverage                 DB     "Average of all elements: %lf", 10, 0
                                            ; Pi, e, The golden ratio, The square root of 2, The square root of 3, The square root of 5, Apery's Constant, Gelfond's Constant, Gelfond-Schneider Constant, The plastic number
    irrationalNumberList                DQ      3.14159, 2.71828, 1.61803, 1.41421, 1.73205, 2.23607, 2.64575, 3.31662, 3.60555, 4.12310
    irrationalNumberListLength          EQU     (($ - irrationalNumberList) / 8)

section .bss
    align 16
    myStack                             RESQ    1                                   ; Pointer to stack structure

section .text
    global main

main:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                     ; Align stack

    ; Allocating memory for the stack
    mov rdi, STACK_ELEMENT_SIZE(8, STACK_ELEMENT_COUNT) ; Allocate memory for stack structure
    call malloc
    mov [myStack], rax                              ; Save pointer to stack structure in myStack

    ; Print memory allocated message
    lea rdi, [formatStringMemoryAllocated]
    xor rax, rax
    call printf

    ; Initialize stack
    mov rax, [myStack]
    lea rdx, [rax + stack.stackArray]               ; Address of stackArray
    mov [rax + stack.stackPointer], rdx             ; stackPointer = &stackArray
    mov DWORD [rax + stack.stackCount], 0
    mov DWORD [rax + stack.stackCapacity], STACK_ELEMENT_COUNT

    ; Pushing values to the stack from the irrationalNumberList
    mov QWORD [rsp + 8], 0                          ; Initialize iterator
    .pushLoop:
        mov rax, [rsp + 8]                          ; Get iterator
        mov rsi, irrationalNumberList
        movsd xmm0, QWORD [rsi + rax * 8]           ; Load value from the irrationalNumberList
        mov rdi, [myStack]                          ; Stack Pointer
        call stackPush
        
        inc QWORD [rsp + 8]                         ; Increment iterator
        cmp QWORD [rsp + 8], irrationalNumberListLength
        jl .pushLoop

    ; Sum all elements in the stack
    mov rdi, [myStack]
    call sumAllStackElements
    lea rdi, [formatStringSum]
    mov rax, 1                                      ; Indicate that ST(0) will be used (SSE)
    call printf

    ; Calculate average of all elements in the stack
    mov rdi, [myStack]
    call averageAllStackElements
    lea rdi, [formatStringAverage]
    mov rax, 1                                      ; Indicate that ST(0) will be used (SSE)
    call printf

    ; Popping values from the stack
    ; 1 more than the irrationalNumberListLength to check if the stack is empty
    mov QWORD [rsp + 8], 0                          ; Initialize iterator
    .popLoop:
        mov rax, [rsp + 8]                          ; Get iterator
        mov rdi, [myStack]                          ; Stack Pointer
        call stackPop
        
        inc QWORD [rsp + 8]                         ; Increment iterator
        cmp QWORD [rsp + 8], irrationalNumberListLength + 1
        jl .popLoop

    ; Freeing memory
    mov rdi, [myStack]
    call free

    ; Print memory freed message
    lea rdi, [formatStringMemoryFreed]
    xor rax, rax
    call printf

    ; Exit
    exit:
        mov rax, SYS_EXIT
        xor rdi, rdi
        syscall

; Subroutine to check if the stack is empty
; @param rdi = pointer to stack structure
; @return rax = 1 if stack is empty, rax = 0 otherwise
isStackEmpty:
    xor rax, rax
    mov eax, [rdi + stack.stackCount]
    cmp rax, 0
    je .stackEmptyException
    jne .stackNotEmpty
    .stackEmptyException:
        mov rax, 1
        ret
    .stackNotEmpty:
        mov rax, 0
        ret

; Subroutine to check if the stack is full
; @param rdi = pointer to stack structure
; @return rax = 1 if stack is full, rax = 0 otherwise
isStackFull:
    xor rax, rax
    xor rdx, rdx
    mov eax, [rdi + stack.stackCount]
    mov edx, [rdi + stack.stackCapacity]
    cmp eax, edx
    je .stackFull
    jne .stackNotFull
    .stackFull:
        mov rax, 1
        ret
    .stackNotFull:
        mov rax, 0
        ret

; Subroutine to push a double value onto the stack
; @param rdi = pointer to stack structure
; @param xmm0 = double value to push
stackPush:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                     ; Align stack

    ; Storing the parameter value in the stack
    movsd [rsp + 8], xmm0                           ; Store the value in the stack

    ; Check if the stack is full
    mov rdi, [myStack]                              ; Make sure we use the stack base pointer
    call isStackFull
    test rax, rax
    jnz .stackFullException

    ; Push value onto the stack
    mov QWORD rax, [rdi + stack.stackPointer]       ; Get stack pointer (address of the next available slot)
    mov QWORD rbx, [rsp + 8]
    mov QWORD [rax], rbx
    add rax, 8                                      ; Move the stack pointer to the next available slot
    mov [rdi + stack.stackPointer], rax             ; Update the stack pointer
    inc DWORD [rdi + stack.stackCount]              ; Increment the stack count

    ; Print pushed value
    lea rdi, [formatStringPushed]
    movsd xmm0, QWORD [rsp + 8]                     ; Load the last pushed value for printing
    mov rax, 1                                      ; Indicate that ST(0) will be used (SSE)
    call printf

    leave
    ret

    .stackFullException:
        lea rdi, [formatStringStackFull]
        xor rax, rax
        call printf

        leave
        ret

; Subroutine to pop a double value from the stack
; @param rdi = pointer to stack structure
; @return xmm0 = popped double value
stackPop:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                     ; Align stack

    ; Check if the stack is empty
    mov rdi, [myStack]                              ; Make sure we use the stack base pointer
    call isStackEmpty
    test rax, rax
    jnz .stackEmptyException

    ; Pop value from the stack
    mov rax, [rdi + stack.stackPointer]             ; Get stack pointer (address of the next available slot)
    sub rax, 8                                      ; Move the stack pointer to the last pushed value
    mov rbx, QWORD [rax]                            ; Get the last pushed value
    mov [rdi + stack.stackPointer], rax             ; Update the stack pointer
    dec DWORD [rdi + stack.stackCount]              ; Decrement the stack count
    mov QWORD [rsp + 8], rbx                        ; Store the popped value in the stack

    ; Print popped value
    lea rdi, [formatStringPopped]
    movsd xmm0, QWORD [rsp + 8]                     ; Load the last popped value for printing
    mov rax, 1                                      ; Indicate that ST(0) will be used (SSE)
    call printf

    leave
    ret

    .stackEmptyException:
        lea rdi, [formatStringStackEmpty]
        xor rax, rax
        call printf

        leave
        ret

; A function summing all elements in the stack
; @param rdi = pointer to stack structure
; @return xmm0 = sum of all elements
sumAllStackElements:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                     ; Align stack

    ; Initialize sum
    movq xmm0, rax
    mov rax, __?float64?__(0.0)                     ; Initialize sum to 0
    movq xmm0, rax

    ; Sum all elements in the stack
    mov rdi, [myStack]                              ; Make sure we use the stack base pointer
    mov rax, [rdi + stack.stackPointer]             ; Get stack pointer (address of the next available slot)
    mov rsi, [rdi + stack.stackArray]               ; Get stack array base address
    mov ecx, [rdi + stack.stackCount]               ; Get stack count

    .sumLoop:
        sub rax, 8                                  ; Move the stack pointer to the last pushed value
        dec rcx                                     ; Decrement the stack count
        movsd xmm1, QWORD [rax]                     ; Load the last pushed value
        addsd xmm0, xmm1                            ; Add the value to the sum
        cmp ecx, 0
        jne .sumLoop

    leave
    ret

; A function calculating the average of all elements in the stack
; @param rdi = pointer to stack structure
; @return xmm0 = average of all elements
averageAllStackElements:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                     ; Align stack

    ; Initialize sum
    movq xmm0, rax
    mov rax, __?float64?__(0.0)                     ; Initialize sum to 0
    movq xmm0, rax

    ; Call sumAllStackElements
    mov rdi, [myStack]                              ; Make sure we use the stack base pointer
    call sumAllStackElements

    ; Calculate average
    xor rax, rax
    mov eax, [rdi + stack.stackCount]               ; Get stack count
    cvtsi2sd xmm1, rax                              ; Convert stack count(integer) to double
    divsd xmm0, xmm1                                ; Calculate average

    leave
    ret

; Pushed value: 3.141590
; Pushed value: 2.718280
; Pushed value: 1.618030
; Pushed value: 1.414210
; Pushed value: 1.732050
; Pushed value: 2.236070
; Pushed value: 2.645750
; Pushed value: 3.316620
; Pushed value: 3.605550
; Pushed value: 4.123100
; Sum of all elements: 26.551250
; Average of all elements: 2.655125
; Popped value: 4.123100
; Popped value: 3.605550
; Popped value: 3.316620
; Popped value: 2.645750
; Popped value: 2.236070
; Popped value: 1.732050
; Popped value: 1.414210
; Popped value: 1.618030
; Popped value: 2.718280
; Popped value: 3.141590
; Stack is empty
; Memory freed