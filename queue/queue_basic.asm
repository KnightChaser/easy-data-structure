; file: queue_basic.asm
; description: A basic queue implementation using an array and structures(struc/endstruc)
;              in x86_64 assembly language. (Also using subroutines)

; compile and run
; nasm -f elf64 -o queue_basic.o queue_basic.asm
; gcc -o queue_basic.out queue_basic.o -no-pie

extern malloc
extern printf
extern free

%define SYS_EXIT                                    60
%define QUEUE_ELEMENT_SIZE_IN_BYTE                  1
%define QUEUE_CAPACITY                              10
%define CALCUALTE_QUEUE_SIZE(queueElementSizeInByte, queueCapacity) \
    (queueElementSizeInByte * queueCapacity + 4 + 4 + 4)
    ; 4 bytes for queueFrontIndex, 4 bytes for queueRearIndex, 4 bytes for queueCapacity

; Verbosity setting (If 1, print messages per every operation)
%define TRUE                                        1
%define FALSE                                       0
%define OPERATION_VERBOSITY                         FALSE

section .data
    ; Queue structure (In this case, use char as the queue element type)
    struc queue
        align 16, DB 0
        .queueArray                                 RESB    QUEUE_CAPACITY      ; Storing elements in the queue
        .queueFrontIndex                            RESD    1                   ; Front pointer of the queue
        .queueRearIndex                             RESD    1                   ; Rear pointer of the queue
        .queueCapacity                              RESD    1                   ; Capacity of the queue
    endstruc

    ; Define format strings to show the messages
    formatStringEnqueued                            DB      "Enqueued: %c", 10, 0
    formatStringDequeued                            DB      "Dequeued: %c", 10, 0
    formatStringPeeked                              DB      "Peeked: %c", 10, 0
    formatStringQueueFull                           DB      "Queue is full", 10, 0
    formatStringQueueEmpty                          DB      "Queue is empty", 10, 0
    formatStringMemoryForQueueAllocated             DB      "Memory for the queue is allocated", 10, 0
    formatStringMemoryForQueueDeallocated           DB      "Memory for the queue is deallocated", 10, 0
    formatStringQueueDisplayStats                   DB      "Front: % 2d, Rear: % 2d, Capacity: % 2d => ", 0
    formatStringQueueDisplayFront                   DB      "| ", 0         ; For displaying the first wall
    formatStringQueueDisplayElement                 DB      "%c | ", 0
    formatStringQueueDisplayVoid                    DB      "  | ", 0
    formatStringNewLine                             DB      10, 0

    ; Element list to enqueue
    elementList                                     DB      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'
    elementListLength                               EQU     $ - elementList

section .bss
    align 16
    ; Define the queue structure
    queuePointer                                    RESQ    1

section .text
    global main

main:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                                                 ; Stack alignment

    ; Allocate memory for the queue structure
    mov rdi, CALCUALTE_QUEUE_SIZE(QUEUE_ELEMENT_SIZE_IN_BYTE, QUEUE_CAPACITY)
    call malloc
    mov [queuePointer], rax                                                     ; Save the pointer to the queue structure

    ; Print memory allocation message
    lea rdi, [formatStringMemoryForQueueAllocated]
    xor rax, rax
    call printf

    ; Initialize the queue structure
    mov rdi, [queuePointer]                                                     ; Load the pointer to the queue structure
    mov DWORD [rdi + queue.queueFrontIndex], -1                                 ; Initialize the front index
    mov DWORD [rdi + queue.queueRearIndex], -1                                  ; Initialize the rear index
    mov DWORD [rdi + queue.queueCapacity], QUEUE_CAPACITY                       ; Initialize the capacity

    ; Enqueue elements to the queue in the elementList
    mov QWORD [rsp], 0                                                          ; Initialize the loop counter
    .enqueueLoop:
        ; Enqueue the element
        xor rsi, rsi
        mov rdi, [queuePointer]
        mov rcx, [rsp]
        mov sil, [elementList + rcx * QUEUE_ELEMENT_SIZE_IN_BYTE]
        call enqueue

        ; Display the queue
        mov rdi, [queuePointer]
        call displayQueue

        inc QWORD [rsp]
        cmp QWORD [rsp], elementListLength
        jle .enqueueLoop

    ; Peek the front element of the queue and print it
    mov rdi, [queuePointer]
    call peek

    lea rdi, [formatStringPeeked]
    mov rsi, rax
    xor rax, rax
    call printf

    ; Dequeue 5 times
    mov QWORD [rsp], 0
    .dequeueLoop:
        ; Dequeue the element
        mov rdi, [queuePointer]
        call dequeue

        ; Display the queue
        mov rdi, [queuePointer]
        call displayQueue

        inc QWORD [rsp]
        cmp QWORD [rsp], 5
        jle .dequeueLoop

    ; Peek the front element of the queue and print it
    mov rdi, [queuePointer]
    call peek

    lea rdi, [formatStringPeeked]
    mov rsi, rax
    xor rax, rax
    call printf

    ; Free the memory allocated for the queue
    mov rdi, [queuePointer]
    call free

    ; Print memory deallocation message
    lea rdi, [formatStringMemoryForQueueDeallocated]
    xor rax, rax
    call printf

    ; Exit
    exit:
        mov rax, SYS_EXIT
        xor rdi, rdi
        syscall

