/**
 * @file linked_list_for_stack_hanoi_problem_visualize.c
 * @brief Source file for the project. Implements the stack via linked list, and solve hanoi tower problem on it.
 *        Additionally, it also demonstrates the usage of the stack-based procedure(subroutine) calls to solve the Hanoi tower problem.
 *        This version of the code also includes the visualization of the disk movement in the Hanoi tower problem.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>

// Define the struct for the node of the linked list
typedef struct HanoiProblemFunctionCall {
    unsigned int disk;
    char sourcePillar;
    char auxiliaryPillar;
    char targetPillar;
} HanoiProblemFunctionCall;

// Define the struct for the node of the linked list
typedef struct HanoiProblemStackNode {
    HanoiProblemFunctionCall data;
    struct HanoiProblemStackNode* next;
} HanoiProblemStackNode;

// Define the struct for the linked list stack
typedef struct HanoiProblemStack {
    HanoiProblemStackNode* top;
    unsigned int size;
} HanoiProblemStack;

// Create a new linked list stack for the Hanoi problem
HanoiProblemStack* createHanoiProblemStack() {
    HanoiProblemStack* hanoiProblemStack = (HanoiProblemStack*)malloc(sizeof(HanoiProblemStack));
    if (hanoiProblemStack == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    hanoiProblemStack->top = NULL;
    hanoiProblemStack->size = 0;
    return hanoiProblemStack;
}

// Check if the linked list stack is empty
bool isHanoiProblemStackEmpty(HanoiProblemStack* hanoiProblemStack) {
    return hanoiProblemStack->size == 0;
}

// Push a new element to the linked list stack
void pushHanoiProblemStack(HanoiProblemStack* hanoiProblemStack,
                           const unsigned int disk,
                           const char sourcePillar,
                           const char auxiliaryPillar,
                           const char targetPillar) {
    HanoiProblemStackNode* newNode = (HanoiProblemStackNode*)malloc(sizeof(HanoiProblemStackNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    newNode->data.disk = disk;
    newNode->data.sourcePillar = sourcePillar;
    newNode->data.auxiliaryPillar = auxiliaryPillar;
    newNode->data.targetPillar = targetPillar;

    // Insert the new node to the top of the linked list stack
    newNode->next = hanoiProblemStack->top;
    hanoiProblemStack->top = newNode;
    hanoiProblemStack->size++;
}

// Pop the top element from the linked list stack
HanoiProblemStackNode* popHanoiProblemStack(HanoiProblemStack* hanoiProblemStack) {
    if (isHanoiProblemStackEmpty(hanoiProblemStack)) {
        fprintf(stderr, "The linked list stack is empty.\n");
        return NULL;
    }

    // Since it's essentially a stack, we can pop the top element by removing the top node
    HanoiProblemStackNode* topNode = hanoiProblemStack->top;
    hanoiProblemStack->top = topNode->next;
    hanoiProblemStack->size--;

    // Don't forget to free the memory of the top node later >_<
    return topNode;
}

// Visualize the entire stack of the Hanoi problem
// to observe the recursive function calls in operating system's perspective
// 
// Example output)
// [Call depth: 1] Disk: 3, Source: A, Auxiliary: B, Target: C
//  |- [Call depth: 2] Disk: 2, Source: A, Auxiliary: C, Target: B
//  |   |- [Call depth: 3] Disk: 1, Source: A, Auxiliary: B, Target: C
// ...
void visualizeHanoiProblemStack(HanoiProblemStack *hanoiProblemStack) {
    HanoiProblemStackNode* currentNode = hanoiProblemStack->top;
    unsigned int currentCallDepth = 1;
    printf("Current total call depth: %u\n", hanoiProblemStack->size);

    while (currentNode != NULL) {
        HanoiProblemFunctionCall currentFunctionCall = currentNode->data;
        for (unsigned int index = 0; index < currentCallDepth; index++)
            printf("   |");

        printf("-[Call depth: %u] Disk: %u, Source: %c, Auxiliary: %c, Target: %c\n",
               currentCallDepth,
               currentFunctionCall.disk,
               currentFunctionCall.sourcePillar,
               currentFunctionCall.auxiliaryPillar,
               currentFunctionCall.targetPillar);
        currentNode = currentNode->next;
        currentCallDepth++;
    }

    // Get the current terminal width and print a separator line in width of the terminal
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    unsigned int terminalWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    for (unsigned int index = 0; index < terminalWidth; index++)
        printf("=");
    printf("\n");
}

static unsigned int diskMovementCounter = 0;

// Print the movement of the disk in the Hanoi tower problem
void moveHanoiDisk(HanoiProblemStack* hanoiProblemStack,
                   const unsigned int disk,
                   const char sourcePillar,
                   const char targetPillar) {
    printf("Move disk %2i from pillar %c to pillar %c\n", disk, sourcePillar, targetPillar);
    visualizeHanoiProblemStack(hanoiProblemStack);
    diskMovementCounter++;
}

// Solve the Hanoi tower problem
void solveHanoiTowerProblem(HanoiProblemStack* hanoiProblemStack,
                            const unsigned int disk,
                            const char sourcePillar,
                            const char auxiliaryPillar,
                            const char targetPillar) {

    // If the stack is not empty, pop the top element each time before proceeding
    // Why? Because we want to visualize the recursive function calls in the stack
    if (!isHanoiProblemStackEmpty(hanoiProblemStack))
        popHanoiProblemStack(hanoiProblemStack);

    // Base case: If there's no disk to move, return
    if (disk == 0)
        return;     

    if (disk == 1) {
        // If there's only one disk to move, move it directly from the source pillar to the target pillar
        pushHanoiProblemStack(hanoiProblemStack, disk, sourcePillar, auxiliaryPillar, targetPillar);
        moveHanoiDisk(hanoiProblemStack, disk, sourcePillar, targetPillar);
    } else {
        // Otherwise, solve the Hanoi tower problem recursively
        solveHanoiTowerProblem(hanoiProblemStack, disk - 1, sourcePillar, targetPillar, auxiliaryPillar);
        
        // Push current function call to the stack to ensure the correct order of the recursive function calls
        // Then, pop the element after moving the disk to the target pillar
        pushHanoiProblemStack(hanoiProblemStack, disk, sourcePillar, auxiliaryPillar, targetPillar);      
        moveHanoiDisk(hanoiProblemStack, disk, sourcePillar, targetPillar);
        popHanoiProblemStack(hanoiProblemStack);

        solveHanoiTowerProblem(hanoiProblemStack, disk - 1, auxiliaryPillar, sourcePillar, targetPillar);
    }

    // We manually do push and pop the stack to visualize the recursive function calls in the stack
    // (Not related to the actual Hanoi tower problem solving algorithm and its functionality)
}


// Solve the Hanoi tower problem
int main(void) {
    HanoiProblemStack* hanoiProblemStack = createHanoiProblemStack();
    solveHanoiTowerProblem(hanoiProblemStack, 3, 'A', 'B', 'C');
    
    printf("The total number of disk movements: %u\n", diskMovementCounter);
    return 0;
}

// Move disk  1 from pillar A to pillar C
// Current total call depth: 1
//    |-[Call depth: 1] Disk: 1, Source: A, Auxiliary: B, Target: C
// ==================================================================================================================================================================================================
// Move disk  2 from pillar A to pillar B
// Current total call depth: 2
//    |-[Call depth: 1] Disk: 2, Source: A, Auxiliary: C, Target: B
//    |   |-[Call depth: 2] Disk: 1, Source: A, Auxiliary: B, Target: C
// ==================================================================================================================================================================================================
// Move disk  1 from pillar C to pillar B
// Current total call depth: 1
//    |-[Call depth: 1] Disk: 1, Source: C, Auxiliary: A, Target: B
// ==================================================================================================================================================================================================
// Move disk  3 from pillar A to pillar C
// Current total call depth: 2
//    |-[Call depth: 1] Disk: 3, Source: A, Auxiliary: B, Target: C
//    |   |-[Call depth: 2] Disk: 1, Source: C, Auxiliary: A, Target: B
// ==================================================================================================================================================================================================
// Move disk  1 from pillar B to pillar A
// Current total call depth: 1
//    |-[Call depth: 1] Disk: 1, Source: B, Auxiliary: C, Target: A
// ==================================================================================================================================================================================================
// Move disk  2 from pillar B to pillar C
// Current total call depth: 2
//    |-[Call depth: 1] Disk: 2, Source: B, Auxiliary: A, Target: C
//    |   |-[Call depth: 2] Disk: 1, Source: B, Auxiliary: C, Target: A
// ==================================================================================================================================================================================================
// Move disk  1 from pillar A to pillar C
// Current total call depth: 1
//    |-[Call depth: 1] Disk: 1, Source: A, Auxiliary: B, Target: C
// ==================================================================================================================================================================================================
// The total number of disk movements: 7