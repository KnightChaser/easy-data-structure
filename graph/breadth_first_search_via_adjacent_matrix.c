/**
 * @file breadth_first_search_via_adjacent_matrix.c
 * @brief Breadth First Search (BFS) for graph implemented using Adjacent Matrix
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// ----------------------- Queue components -----------------------

// Queue structure (Represent a queue that stores the vertices during BFS)
typedef unsigned int QueueElement;
typedef struct queue {
    unsigned int frontIndex;
    unsigned int rearIndex;
    unsigned int currentSize;
    unsigned int capacity;
    QueueElement* array;
} Queue;


// Create a queue
Queue* createQueue(unsigned int capacity) {
    Queue* queue        = (Queue*) malloc(sizeof(Queue));
    queue->capacity     = capacity;
    queue->frontIndex   = 0;
    queue->currentSize  = 0;
    queue->rearIndex    = capacity - 1;
    queue->array = (QueueElement*) malloc(queue->capacity * sizeof(QueueElement));
    return queue;
}

// Check if the queue is full
bool isQueueFull(Queue* queue) {
    return queue->currentSize == queue->capacity;
}

// Check if the queue is empty
bool isQueueEmpty(Queue* queue) {
    return queue->currentSize == 0;
}

// Enqueue an element to the queue
void enqueue(Queue* queue, QueueElement element) {
    if (isQueueFull(queue)) {
        fprintf(stderr, "Queue is full\n");
        return;
    }
    queue->rearIndex = (queue->rearIndex + 1) % queue->capacity;
    queue->array[queue->rearIndex] = element;
    queue->currentSize++;
}

// Dequeue an element from the queue
QueueElement dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        fprintf(stderr, "Queue is empty\n");
        return -1;
    }
    QueueElement element = queue->array[queue->frontIndex];
    queue->frontIndex = (queue->frontIndex + 1) % queue->capacity;
    queue->currentSize--;
    return element;
}

// ----------------------- Graph components ------------------------

// Edge structure (Represent a single edge in the graph)
typedef struct edge {
    unsigned int sourceEdge;
    unsigned int destinationEdge;
    bool isDirected;                    // Directed or undirected edge (If directed, source -> destination, otherwise source <-> destination)
} Edge;

// Graph structure (Represent a graph)
typedef struct graphViaAdjacentMatrix {
    unsigned int numberOfVertices;      // The number of vertices in the graph
    unsigned int numberOfEdges;         // The number of edges in the graph
    bool adjacentMatrix[MAX_VERTICES][MAX_VERTICES];
} GraphViaAdjacentMatrix;

// Create a graph via adjacent matrix
GraphViaAdjacentMatrix* createGraphViaAdjacentMatrix(unsigned int vertices) {
    GraphViaAdjacentMatrix* graph = (GraphViaAdjacentMatrix*) malloc(sizeof(GraphViaAdjacentMatrix));
    graph->numberOfVertices = vertices;
    graph->numberOfEdges = 0;
    for (unsigned int row = 0; row < vertices; row++) {
        for (unsigned int column = 0; column < vertices; column++) {
            graph->adjacentMatrix[row][column] = false;
        }
    }
    return graph;
}

// Add an edge to the graph
void addEdgeToGraphViaAdjacentMatrix(GraphViaAdjacentMatrix* graph, Edge* edge) {
    if (edge->sourceEdge < graph->numberOfVertices && edge->destinationEdge < graph->numberOfVertices) {
        graph->adjacentMatrix[edge->sourceEdge][edge->destinationEdge] = true;
        if (!edge->isDirected) {
            // If the edge is undirected, add the reverse edge
            graph->adjacentMatrix[edge->destinationEdge][edge->sourceEdge] = true;
            graph->numberOfEdges++;     // Consider the reverse edge as well
        }
        graph->numberOfEdges++;
    } else {
        fprintf(stderr, "Invalid edge source or destination\n");
    }
}

// Print the graph via adjacent matrix
void printGraphViaAdjacentMatrix(GraphViaAdjacentMatrix* graph) {
    printf("    ");
    for (unsigned int column = 0; column < graph->numberOfVertices; column++) {
        printf("%02d  ", column);
    }
    printf("\n");
    for (unsigned int row = 0; row < graph->numberOfVertices; row++) {
        printf("%02d  ", row);
        for (unsigned int column = 0; column < graph->numberOfVertices; column++) {
            printf("%c   ", graph->adjacentMatrix[row][column] ? 'T' : 'F');
        }
        printf("\n");
    }
}

// Breadth First Search (BFS) for the graph via adjacent matrix in iterative way
void breadthFirstSearchIterative(GraphViaAdjacentMatrix* graph, unsigned int sourceVertex) {
    // Create a queue for BFS at the initialization
    Queue* queue = createQueue(graph->numberOfVertices);
    bool visited[graph->numberOfVertices];
    for (unsigned int vertex = 0; vertex < graph->numberOfVertices; vertex++)
        visited[vertex] = false;

    // Mark the current vertex as visited and enqueue it
    visited[sourceVertex] = true;
    enqueue(queue, sourceVertex);

    // Repeat until the vertex queue goes empty
    while (!isQueueEmpty(queue)) {
        unsigned int currentVertex = dequeue(queue);
        printf("VERTEX %d -> ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex currentVertex
        // If an adjacent has not been visited, then mark it visited and enqueue it
        for (unsigned int adjacentVertex = 0; adjacentVertex < graph->numberOfVertices; adjacentVertex++) {
            if (graph->adjacentMatrix[currentVertex][adjacentVertex] && !visited[adjacentVertex]) {
                // Mark the adjacent vertex as visited and enqueue it
                visited[adjacentVertex] = true;
                enqueue(queue, adjacentVertex);
            }
        }
    }

    printf("END\n");
}

int main(void) {
    // Create a graph with 5 vertices
    GraphViaAdjacentMatrix* graph = createGraphViaAdjacentMatrix(5);

    // Add edges to the graph
    Edge edge1 = {0, 1, false};
    Edge edge2 = {0, 2, false};
    Edge edge3 = {1, 2, false};
    Edge edge4 = {1, 3, false};
    Edge edge5 = {2, 3, false};
    Edge edge6 = {3, 4, false};
    addEdgeToGraphViaAdjacentMatrix(graph, &edge1);
    addEdgeToGraphViaAdjacentMatrix(graph, &edge2);
    addEdgeToGraphViaAdjacentMatrix(graph, &edge3);
    addEdgeToGraphViaAdjacentMatrix(graph, &edge4);
    addEdgeToGraphViaAdjacentMatrix(graph, &edge5);
    addEdgeToGraphViaAdjacentMatrix(graph, &edge6);

    // Print the graph
    printGraphViaAdjacentMatrix(graph);

    // Perform Breadth First Search (BFS) from vertex 0
    breadthFirstSearchIterative(graph, 0);

    return 0;
}

//     00  01  02  03  04  
// 00  F   T   T   F   F   
// 01  T   F   T   T   F   
// 02  T   T   F   T   F   
// 03  F   T   T   F   T   
// 04  F   F   F   T   F   
// VERTEX 0 -> VERTEX 1 -> VERTEX 2 -> VERTEX 3 -> VERTEX 4 -> END