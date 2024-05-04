/**
 * @file linked_list_for_stack_hanoi_problem.c
 * @brief Source file for the project. Implements the stack via linked list, and solve hanoi tower problem on it.
 *        Additionally, it also demonstrates the usage of the stack-based procedure(subroutine) calls to solve the Hanoi tower problem.
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

// Print the movement of the disk in the Hanoi tower problem
void moveHanoiDisk(const unsigned int disk,
                   const char sourcePillar,
                   const char targetPillar) {
    printf("Move disk %2i from pillar %c to pillar %c\n", disk, sourcePillar, targetPillar);
}

// Solve the Hanoi tower problem
void solveHanoiTowerProblem(const unsigned int disk,
                            const char sourcePillar,
                            const char auxiliaryPillar,
                            const char targetPillar) {
    HanoiProblemStack* hanoiProblemStack = createHanoiProblemStack();
    pushHanoiProblemStack(hanoiProblemStack, disk, sourcePillar, auxiliaryPillar, targetPillar);

    // While the stack is not empty, keep solving the Hanoi tower problem
    // The problem will be ultimately solved when the stack is empty
    while (!isHanoiProblemStackEmpty(hanoiProblemStack)) {
        HanoiProblemStackNode* topNode = popHanoiProblemStack(hanoiProblemStack);
        HanoiProblemFunctionCall topFunctionCall = topNode->data;
        free(topNode);

        if (topFunctionCall.disk == 1) {
            // If there is only one disk left, move it directly from the source to the destination!
            moveHanoiDisk(topFunctionCall.disk, topFunctionCall.sourcePillar, topFunctionCall.targetPillar);
        } else {
            // Push the next recursive function calls to the stack
            pushHanoiProblemStack(hanoiProblemStack, topFunctionCall.disk - 1, topFunctionCall.sourcePillar, topFunctionCall.targetPillar, topFunctionCall.auxiliaryPillar);
            moveHanoiDisk(topFunctionCall.disk, topFunctionCall.sourcePillar, topFunctionCall.targetPillar);
            pushHanoiProblemStack(hanoiProblemStack, topFunctionCall.disk - 1, topFunctionCall.auxiliaryPillar, topFunctionCall.sourcePillar, topFunctionCall.targetPillar);
        }
    }
}

// Solve the Hanoi tower problem
int main(void) {
    solveHanoiTowerProblem(3, 'A', 'B', 'C');
    return 0;
}

// Move disk  3 from pillar A to pillar C
// Move disk  2 from pillar B to pillar C
// Move disk  1 from pillar A to pillar C
// Move disk  1 from pillar B to pillar A
// Move disk  2 from pillar A to pillar B
// Move disk  1 from pillar C to pillar B
// Move disk  1 from pillar A to pillar C