; Subroutine to check if the queue is full
; @param ($rdi) queuePointer: Pointer to the queue structure
; @return ($rax) 1 if the queue is full, 0 otherwise
isQueueFull:
    xor rax, rax
    xor rbx, rbx
    mov eax, [rdi + queue.queueRearIndex]
    mov ebx, [rdi + queue.queueCapacity]
    dec ebx                                                                 ; Rear index starts from -1
    cmp eax, ebx
    je .queueFull
    jne .queueNotFull
    .queueFull:
        mov rax, 1
        ret
    .queueNotFull:
        mov rax, 0
        ret

; Subroutine to check if the queue is empty
; @param ($rdi) queuePointer: Pointer to the queue structure
; @return ($rax) 1 if the queue is empty, 0 otherwise
isQueueEmpty:
    xor rax, rax
    xor rbx, rbx
    mov eax, [rdi + queue.queueFrontIndex]
    mov ebx, [rdi + queue.queueRearIndex]
    cmp eax, ebx
    je .queueEmpty
    jne .queueNotEmpty
    .queueEmpty:
        mov rax, 1
        ret
    .queueNotEmpty:
        mov rax, 0
        ret

; Subroutine to enqueue an element to the queue
; @param ($rdi) queuePointer: Pointer to the queue structure
; @param ($rsi) element: Element to be enqueued (actually $sil because of the register size)
enqueue:
    push rbp
    mov rbp, rsp
    sub rsp, 16                                                                 ; Stack alignment

    ; Store the parameters to the local stack
    mov QWORD [rsp], rdi                                                        ; Store the queuePointer
    mov BYTE [rsp + 8], sil                                                     ; Store the element

    ; Check if the queue is full
    mov rdi, [rsp]
    call isQueueFull
    cmp rax, 1
    je .queueFullException

    ; Enqueue the element
    ; queue->queueRearIndex++;
    ; queue->queueArray[queue->queueRearIndex] = element;
    xor rax, rax
    mov eax, [rdi + queue.queueRearIndex]
    inc eax
    mov DWORD [rdi + queue.queueRearIndex], eax
    lea rbx, [rdi + queue.queueArray]                                          ; Load the address of the queueArray
    mov cl, [rsp + 8]
    mov [rbx + rax * QUEUE_ELEMENT_SIZE_IN_BYTE], cl

    ; Print enqueued message
    mov r10, OPERATION_VERBOSITY
    cmp r10, TRUE
    je .printEnqueuedMessage
    jmp .exit

    .printEnqueuedMessage:
        lea rdi, [formatStringEnqueued]
        mov rsi, [rsp + 8]
        xor rax, rax
        call printf

    ; Exit
    .exit:
        leave
        ret

    .queueFullException:
        ; Print queue full message
        lea rdi, [formatStringQueueFull]
        xor rax, rax
        call printf

        leave
        ret

