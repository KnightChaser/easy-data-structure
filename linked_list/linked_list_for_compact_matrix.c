/**
 * @file linked_list_for_compact_matrix.c
 * @brief A linked list implementation for storing matrices in compact manner.
 *        A compact matrix is a matrix in which most of the elements are zero, so we store only non-zero elements themselves and their positions.
 *        A variation of array/compact_matrix.c
 */
// 

#include <stdio.h>
#include <stdlib.h>

typedef double MatrixElementType;

// A structure that represents a single element in a compact matrix
typedef struct CompactMatrixElement {
    unsigned int rowIndex;
    unsigned int columnIndex;
    MatrixElementType value;
} CompactMatrixElement;

// A structure that represents a single node in a linked list for CompactMatrixElement
typedef struct CompactMatrixNode {
    CompactMatrixElement data;
    struct CompactMatrixNode *next;
} CompactMatrixNode;

// Create a new node with the given data, for starting
CompactMatrixNode* createCompactMatrixNode(CompactMatrixElement data) {
    CompactMatrixNode *newNode = (CompactMatrixNode *)malloc(sizeof(CompactMatrixNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert a new node at the start
CompactMatrixNode* insertCompactMatrixNodeAtStart(CompactMatrixNode *headNode,
                                                  CompactMatrixElement data) {
    CompactMatrixNode *newNode = (CompactMatrixNode *)malloc(sizeof(CompactMatrixNode));
    newNode->data = data;
    newNode->next = headNode;
    headNode = newNode;
    return headNode;
}

// Insert a new node next to the given node
CompactMatrixNode* insertCompactMatrixNodeBehindGivenNode(CompactMatrixNode *headNode,
                                                          CompactMatrixNode *previousNode,
                                                          CompactMatrixElement data) {
    CompactMatrixNode *newNode = (CompactMatrixNode *)malloc(sizeof(CompactMatrixNode));
    newNode->data = data;
    newNode->next = previousNode->next;
    previousNode->next = newNode;
    return headNode;
}

// Insert a new node at the end
CompactMatrixNode* insertCompactMatrixNodeAtEnd(CompactMatrixNode *headNode,
                                                CompactMatrixElement data) {
    CompactMatrixNode *newNode = (CompactMatrixNode *)malloc(sizeof(CompactMatrixNode));
    newNode->data = data;
    newNode->next = NULL;

    // If the given linked list is empty
    if (headNode == NULL) {
        headNode = newNode;
        return headNode;
    }

    // Traverse to the end of the linked list,
    // and insert the new node at the end of the given linked list
    // (We don't have tail pointer, so we need to traverse to the end)
    CompactMatrixNode *currentNode = headNode;
    while (currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    
    currentNode->next = newNode;
    return headNode;
}

// Delete the first node
CompactMatrixNode* deleteCompactMatrixNodeAtStart(CompactMatrixNode *headNode) {
    if (headNode == NULL) {
        fprintf(stderr, "The linked list is empty, so can't delete a new node.\n");
    }

    CompactMatrixNode *tempNode = headNode;
    headNode = headNode->next;
    free(tempNode);
    return headNode;
}

// Delete the node next to the given node
CompactMatrixNode* deleteCompactMatrixNodeBehindGivenNode(CompactMatrixNode *headNode,
                                                            CompactMatrixNode *previousNode) {
    // Range check, if the given node is NULL or the next node is NULL
    if (previousNode == NULL || previousNode->next == NULL) {
        fprintf(stderr, "The given node is NULL or the next node is NULL, so can't delete a new node.\n");
    }

    CompactMatrixNode *tempNode = previousNode->next;
    previousNode->next = tempNode->next;
    free(tempNode);
    return headNode;
}

// Delete the last node
CompactMatrixNode* deleteCompactMatrixNodeAtEnd(CompactMatrixNode *headNode) {
    if (headNode == NULL) {
        fprintf(stderr, "The linked list is empty, so can't delete a new node.\n");
    }

    // Traverse to the end of the linked list, and delete the last node
    // We have to manually traverse the linked list to the end because we don't have a tail pointer
    CompactMatrixNode *currentNode = headNode;              // This node will be kept, as a new tail
    CompactMatrixNode *currentNodeNext = headNode->next;    // This node will be deleted
    while (currentNode->next->next != NULL) {
        currentNode = currentNode->next;
        currentNodeNext = currentNodeNext->next;
    }

    currentNode->next = NULL;
    free(currentNodeNext);
    return headNode;
}

// Display the linked list
void displayCompactMatrix(CompactMatrixNode *headNode) {
    CompactMatrixNode *currentNode = headNode;
    printf("    ");
    while (currentNode != NULL) {
        printf("{ROW => %d, COL => %d, DATA => %f} \n -> ", currentNode->data.rowIndex, currentNode->data.columnIndex, currentNode->data.value);
        currentNode = currentNode->next;
    }
    printf("NULL\n");
}

// Delete the linked list
void deleteCompactMatrix(CompactMatrixNode *headNode) {
    // Traverse the linked list, and delete all nodes sequentially
    CompactMatrixNode *currentNode = headNode;
    while (currentNode != NULL) {
        CompactMatrixNode *tempNode = currentNode;
        currentNode = currentNode->next;
        free(tempNode);
    }
    printf("The linked list is deleted successfully.\n");
}

int main(void) {
    unsigned int sparseMatrixX = 4;     // Number of columns
    unsigned int sparseMatrixY = 5;     // Number of rows
    MatrixElementType** dynamicSparseMatrix = (MatrixElementType**)malloc(sparseMatrixY * sizeof(MatrixElementType*));
    for (unsigned int index = 0; index < sparseMatrixY; index++) {
        dynamicSparseMatrix[index] = (MatrixElementType*)malloc(sparseMatrixX * sizeof(MatrixElementType));
    }

    // Initialize the dynamicSparseMatrix with values manually (for simplicity and safety)
    MatrixElementType sparseMatrixValues[5][4] = {
        {0.0, 0.1, 3.2, 0.0},
        {0.0, 0.0, 5.4, 7.5},
        {0.0, 0.0, 0.0, 0.0},
        {0.0, 2.3, 6.7, 0.0},
        {0.0, 0.0, 0.0, 0.0}
    };

    // y comes first because we want to store the matrix in "row-major order"
    for (unsigned int y = 0; y < sparseMatrixY; y++) {
        for (unsigned int x = 0; x < sparseMatrixX; x++) {
            dynamicSparseMatrix[y][x] = sparseMatrixValues[y][x];
        }
    }

    // Create a linked list for compact matrix after traversing the sparse matrix
    CompactMatrixNode *linkedListFront = NULL;
    CompactMatrixNode *linkedListRear  = NULL;

    for (size_t y = 0; y < sparseMatrixY; y++) {
        for (size_t x = 0; x < sparseMatrixX; x++) {
            if (dynamicSparseMatrix[y][x] != 0) {
                CompactMatrixElement newElement = {x, y, dynamicSparseMatrix[y][x]};
                // Let's compare the outcome of adding data to the front and the rear
                linkedListFront = insertCompactMatrixNodeAtEnd(linkedListFront, newElement);
                linkedListRear = insertCompactMatrixNodeAtStart(linkedListRear, newElement);
            }
        }
    }

    // Print the linked list
    displayCompactMatrix(linkedListFront);  printf("\n");
    displayCompactMatrix(linkedListRear);

    // Delete the linked list
    deleteCompactMatrix(linkedListFront);
    deleteCompactMatrix(linkedListRear);

    // Free the dynamicSparseMatrix memory
    for (unsigned int index = 0; index < sparseMatrixY; index++) {
        free(dynamicSparseMatrix[index]);
    }
    free(dynamicSparseMatrix);

    return 0;
}

//     {ROW => 1, COL => 0, DATA => 0.100000} 
//  -> {ROW => 2, COL => 0, DATA => 3.200000} 
//  -> {ROW => 2, COL => 1, DATA => 5.400000} 
//  -> {ROW => 3, COL => 1, DATA => 7.500000} 
//  -> {ROW => 1, COL => 3, DATA => 2.300000} 
//  -> {ROW => 2, COL => 3, DATA => 6.700000} 
//  -> NULL

//     {ROW => 2, COL => 3, DATA => 6.700000} 
//  -> {ROW => 1, COL => 3, DATA => 2.300000} 
//  -> {ROW => 3, COL => 1, DATA => 7.500000} 
//  -> {ROW => 2, COL => 1, DATA => 5.400000} 
//  -> {ROW => 2, COL => 0, DATA => 3.200000}
//  -> {ROW => 1, COL => 0, DATA => 0.100000}
//  -> NULL
// The linked list is deleted successfully.
// The linked list is deleted successfully.