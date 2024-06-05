/**
 * @file prim_mst_via_priority_queue.cpp
 * @brief Prim's Minimum Spanning Tree Algorithm using Priority Queue (Adjacency List) built with using C++.
 */
//

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_map>
#include <string>

// Define a custom comparator for priority queue
struct Compare {
    bool operator()(const std::tuple<double, std::string, std::string>& edge1,
                    const std::tuple<double, std::string, std::string>& edge2) {
        // Compare the weights of the edges and return if the weight of the first edge is greater than the second's
        return std::get<0>(edge1) > std::get<0>(edge2);
    }
};

// Function to find the Minimum Spanning Tree using Prim's Algorithm
// The graph is represented as <startingVertex, <destinationVertex, weight>>
template <typename EdgeWeightType>      // WeightType is the type of the weight of the edge (int, double, float, etc.)
void primMST(const std::unordered_map<std::string, std::vector<std::pair<std::string, EdgeWeightType>>>& graphAdjacencyList,
             const std::string& startingVertex) {

    // Priority queue to store the edges
    std::priority_queue<std::tuple<EdgeWeightType, std::string, std::string>, 
                        std::vector<std::tuple<EdgeWeightType, std::string, std::string>>, 
                        Compare> priorityQueue;

    // Track the visited vertices for MST
    std::unordered_map<std::string, bool> visitedVertices;

    // Store the weights of the MST edges
    std::vector<std::tuple<std::string, std::string, EdgeWeightType>> mstEdges;

    // Total weight of the MST
    EdgeWeightType mstTotalWeight = 0;

    // Initialize the starting vertex and its adjacencies
    visitedVertices[startingVertex] = true;
    for (const auto& neighbour : graphAdjacencyList.at(startingVertex)) {
        // (weight, startingVertex, destinationVertex)
        priorityQueue.push({neighbour.second, startingVertex, neighbour.first});
    }

    // Loop until the priority queue is empty
    while (!priorityQueue.empty()) {
        EdgeWeightType edgeWeight;
        std::string startingVertex, destinationVertex;
        std::tie(edgeWeight, startingVertex, destinationVertex) = priorityQueue.top();
        priorityQueue.pop();

        // If the destination vertex is already visited, skip the edge
        if (visitedVertices[destinationVertex])
            continue;

        // Include the edge in the MST
        visitedVertices[destinationVertex] = true;
        mstEdges.push_back(std::make_tuple(startingVertex, destinationVertex, edgeWeight));
        mstTotalWeight += edgeWeight;

        // Add the destination vertex's adjacencies to the priority queue
        for (const auto& destinationVertexNeighbour : graphAdjacencyList.at(destinationVertex)) {
            if (!visitedVertices[destinationVertexNeighbour.first]) {
                priorityQueue.push({destinationVertexNeighbour.second, destinationVertex, destinationVertexNeighbour.first});
            }
        }
    }

    // Print
    std::cout << "Minimum Spanning Tree Edges:\n";
    for (const auto& edge : mstEdges) {
        std::cout << "(" << std::get<0>(edge) << ", " << std::get<1>(edge) << ") -> Cost: " << std::get<2>(edge) << "\n";
    }
    std::cout << "Total Weight of MST: " << mstTotalWeight << "\n";
}

int main(void) {
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> graph{
        {"A", {{"B", 2}, {"D", 6}}},
        {"B", {{"A", 2}, {"C", 3}, {"D", 8}, {"E", 5}}},
        {"C", {{"B", 3}, {"E", 7}}},
        {"D", {{"A", 6}, {"B", 8}, {"E", 9}}},
        {"E", {{"B", 5}, {"C", 7}, {"D", 9}}}
    };
    
    primMST(graph, "A");

    return 0;
}

// (A, B) -> Cost: 2
// (B, C) -> Cost: 3
// (B, E) -> Cost: 5
// (A, D) -> Cost: 6
// Total Weight of MST: 16