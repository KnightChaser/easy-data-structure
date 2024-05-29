/**
 * @file graph_via_adjacent_matrix_advanced.cpp
 * @brief Graph(data structure) implementation via adjacent matrix approach.
 *        Note that the graph is directed graph.
 *        For convenience, the graph is managed by unordered_map (vertex to index) and vector (index to vertex).
 *        The this->vertexToIndex and indexToVertex mappings help manage the conversion between vertex names and their corresponding indices in the adjacency matrix.
 */
//

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdexcept>

// The vertices and edges will be dynamically allocated
template <typename GraphVertexType>
class GraphViaAdjacentMatrix {
private:
    unsigned int numberOfVertices;                                      // The number of vertices in the graph
    unsigned int numberOfEdges;                                         // The number of edges in the graph
    std::vector<std::vector<bool>> adjacentMatrix;                      // Adjacent matrix to store the edges
    std::unordered_map<GraphVertexType, unsigned int> vertexToIndex;    // Map vertex to index (e.g., "A" -> 0, "B" -> 1, ...)
    std::unordered_map<unsigned int, GraphVertexType> indexToVertex;    // Map index to vertex (e.g., 0 -> "A", 1 -> "B", ...)
public:
    // Constructor to create a graph via adjacent matrix
    GraphViaAdjacentMatrix() {
        numberOfVertices = 0;
        numberOfEdges = 0;
    }

    // Destructor to clear the graph
    ~GraphViaAdjacentMatrix() {
        adjacentMatrix.clear();
        vertexToIndex.clear();
        indexToVertex.clear();
    }

    // Methods
    void addVertex(GraphVertexType vertex);
    void addEdge(GraphVertexType sourceVertex, GraphVertexType destinationVertex, bool isDirected);
    void removeVertex(GraphVertexType vertex);
    void removeEdge(GraphVertexType sourceVertex, GraphVertexType destinationVertex, bool isDirected);
    void displayGraph();
};

// Add a vertex to the graph
template <typename GraphVertexType>
void GraphViaAdjacentMatrix<GraphVertexType>::addVertex(GraphVertexType vertex) {
    if (vertexToIndex.find(vertex) != vertexToIndex.end()) {
        throw std::invalid_argument("Vertex already exists");
    }

    unsigned int index = numberOfVertices;
    vertexToIndex[vertex] = index;
    indexToVertex[index] = vertex;
    numberOfVertices++;
    
    this->adjacentMatrix.resize(numberOfVertices);
    for (unsigned int index = 0; index < numberOfVertices; index++)
        this->adjacentMatrix[index].resize(numberOfVertices);

    // Initialize the new row and column
    for (unsigned int index = 0; index < numberOfVertices; index++) {
        this->adjacentMatrix[numberOfVertices - 1][index] = false;
        this->adjacentMatrix[index][numberOfVertices - 1] = false;
    }
}

// Add an edge to the graph
template <typename GraphVertexType>
void GraphViaAdjacentMatrix<GraphVertexType>::addEdge(GraphVertexType sourceVertex, GraphVertexType destinationVertex, bool isDirected) {
    if (vertexToIndex.find(sourceVertex) == vertexToIndex.end() || vertexToIndex.find(destinationVertex) == vertexToIndex.end()) {
        throw std::out_of_range("Invalid source or destination vertex");
    }

    unsigned int sourceIndex = vertexToIndex[sourceVertex];
    unsigned int destinationIndex = vertexToIndex[destinationVertex];

    this->adjacentMatrix[sourceIndex][destinationIndex] = true;
    this->numberOfEdges++;
    if (!isDirected) {
        // If the edge is undirected, add the reverse edge
        this->adjacentMatrix[destinationIndex][sourceIndex] = true;
        this->numberOfEdges++;      // Considering the reverse edge
    }
}