; Subroutine to dequeue an element from the queue
; @param ($rdi) queuePointer: Pointer to the queue structure
; @return ($rax) Dequeued element (actually $al because of the register size)
;                If the queue is empty, return -1
dequeue:
    push rbp
    mov rbp, rsp
    sub rsp, 16

    ; Check if the queue is empty
    call isQueueEmpty
    cmp rax, 1
    je .queueEmptyException

    ; Dequeue the element
    ; queue->queueFrontIndex++;
    ; QueueElement data = queue->queueArray[queue->queueFrontIndex];
    ; memset(&queue->queueArray[queue->queueFrontIndex], 0, sizeof(char));
    ; return data;
    xor rax, rax
    mov eax, [rdi + queue.queueFrontIndex]              ; Load front index
    inc eax
    mov DWORD [rdi + queue.queueFrontIndex], eax        ; Increment the front index

    lea rbx, [rdi + queue.queueArray]                   ; Get address of the queueArray
    movzx eax, BYTE [rbx + rax]                         ; Load the element at the front index
    
    ; Clear the dequeued element
    xor rax, rax
    mov eax, DWORD [rdi + queue.queueFrontIndex]
    mov BYTE [rdi + queue.queueArray + rax * QUEUE_ELEMENT_SIZE_IN_BYTE], 0 ; Clear the dequeued element

    ; Print dequeued message, if verbosity is enabled
    mov r10, OPERATION_VERBOSITY
    cmp r10, TRUE
    je .printDequeuedMessage
    jmp .exit

    .printDequeuedMessage:
        lea rdi, [formatStringDequeued]
        movzx rsi, al
        xor rax, rax
        call printf

    .exit:
        movzx rax, al    ; Return the dequeued element in rax
        leave
        ret

    .queueEmptyException:
        lea rdi, [formatStringQueueEmpty]
        xor rax, rax
        call printf
        mov rax, -1       ; Return -1 if the queue is empty
        leave
        ret


; Subroutine to peek the front element of the queue (not dequeue, so the front index is not changed)
; @param ($rdi) queuePointer: Pointer to the queue structure
; @return ($rax) Front element of the queue (actually $al because of the register size)
;                If the queue is empty, return -1
peek:
    push rbp
    mov rbp, rsp
    sub rsp, 16

    ; Check if the queue is empty
    call isQueueEmpty
    cmp rax, 1
    je .queueEmptyException

    ; Peek the front element
    xor rax, rax
    mov eax, DWORD [rdi + queue.queueFrontIndex]              ; Load front index
    inc eax                                                   ; The index starts from -1
    lea rbx, [rdi + queue.queueArray]                         ; Get address of the queueArray
    movzx eax, BYTE [rbx + rax * QUEUE_ELEMENT_SIZE_IN_BYTE]  ; Load the element at the front index

    xor rcx, rcx 
    mov cl, al                                                ; Because rax often used as a return value
    
    ; Print peeked message, if verbosity is enabled
    mov r10, OPERATION_VERBOSITY
    cmp r10, TRUE
    je .printPeekedMessage
    jmp .returnPeekedValue

    .printPeekedMessage:
        lea rdi, [formatStringPeeked]
        movzx rsi, cl
        xor rax, rax
        call printf
        jmp .returnPeekedValue

    .returnPeekedValue:
        xor rax, rax
        movzx rax, cl                                          ; Return peeked value
        leave
        ret

    .queueEmptyException:
        lea rdi, [formatStringQueueEmpty]
        xor rax, rax
        call printf
        mov rax, -1        ; Return -1 if the queue is empty
        leave
        ret

