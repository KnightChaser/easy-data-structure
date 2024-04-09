/**
 * @file linked_list_for_polynomials.c
 * @brief A linked list and its methods implementation for polynomial expression representation and operations.
 */
//

#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the linked list
typedef struct PolynomialNode {
    double coefficient;
    int exponent;
    struct PolynomialNode *next;
} PolynomialNode;

// We don't need tail pointer because struct Polynomial has descending ordered ndoes of exponent.
typedef struct Polynomial {
    PolynomialNode *head;
    unsigned int length;
} Polynomial;

// Create a new polynomial
Polynomial* createPolynomial() {
    Polynomial *polynomial = (Polynomial *)malloc(sizeof(Polynomial));
    polynomial->head = NULL;
    polynomial->length = 0;
    return polynomial;
}

// Insert a new node at the end of the polynomial
// Add a new term to the given polynomial linked list(Expression).
// The node will be added in descending order of the exponent.
void addPolynomialNode(Polynomial *polynomial, const double coefficient, const int exponent) {
    PolynomialNode *newTermNode = (PolynomialNode *)malloc(sizeof(PolynomialNode));
    newTermNode->coefficient = coefficient;
    newTermNode->exponent = exponent;
    newTermNode->next = NULL;

    if (polynomial->head == NULL || polynomial->head->exponent < exponent) {
        // If the polynomial is empty or the new node should be placed before the head 
        // (i.e., the exponent of the new node is greater than the exponent of the head node)
        newTermNode->next = polynomial->head;
        polynomial->head = newTermNode;
    } else {
        // Find the node after which the new node should be inserted
        PolynomialNode *current = polynomial->head;
        while (current->next != NULL && current->next->exponent > exponent) {
            current = current->next;
        }

        // Insert the new node after 'current'
        newTermNode->next = current->next;
        current->next = newTermNode;
    }

    polynomial->length++;
}

// Pretty display the given polynomial linked list like a mathematical expression
void displayPolynomialLinkedList(const Polynomial *polynomial) {
    if (polynomial->head == NULL) {
        fprintf(stderr, "The polynomial is empty.\n");
        return;
    }

    PolynomialNode *currentNode = polynomial->head;
    while (currentNode != NULL) {
        if (currentNode->exponent == 0) {
            // If exponent is 0, just print the coefficient because x^0 = 1
            printf("%f", currentNode->coefficient);
        } else if (currentNode->exponent == 1) {
            // If exponent is 1, no need to print the exponent part because x^1 = x
            printf("%fx", currentNode->coefficient);
        } else {
            printf("%fx^%d", currentNode->coefficient, currentNode->exponent);
        }
        
        // Check if it's not the last node to print the ' + ' symbol
        if (currentNode->next != NULL) {
            printf(" + ");
        }
        
        currentNode = currentNode->next;
    }

    printf("\n"); // New line after displaying the whole polynomial
}

// Add two polynomials. Create a new polynomial that is the sum of the two given polynomials.
Polynomial* addPolynomials(const Polynomial *polynomial1, const Polynomial *polynomial2) {
    Polynomial *result = createPolynomial();
    PolynomialNode *currentNode1 = polynomial1->head;
    PolynomialNode *currentNode2 = polynomial2->head;

    while (currentNode1 != NULL && currentNode2 != NULL) {
        if (currentNode1->exponent == currentNode2->exponent) {
            // If the exponents of the two nodes are equal, add the coefficients and insert to the new node
            addPolynomialNode(result, currentNode1->coefficient + currentNode2->coefficient, currentNode1->exponent);
            currentNode1 = currentNode1->next;
            currentNode2 = currentNode2->next;
        } else if (currentNode1->exponent > currentNode2->exponent) {
            // If the first polynomial has a greater exponent, then just insert the first node to the new node
            addPolynomialNode(result, currentNode1->coefficient, currentNode1->exponent);
            currentNode1 = currentNode1->next;
        } else {
            // If the second polynomial has a greater exponent, then just insert the second node to the new node
            addPolynomialNode(result, currentNode2->coefficient, currentNode2->exponent);
            currentNode2 = currentNode2->next;
        }
    }

    // If there are remaining nodes in the first polynomial
    while (currentNode1 != NULL) {
        addPolynomialNode(result, currentNode1->coefficient, currentNode1->exponent);
        currentNode1 = currentNode1->next;
    }

    // If there are remaining nodes in the second polynomial
    while (currentNode2 != NULL) {
        addPolynomialNode(result, currentNode2->coefficient, currentNode2->exponent);
        currentNode2 = currentNode2->next;
    }

    return result;
}

