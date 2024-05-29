/**
 * @file breadth_first_search_via_adjacent_list.c
 * @brief Breadth First Search (BFS) for graph implemented using Adjacent List
 */
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdbool.h>

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

// ----------------------- Graph components -----------------------

// Edge structure (Represent an edge in the graph)
typedef struct edge {
    unsigned int sourceVertex;
    unsigned int destinationVertex;
    bool isDirected;
} Edge;

// A single node in the graph (Represent a vertex in the graph)
// A given source vertex can have multiple destination vertices (multiple degrees)
typedef struct graphNode {
    unsigned int vertex;
    struct graphNode* next;
} GraphNode;

// Graph structure
typedef struct graphViaAdjacentList {
    unsigned int numberOfVertices;
    unsigned int numberOfEdges;
    GraphNode** adjacentList;
} GraphViaAdjacentList;

// Create a graph via adjacent list
GraphViaAdjacentList* createGraphViaAdjacentList(unsigned int numberOfVertices) {
    GraphViaAdjacentList* graph = (GraphViaAdjacentList*) calloc(1, sizeof(GraphViaAdjacentList));
    graph->numberOfVertices     = numberOfVertices;
    graph->numberOfEdges        = 0;
    graph->adjacentList         = (GraphNode**) calloc(numberOfVertices, sizeof(GraphNode*));
    return graph;
}

// Add an edge to the graph
void addEdgeToGraphViaAdjacentList(GraphViaAdjacentList* graph, Edge* edge) {
    if (edge->sourceVertex < graph->numberOfVertices && edge->destinationVertex < graph->numberOfVertices) {
        GraphNode* node = (GraphNode*) calloc(1, sizeof(GraphNode));
        node->vertex = edge->destinationVertex;
        node->next = graph->adjacentList[edge->sourceVertex];   // Insert the new node at the beginning, taking only O(1) time   
        graph->adjacentList[edge->sourceVertex] = node;         // Add the node to the front of the linked list
        graph->numberOfEdges++;

        if (!edge->isDirected) {
            // If the edge is undirected, add the reverse edge
            GraphNode* reverseNode = (GraphNode*) calloc(1, sizeof(GraphNode));
            reverseNode->vertex = edge->sourceVertex;
            reverseNode->next = graph->adjacentList[edge->destinationVertex];
            graph->adjacentList[edge->destinationVertex] = reverseNode;     // Add the node to the front of the linked list
            graph->numberOfEdges++;                                         // Consider the reverse edge as well
        }
    } else {
        // Invalid edge source or destination
        fprintf(stderr, "Invalid edge source or destination\n");
    }
}

// Edge and vertex removal is not implemented for brevity

// Breadth First Search (BFS) for the graph (Iterative)
// Breadth First Search (BFS) for the graph (Iterative)
void breadthFirstSearchIterative(GraphViaAdjacentList* graph, unsigned int sourceVertex) {
    // Initialize the data to conduct the BFS
    bool* visited = (bool*) calloc(graph->numberOfVertices, sizeof(bool));
    Queue* bfsQueue = createQueue(graph->numberOfVertices);

    // Enqueue the source vertex and mark it as visited
    enqueue(bfsQueue, sourceVertex);
    visited[sourceVertex] = true;  // Ensure we mark as visited right when enqueueing

    // Continue the BFS until the queue is empty
    while (!isQueueEmpty(bfsQueue)) {
        // Dequeue the current vertex and visit it
        unsigned int currentVertex = dequeue(bfsQueue);
        printf("VERTEX %d -> ", currentVertex);

        // Visit all the adjacent vertices of the current vertex
        GraphNode* adjacentNode = graph->adjacentList[currentVertex];
        while (adjacentNode != NULL) {
            unsigned int adjacentVertex = adjacentNode->vertex;
            if (!visited[adjacentVertex]) {
                enqueue(bfsQueue, adjacentVertex);
                visited[adjacentVertex] = true;  // Mark as visited immediately when enqueuing
            }
            adjacentNode = adjacentNode->next;
        }
    }

    printf("END\n");
}

// Print the graph via adjacent list
void printGraphViaAdjacentList(GraphViaAdjacentList* graph) {
    for (unsigned int vertex = 0; vertex < graph->numberOfVertices; vertex++) {
        printf("VERTEX %d -> ", vertex);
        GraphNode* adjacentNode = graph->adjacentList[vertex];
        while (adjacentNode != NULL) {
            printf("%d ", adjacentNode->vertex);
            adjacentNode = adjacentNode->next;
        }
        printf("\n");
    }
}

int main(void) {
    // Create a graph with 5 vertices
    GraphViaAdjacentList* graph = createGraphViaAdjacentList(5);

    // Add edges to the graph
    Edge edge1 = {0, 1, true};
    Edge edge2 = {0, 2, true};
    Edge edge3 = {1, 2, true};
    Edge edge4 = {2, 0, true};
    Edge edge5 = {2, 3, true};
    Edge edge6 = {3, 3, true};
    Edge edge7 = {3, 4, true};
    addEdgeToGraphViaAdjacentList(graph, &edge1);
    addEdgeToGraphViaAdjacentList(graph, &edge2);
    addEdgeToGraphViaAdjacentList(graph, &edge3);
    addEdgeToGraphViaAdjacentList(graph, &edge4);
    addEdgeToGraphViaAdjacentList(graph, &edge5);
    addEdgeToGraphViaAdjacentList(graph, &edge6);
    addEdgeToGraphViaAdjacentList(graph, &edge7);

    // Print the graph
    printGraphViaAdjacentList(graph);

    // Conduct BFS from the source vertex 2
    printf("BFS from vertex 2: ");
    breadthFirstSearchIterative(graph, 2);

    printf("BFS from vertex 0: ");
    breadthFirstSearchIterative(graph, 0);

    return 0;
}

// VERTEX 0 -> 2 1 
// VERTEX 1 -> 2
// VERTEX 2 -> 3 0
// VERTEX 3 -> 4 3
// VERTEX 4 ->
// BFS from vertex 2: VERTEX 2 -> VERTEX 3 -> VERTEX 0 -> VERTEX 4 -> VERTEX 1 -> END
// BFS from vertex 0: VERTEX 0 -> VERTEX 2 -> VERTEX 1 -> VERTEX 3 -> VERTEX 4 -> END