; Subroutine to display the queue pretty
; @param ($rdi) queuePointer: Pointer to the queue structure
; Example output)
; |   |   | A | B | C |   |   |   |   |   | (Blank spaces are empty elements)
displayQueue:
    push rbp
    mov rbp, rsp
    sub rsp, 32                                             ; Stack alignment + store queue indices

    ; Print the queue elements
    xor rax, rax
    mov QWORD [rsp], rdi                                    ; Store the queuePointer ($rsp)
    mov DWORD eax, [rdi + queue.queueFrontIndex]            
    mov DWORD [rsp + 8], eax                                ; Store the front index ($rsp + 8)
    mov DWORD eax, [rdi + queue.queueRearIndex]             
    mov DWORD [rsp + 12], eax                               ; Store the rear index ($rsp + 12)
    mov DWORD [rsp + 16], 0                                 ; Initialize the loop counter ($rsp + 16)
    mov DWORD eax, [rdi + queue.queueCapacity]              
    mov DWORD [rsp + 20], eax                               ; Store the capacity ($rsp + 20)

    ; Print the queue stats
    lea rdi, [formatStringQueueDisplayStats]
    xor rsi, rsi
    xor rdx, rdx
    xor rcx, rcx
    mov esi, DWORD [rsp + 8]                                ; Front index
    mov edx, DWORD [rsp + 12]                               ; Rear index
    mov ecx, DWORD [rsp + 20]                               ; Capacity
    xor rax, rax
    call printf

    ; Print the front wall
    lea rdi, [formatStringQueueDisplayFront]
    xor rax, rax
    call printf

    .displayQueueLoop:
        xor rax, rax
        mov eax, DWORD [rsp + 20]                           ; Load the capacity
        cmp DWORD [rsp + 16], eax                           ; Check if the loop counter is equal to the queue capacity
        je .exit

        ; if (index >= queueFrontIndex && index <= queueRearIndex) { print element; }
        ; else { print blank space; }
        mov rdi, QWORD [rsp]
        mov eax, DWORD [rsp + 16]                           ; Loop counter (index) 
        mov ebx, DWORD [rsp + 8]                            ; Front index
        mov ecx, DWORD [rsp + 12]                           ; Rear index
        
        cmp eax, ebx
        jle .printBlankSpace                                ; if (index < queueFrontIndex) { print blank space; }

        cmp eax, ecx
        jge .printBlankSpace                                ; if (index > queueRearIndex) { print blank space; }

        ; Print the element
        lea rdi, [formatStringQueueDisplayElement]
        mov QWORD rcx, [rsp]                                ; Load the queuePointer then extract the element(byte) from the queueArray
        movzx rsi, BYTE [rcx + queue.queueArray + rax * QUEUE_ELEMENT_SIZE_IN_BYTE]
        xor rax, rax
        call printf

        jmp .incrementLoopCounter

        .printBlankSpace:
            ; Print blank space
            lea rdi, [formatStringQueueDisplayVoid]
            xor rax, rax
            call printf

        .incrementLoopCounter:
            inc DWORD [rsp + 16]
            jmp .displayQueueLoop

    .exit:
        ; Print new line
        lea rdi, [formatStringNewLine]
        xor rax, rax
        call printf

        leave
        ret

; Memory for the queue is allocated
; Front: -1, Rear:  0, Capacity:  10 => |   |   |   |   |   |   |   |   |   |   | 
; Front: -1, Rear:  1, Capacity:  10 => | A |   |   |   |   |   |   |   |   |   | 
; Front: -1, Rear:  2, Capacity:  10 => | A | B |   |   |   |   |   |   |   |   | 
; Front: -1, Rear:  3, Capacity:  10 => | A | B | C |   |   |   |   |   |   |   | 
; Front: -1, Rear:  4, Capacity:  10 => | A | B | C | D |   |   |   |   |   |   | 
; Front: -1, Rear:  5, Capacity:  10 => | A | B | C | D | E |   |   |   |   |   | 
; Front: -1, Rear:  6, Capacity:  10 => | A | B | C | D | E | F |   |   |   |   | 
; Front: -1, Rear:  7, Capacity:  10 => | A | B | C | D | E | F | G |   |   |   | 
; Front: -1, Rear:  8, Capacity:  10 => | A | B | C | D | E | F | G | H |   |   | 
; Peeked: A
; Front:  0, Rear:  8, Capacity:  10 => |   | B | C | D | E | F | G | H |   |   | 
; Front:  1, Rear:  8, Capacity:  10 => |   |   | C | D | E | F | G | H |   |   | 
; Front:  2, Rear:  8, Capacity:  10 => |   |   |   | D | E | F | G | H |   |   | 
; Front:  3, Rear:  8, Capacity:  10 => |   |   |   |   | E | F | G | H |   |   | 
; Front:  4, Rear:  8, Capacity:  10 => |   |   |   |   |   | F | G | H |   |   | 
; Front:  5, Rear:  8, Capacity:  10 => |   |   |   |   |   |   | G | H |   |   | 
; Peeked: G
; Memory for the queue is deallocated