/**
 * @file priority_queue_via_max_heap_array.cpp
 * @brief C++ Program to implement Priority Queue using Max Heap
 */
//

#include <iostream>
#include <vector>
#include <stdexcept>

template <typename PriorityQueueElementType>
class PriorityQueueViaMaxHeapArray {
private:
    std::vector<PriorityQueueElementType> maxHeapArray;
    unsigned int size = 0;

    void heapifyUp(unsigned int index);             // Helper method to maintain the heap property after insertion
    void heapifyDown(unsigned int index);           // Helper method to maintain the heap property after removal
    
public:
    void insert(PriorityQueueElementType data);     // Method to insert an element into the priority queue
    PriorityQueueElementType remove();              // Method to remove the element with the highest priority (highest value) from the priority queue
    PriorityQueueElementType getMax();              // Method to get the element with the highest priority (highest value) from the priority queue
    PriorityQueueElementType getMin();              // Method to get the element with the lowest priority (lowest value) from the priority queue
    unsigned int getSize();                         // Method to get the this->size of the priority queue
    void display();                                 // Method to display the elements of the priority queue via level order traversal
};

// Method to insert an element into the priority queue
template <typename PriorityQueueElementType>
void PriorityQueueViaMaxHeapArray<PriorityQueueElementType>::insert(PriorityQueueElementType data) {
    maxHeapArray.push_back(data);
    this->size++;
    heapifyUp(this->size - 1);
}

// Helper method to maintain the heap property after insertion
template <typename PriorityQueueElementType>
void PriorityQueueViaMaxHeapArray<PriorityQueueElementType>::heapifyUp(unsigned int index) {
    while (index > 0) {
        // Note that the max heap is implemented as an array, so the parent index can be calculated as (index - 1) / 2
        unsigned int parentIndex = (index - 1) / 2;
        // If the parent node is less than the current node, swap them to maintain the max heap property
        if (maxHeapArray[parentIndex] < maxHeapArray[index]) {
            std::swap(maxHeapArray[parentIndex], maxHeapArray[index]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

// Method to remove the element with the highest priority (highest value) from the priority queue
template <typename PriorityQueueElementType>
PriorityQueueElementType PriorityQueueViaMaxHeapArray<PriorityQueueElementType>::remove() {
    if (this->size == 0) {
        throw std::out_of_range("Priority Queue is empty");
    }

    // The element with the highest priority is always the root of the max heap
    // So, removing the root element will be removing the first element of the array
    PriorityQueueElementType removedElement = maxHeapArray[0];
    maxHeapArray[0] = maxHeapArray[this->size - 1];                 // Replace the root with the last element of the array
    maxHeapArray.pop_back();                                        // Remove the last element of the array (which was the root)
    this->size--;

    // Maintain the heap property after removal
    // Note that the root element is replaced with the last element of the array (which was the last element of the max heap)
    heapifyDown(0);
    return removedElement;
}

// Helper method to maintain the heap property after removal
template <typename PriorityQueueElementType>
void PriorityQueueViaMaxHeapArray<PriorityQueueElementType>::heapifyDown(unsigned int index) {
    while (index < this->size) {
        // Note that the max heap is implemented as an array, so the left child index can be calculated as 2 * index + 1
        unsigned int leftChildIndex = 2 * index + 1;
        unsigned int rightChildIndex = 2 * index + 2;
        unsigned int maxIndex = index;                      // Assume the current node is the largest

        if (leftChildIndex < this->size && maxHeapArray[leftChildIndex] > maxHeapArray[maxIndex]) {
            // If the left child is greater than the current node, update the max index
            maxIndex = leftChildIndex;
        }
        if (rightChildIndex < this->size && maxHeapArray[rightChildIndex] > maxHeapArray[maxIndex]) {
            // If the right child is greater than the current node, update the max index
            maxIndex = rightChildIndex;
        }
        if (maxIndex == index) {
            // If the current node is the largest, we don't need to do anything because the max heap property is maintained
            break;
        } else {
            // Otherwise, swap the current node with the largest child
            std::swap(maxHeapArray[index], maxHeapArray[maxIndex]);
            index = maxIndex;
        }
    }
}

// Method to get the element with the highest priority (highest value) from the priority queue
template <typename PriorityQueueElementType>
PriorityQueueElementType PriorityQueueViaMaxHeapArray<PriorityQueueElementType>::getMax() {
    if (this->size == 0) {
        throw std::out_of_range("Priority Queue is empty");
    }

    // The element with the highest priority is always the root of the max heap
    return maxHeapArray[0];
}

// Method to get the element with the lowest priority (lowest value) from the priority queue
template <typename PriorityQueueElementType>
PriorityQueueElementType PriorityQueueViaMaxHeapArray<PriorityQueueElementType>::getMin() {
    if (this->size == 0) {
        throw std::out_of_range("Priority Queue is empty");
    }
    
    // We just need to iterate through the max heap array to find the minimum element
    PriorityQueueElementType minElement = maxHeapArray[0];
    for (const auto& element : maxHeapArray) {
        if (element < minElement) {
            minElement = element;
        }
    }
    return minElement;
}

// Method to get the this->size of the priority queue
template <typename PriorityQueueElementType>
unsigned int PriorityQueueViaMaxHeapArray<PriorityQueueElementType>::getSize() {
    return this->size;
}

// Method to display the elements of the priority queue via level order traversal
template <typename PriorityQueueElementType>
void PriorityQueueViaMaxHeapArray<PriorityQueueElementType>::display() {
    if (this->size == 0) {
        throw std::out_of_range("Priority Queue is empty");
    }
    for (unsigned int index = 0; index < this->size; index++) {
        std::cout << maxHeapArray[index] << " ";
    }
    std::cout << std::endl;
}

// Main function
int main() {
    PriorityQueueViaMaxHeapArray<int> priorityQueue;

    int elementsToInsert[] = { 10, 20, 15, 40, 50, 100 };
    for (const auto& element : elementsToInsert) {
        priorityQueue.insert(element);
        priorityQueue.display();
    }

    std::cout << "Element with the highest priority: " << priorityQueue.getMax() << std::endl;
    std::cout << "Element with the lowest priority: " << priorityQueue.getMin() << std::endl;

    std::cout << "Removed element with the highest priority: " << priorityQueue.remove() << std::endl;
    priorityQueue.display();

    return 0;
}

// 10 
// 20 10 
// 20 10 15 
// 40 20 15 10 
// 50 40 15 10 20
// 100 40 50 10 20 15
// Element with the highest priority: 100
// Element with the lowest priority: 10
// Removed element with the highest priority: 100
// 50 40 15 10 20