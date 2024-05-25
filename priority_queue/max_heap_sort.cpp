/**
 * @file max_heap_sort.cpp
 * @brief C++ Program to implement Max Heap Sort Algorithm
 *        To be simple, we use <queue> to implement the max heap sort algorithm.
 */
//

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

// A helper method to display the elements of the priority queue
template <typename PriorityQueueElementType>
void displayPriorityQueue(std::priority_queue<PriorityQueueElementType> maxHeap) {
    std::cout << "Priority Queue elements: ";
    while (!maxHeap.empty()) {
        std::cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    std::cout << std::endl;
}

// A helper method to sort the elements of the priority queue in descending order
template <typename PriorityQueueElementType>
std::vector<PriorityQueueElementType> priorityQueueSortDescending(std::vector<PriorityQueueElementType> elements) {
    // First, we insert the elements into the priority queue
    // Due to the properties of the max heap, the elements will be inserted in descending order
    std::priority_queue<PriorityQueueElementType> maxHeap;
    for (PriorityQueueElementType element : elements) {
        maxHeap.push(element);
    }

    // Then, we extract the elements from the priority queue
    // The elements will be extracted in descending order
    std::vector<PriorityQueueElementType> sortedElements;
    while (!maxHeap.empty()) {
        sortedElements.push_back(maxHeap.top());
        maxHeap.pop();
    }

    return sortedElements;
}

// A helper method to sort the elements of the priority queue in ascending order
template <typename PriorityQueueElementType>
std::vector<PriorityQueueElementType> priorityQueueSortAscending(std::vector<PriorityQueueElementType> elements) {
    // First, we use the priorityQueueSortDescending method to sort the elements in descending order
    std::vector<PriorityQueueElementType> sortedElements = priorityQueueSortDescending(elements);

    // Then, we reverse the order of the elements to get the ascending order
    std::reverse(sortedElements.begin(), sortedElements.end());
    return sortedElements;
}

// A helper method to simply display the elements of a vector
template <typename VectorElementType>
void displayVector(std::vector<VectorElementType> elements) {
    std::cout << "Vector elements: ";
    for (VectorElementType element : elements) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main(void) {
    // Create a vector of integers
    std::vector<int> elements = {5, 3, 8, 4, 1, 2, 9, 7, 6};
    displayVector(elements);

    // Sort the elements in descending order using the priority queue
    std::vector<int> sortedElementsDescending = priorityQueueSortDescending(elements);
    displayVector(sortedElementsDescending);

    // Sort the elements in ascending order using the priority queue
    std::vector<int> sortedElementsAscending = priorityQueueSortAscending(elements);
    displayVector(sortedElementsAscending);

    return 0;
}

// Vector elements: 5 3 8 4 1 2 9 7 6 
// Vector elements: 9 8 7 6 5 4 3 2 1
// Vector elements: 1 2 3 4 5 6 7 8 9