// Subtract two polynomials. First polynomial - Second polynomial.
// Create a new polynomial that is the difference of the two given polynomials.
Polynomial* subtractPolynomials(const Polynomial *polynomial1, const Polynomial *polynomial2) {
    Polynomial *result = createPolynomial();
    PolynomialNode *currentNode1 = polynomial1->head;
    PolynomialNode *currentNode2 = polynomial2->head;

    while (currentNode1 != NULL && currentNode2 != NULL) {
        if (currentNode1->exponent == currentNode2->exponent) {
            // If the exponents of the two nodes are equal, subtract the coefficients and insert to the new node.
            if (currentNode1->coefficient - currentNode2->coefficient != 0) {
                // If the subtracted coefficient is zero, then the current term is no longer needed.
                addPolynomialNode(result, currentNode1->coefficient - currentNode2->coefficient, currentNode1->exponent);
            }
            currentNode1 = currentNode1->next;
            currentNode2 = currentNode2->next;
        } else if (currentNode1->exponent > currentNode2->exponent) {
            // If the first polynomial has a greater exponent, then just insert the first node to the new node
            addPolynomialNode(result, currentNode1->coefficient, currentNode1->exponent);
            currentNode1 = currentNode1->next;
        } else {
            // If the second polynomial has a greater exponent, then just insert the second node to the new node
            // Be aware that the second polynomial's coefficient should be negated because the second is subtracted from the first.
            addPolynomialNode(result, -currentNode2->coefficient, currentNode2->exponent);
            currentNode2 = currentNode2->next;
        }
    }

    // If there are remaining nodes in the first polynomial
    while (currentNode1 != NULL) {
        addPolynomialNode(result, currentNode1->coefficient, currentNode1->exponent);
        currentNode1 = currentNode1->next;
    }

    // If there are remaining nodes in the second polynomial
    while (currentNode2 != NULL) {
        // Be aware that the second polynomial's coefficient should be negated because the second is subtracted from the first.
        // So we add the "negated" coefficient to the new polynomial.
        addPolynomialNode(result, -currentNode2->coefficient, currentNode2->exponent);
        currentNode2 = currentNode2->next;
    }
    
    return result;
}

// Delete the polynomial linked list
void deletePolynomial(Polynomial *polynomial) {
    PolynomialNode *currentNode = polynomial->head;
    while (currentNode != NULL) {
        PolynomialNode *nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
    free(polynomial);
    printf("The polynomial linked list is deleted successfully.\n");
}

int main(void) {

    // Create a first polynomial
    Polynomial *polynomialA = createPolynomial();
    addPolynomialNode(polynomialA, 4, 2);       // 4x^2
    addPolynomialNode(polynomialA, 2, 3);       // 2x^3
    addPolynomialNode(polynomialA, 3, 8);       // 3x^8
    addPolynomialNode(polynomialA, 4, 1);       // 4x^1
    addPolynomialNode(polynomialA, 5, 0);       // 5x^0
    displayPolynomialLinkedList(polynomialA);                         // 3x^8 + 2x^3 + 4x^2 + 4x + 5


    // Create a second polynomial
    Polynomial *polynomialB = createPolynomial();
    addPolynomialNode(polynomialB, 3, 2);       // 3x^2
    addPolynomialNode(polynomialB, 5, 5);       // 5x^5 
    addPolynomialNode(polynomialB, 2, 3);       // 2x^3
    addPolynomialNode(polynomialB, 1, 4);       // 1x^4
    addPolynomialNode(polynomialB, 4, 1);       // 4x^1
    addPolynomialNode(polynomialB, 5, 0);       // 5x^0
    displayPolynomialLinkedList(polynomialB);                         // 5x^5 + x^4 + 2x^3 + 3x^2 + 4x + 5

    // Add two polynomials; result will be 3x^8 + 5x^5 + x^4 + 4x^3 + 7x^2 + 8x + 10
    Polynomial *added = addPolynomials(polynomialA, polynomialB);
    displayPolynomialLinkedList(added);

    // Subtract(first - second) two polynomials: 3x^8 - 5x^5 - x^4 + x^2
    Polynomial *subtracted = subtractPolynomials(polynomialA, polynomialB);
    displayPolynomialLinkedList(subtracted);


    deletePolynomial(polynomialA);
    deletePolynomial(polynomialB);
    deletePolynomial(added);
    deletePolynomial(subtracted);

    return 0;
}

// 3.000000x^8 + 2.000000x^3 + 4.000000x^2 + 4.000000x + 5.000000
// 5.000000x^5 + 1.000000x^4 + 2.000000x^3 + 3.000000x^2 + 4.000000x + 5.000000
// 3.000000x^8 + 5.000000x^5 + 1.000000x^4 + 4.000000x^3 + 7.000000x^2 + 8.000000x + 10.000000
// The polynomial linked list is deleted successfully.
// The polynomial linked list is deleted successfully.
// The polynomial linked list is deleted successfully.