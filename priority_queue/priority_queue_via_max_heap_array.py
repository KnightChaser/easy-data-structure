# file: priority_queue/priority_queue_via_max_heap_array.py
# brief: Priority Queue implementation using Max Heap
#        Max heap is a binary tree where the parent node is greater than its children
#        Max heap can be implemented using an array where the parent node is at index i

from typing import List, Union

class PriorityQueueViaMaxHeapArray:
    def __init__(self) -> None:
        self.heap:List[Union[int, float]] = []

    # Insert a value in the heap
    def insert(self, value:Union[int, float]) -> None:
        self.heap.append(value)
        self._heapify_up()

    # _heapify_up is a helper function to maintain the heap property while inserting a value
    def _heapify_up(self) -> None:
        index:int = len(self.heap) - 1
        while index > 0:
            parent_index:int = (index - 1) // 2
            if self.heap[index] > self.heap[parent_index]:
                # Swap the parent and child node if the child node is greater than the parent node (to keep the max heap property)
                self.heap[index], self.heap[parent_index] = self.heap[parent_index], self.heap[index]
                index = parent_index
            else:
                break

    # Remove the maximum value from the heap
    def remove(self) -> Union[int, float]:
        if len(self.heap) == 0:
            raise ValueError("Heap is empty")
        max_value = self.heap[0]
        self.heap[0] = self.heap[-1]
        self.heap.pop()
        self._heapify_down()
        return max_value
    
    # _heapify_down is a helper function to maintain the heap property while removing the maximum value
    def _heapify_down(self) -> None:
        index:int = 0
        while index < len(self.heap):
            # Find the left and right child index of the current node.
            # Note that this implementation uses an array to represent the heap
            left_child_index:int = 2 * index + 1
            right_child_index:int = 2 * index + 2
            if left_child_index >= len(self.heap):
                # If the left child index is greater than the heap size, then the current node is a leaf node
                break
            if right_child_index >= len(self.heap):
                # If the right child index is greater than the heap size, then the current node has only one child
                right_child_index = left_child_index
            
            max_child_index:int = left_child_index if self.heap[left_child_index] > self.heap[right_child_index] else right_child_index
            if self.heap[index] < self.heap[max_child_index]:
                # Swap the parent and child node if the child node is greater than the parent node (to keep the max heap property)
                self.heap[index], self.heap[max_child_index] = self.heap[max_child_index], self.heap[index]
                # Change the index to the child node index
                index = max_child_index
            else:
                break

    # Get the maximum value from the heap
    def get_max(self) -> Union[int, float]:
        if len(self.heap) == 0:
            raise ValueError("Heap is empty")
        return self.heap[0]
    
    # Get the minimum value from the heap
    def get_min(self) -> Union[int, float]:
        if len(self.heap) == 0:
            raise ValueError("Heap is empty")
        # We just need to iterate through the heap(array) to find the minimum value
        min_value = self.heap[0]
        for value in self.heap:
            if value < min_value:
                min_value = value
        return min_value
    
    # Get the size of the heap
    def size(self) -> int:
        return len(self.heap)
    
    # Print the heap via inorder traversal
    def inorder_traversal(self) -> None:
        self._inorder_traversal(0)

    # Helper function to print the heap via inorder traversal
    def _inorder_traversal(self, index:int) -> None:
        if index >= len(self.heap):
            return
        self._inorder_traversal(2 * index + 1)
        print(self.heap[index], end=" ")
        self._inorder_traversal(2 * index + 2)
        return
    
    # Print the heap via level order traversal
    def level_order_traversal(self) -> None:
        for value in self.heap:
            print(value, end=" ")
        return
    
# Usage
if __name__ == "__main__":
    pq = PriorityQueueViaMaxHeapArray()

    pq.insert(10)
    pq.insert(20)
    pq.insert(15)
    pq.insert(40)
    pq.insert(50)
    pq.insert(100)
    pq.insert(25)
    pq.insert(45)
    pq.insert(30)
    pq.insert(35)
    pq.insert(5)
    pq.insert(60)
    pq.insert(55)
    pq.insert(70)
    pq.insert(80)
    pq.insert(90)
    pq.insert(75)
    pq.insert(65)
    pq.insert(85)
    pq.insert(95)
    
    pq.level_order_traversal()
    print()
    print("Max value:", pq.get_max())
    print("Min value:", pq.get_min())
    print("Size:", pq.size())
    print("Removing max value:", pq.remove())
    print("Max value:", pq.get_max())
    print("Min value:", pq.get_min())
    print("Size:", pq.size())
    pq.level_order_traversal()

# 100 95 80 85 90 55 70 45 75 35 5 15 50 25 60 10 40 30 65 20 
# Max value: 100
# Min value: 5
# Size: 20
# Removing max value: 100
# Max value: 95
# Min value: 5
# Size: 19
# 95 90 80 85 35 55 70 45 75 20 5 15 50 25 60 10 40 30 65