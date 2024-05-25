/**
 * @file priority_queue_via_max_heap_stl.cpp
 * @brief C++ Program to implement Priority Queue using Max Heap via STL(Standard Template Library)
 *        With using <queue>, we can easily use the priority queue as a max heap! >_<
 */
//

#include <iostream>
#include <queue>

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

int main(void) {
    std::priority_queue<int> maxHeap;

    // Insert elements into the priority queue
    maxHeap.push(10);
    maxHeap.push(30);
    maxHeap.push(20);
    maxHeap.push(5);
    maxHeap.push(15);

    // Display the elements of the priority queue
    while (!maxHeap.empty()) {
        displayPriorityQueue(maxHeap);
        maxHeap.pop();
    }
    std::cout << std::endl;

    return 0;
}

// Priority Queue elements: 30 20 15 10 5 
// Priority Queue elements: 20 15 10 5
// Priority Queue elements: 15 10 5
// Priority Queue elements: 10 5
// Priority Queue elements: 5