// Remove a vertex from the graph
template <typename GraphVertexType>
void GraphViaAdjacentMatrix<GraphVertexType>::removeVertex(GraphVertexType vertex) {
    if (vertexToIndex.find(vertex) == vertexToIndex.end()) {
        throw std::out_of_range("Invalid vertex");
    }

    unsigned int indexToRemove = vertexToIndex[vertex];

    // Remove the vertex from the adjacent matrix
    for (unsigned int vertexIndex = 0; vertexIndex < numberOfVertices; vertexIndex++) {
        this->adjacentMatrix[indexToRemove][vertexIndex] = false;
        this->adjacentMatrix[vertexIndex][indexToRemove] = false;
    }

    // Remove the vertex from the graph
    this->adjacentMatrix.erase(this->adjacentMatrix.begin() + indexToRemove);
    for (auto& row : this->adjacentMatrix) {
        row.erase(row.begin() + indexToRemove);
    }

    // Update the mappings
    vertexToIndex.erase(vertex);
    indexToVertex.erase(indexToRemove);

    // Adjust the remaining indices
    for (unsigned int vertexIndex = indexToRemove; vertexIndex < numberOfVertices - 1; vertexIndex++) {
        vertexToIndex[indexToVertex[vertexIndex + 1]]--;
        indexToVertex[vertexIndex] = indexToVertex[vertexIndex + 1];
    }
    indexToVertex.erase(numberOfVertices - 1);

    this->numberOfVertices--;
}

// Remove an edge from the graph
template <typename GraphVertexType>
void GraphViaAdjacentMatrix<GraphVertexType>::removeEdge(GraphVertexType sourceVertex, GraphVertexType destinationVertex, bool isDirected) {
    if (vertexToIndex.find(sourceVertex) == vertexToIndex.end() || vertexToIndex.find(destinationVertex) == vertexToIndex.end()) {
        throw std::out_of_range("Invalid source or destination vertex");
    }

    unsigned int sourceIndex = vertexToIndex[sourceVertex];
    unsigned int destinationIndex = vertexToIndex[destinationVertex];

    this->adjacentMatrix[sourceIndex][destinationIndex] = false;
    this->numberOfEdges--;
    if (!isDirected) {
        // If the edge is undirected, remove the reverse edge
        // Note that removing edge is not removing the vertex
        if (this->adjacentMatrix[destinationIndex][sourceIndex] == true) {
            this->adjacentMatrix[destinationIndex][sourceIndex] = false;
            this->numberOfEdges--;      // Considering the reverse edge
        }
    }
}

// Display the graph via adjacent matrix
template <typename GraphVertexType>
void GraphViaAdjacentMatrix<GraphVertexType>::displayGraph() {
    std::cout << "   ";
    for (unsigned int column = 0; column < numberOfVertices; column++) {
        std::cout << indexToVertex[column] << "  ";
    }
    std::cout << std::endl;
    for (unsigned int row = 0; row < numberOfVertices; row++) {
        std::cout << indexToVertex[row] << "  ";
        for (unsigned int column = 0; column < numberOfVertices; column++) {
            std::cout << (this->adjacentMatrix[row][column] ? "T" : "F") << "  ";
        }
        std::cout << std::endl;
    }
}

int main(void) {
    GraphViaAdjacentMatrix<std::string> graph;
    graph.addVertex("A");
    graph.addVertex("B");
    graph.addVertex("C");
    graph.addVertex("D");
    graph.addVertex("E");
    graph.addVertex("F");

    graph.addEdge("A", "B", true);
    graph.addEdge("B", "C", false);
    graph.addEdge("C", "D", true);
    graph.addEdge("D", "E", true);
    graph.addEdge("E", "A", false);
    graph.addEdge("F", "A", true);
    graph.addEdge("F", "B", false);
    graph.addEdge("F", "C", true);

    graph.displayGraph();

    return 0;
}

//    A  B  C  D  E  F  
// A  F  T  F  F  T  F
// B  F  F  T  F  F  T
// C  F  T  F  T  F  F
// D  F  F  F  F  T  F
// E  T  F  F  F  F  F
// F  T  T  T  F  F  F