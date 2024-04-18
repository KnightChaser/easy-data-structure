// file: circular_linked_list.go
// description: A simple circular linked list implementation in Go language

package main

import (
	"C" // To avoid error in VS Code
)
import "fmt"

// Just to avoid error in VS Code

// To provide support for any comparable type, we use the any type constraint
type CircularLinkedListNode[CircularLinkedListNodeType comparable] struct {
	data CircularLinkedListNodeType
	next *CircularLinkedListNode[CircularLinkedListNodeType]
}

type CircularLinkedList[CircularLinkedListNodeType comparable] struct {
	head *CircularLinkedListNode[CircularLinkedListNodeType]
	size uint32
}

// Creates a new circular linked list with only one initial node
func NewCircularLinkedList[CircularLinkedListNodeType comparable](data CircularLinkedListNodeType) *CircularLinkedList[CircularLinkedListNodeType] {
	newNode := &CircularLinkedListNode[CircularLinkedListNodeType]{data: data}
	newNode.next = newNode
	return &CircularLinkedList[CircularLinkedListNodeType]{head: newNode}
}

// Inserts a new node next to the head node
func (cll *CircularLinkedList[CircularLinkedListNodeType]) InsertNextToHeadNode(data CircularLinkedListNodeType) {
	// ... <-> head <-> newNode <-> ...
	newNode := &CircularLinkedListNode[CircularLinkedListNodeType]{data: data}
	newNode.next = cll.head.next
	cll.head.next = newNode
	cll.size++
}

// Inserts a new node before the head node
func (cll *CircularLinkedList[CircularLinkedListNodeType]) InsertBeforeHeadNode(data CircularLinkedListNodeType) {
	// ... <-> newNode <-> head <-> ...
	newNode := &CircularLinkedListNode[CircularLinkedListNodeType]{data: data}
	newNode.next = cll.head
	currentNode := cll.head

	// Traverse to the last node
	for currentNode.next != cll.head {
		currentNode = currentNode.next
	}

	currentNode.next = newNode
	cll.size++
}

// Inserts a new node next to the last node
func (cll *CircularLinkedList[CircularLinkedListNodeType]) InsertNextToLastNode(data CircularLinkedListNodeType) {
	// ... <-> lastNode <-> newNode <-> head <-> ...
	newNode := &CircularLinkedListNode[CircularLinkedListNodeType]{data: data}
	newNode.next = cll.head

	currentNode := cll.head
	// Traverse to the last node
	for currentNode.next != cll.head {
		currentNode = currentNode.next
	}

	currentNode.next = newNode // Connect the last node to the new node
	cll.size++
}

// Inserts a new node before the last node
func (cll *CircularLinkedList[CircularLinkedListNodeType]) InsertBeforeLastNode(data CircularLinkedListNodeType) {
	// ... <-> newNode <-> lastNode <-> head <-> ...
	newNode := &CircularLinkedListNode[CircularLinkedListNodeType]{data: data}
	newNode.next = cll.head

	currentNode := cll.head
	// Traverse to the last node
	for currentNode.next.next != cll.head {
		currentNode = currentNode.next
	}

	newNode.next = currentNode.next
	currentNode.next = newNode
	cll.size++
}

// Inserts a new node next to a node whose data is equal to the given data
func (cll *CircularLinkedList[CircularLinkedListNodeType]) InsertNextToNodeByValue(data CircularLinkedListNodeType, targetData CircularLinkedListNodeType) {
	// ... <-> targetNode <-> newNode <-> ...
	newNode := &CircularLinkedListNode[CircularLinkedListNodeType]{data: data}
	currentNode := cll.head

	// Traverse to the target node having the target data
	for currentNode.data != targetData {
		currentNode = currentNode.next
		if currentNode == cll.head {
			// Target data not found in the list
			fmt.Println("Target data not found in the list")
			return
		}
	}

	newNode.next = currentNode.next
	currentNode.next = newNode
	cll.size++
}

// Inserts a new node before a node whose data is equal to the given data
func (cll *CircularLinkedList[CircularLinkedListNodeType]) InsertBeforeNodeByValue(data CircularLinkedListNodeType, targetData CircularLinkedListNodeType) {
	if cll.size == 0 {
		fmt.Println("List is empty")
		return
	}

	newNode := &CircularLinkedListNode[CircularLinkedListNodeType]{data: data}
	currentNode := cll.head

	for currentNode.next.data != targetData {
		currentNode = currentNode.next
		if currentNode == cll.head {
			// Target data not found in the list
			fmt.Println("Target data not found in the list")
			return
		}
	}

	newNode.next = currentNode.next
	currentNode.next = newNode
	cll.size++
}

// Delets a node whose data is equal to the given data
func (cll *CircularLinkedList[CircularLinkedListNodeType]) DeleteNodeByValue(targetData CircularLinkedListNodeType) {
	currentNode := cll.head

	// Traverse to the target node having the target data
	for currentNode.next.data != targetData {
		currentNode = currentNode.next
	}

	currentNode.next = currentNode.next.next
	cll.size--
	// Golang has a garbage collector, so we don't need to manually free the memory
	// It's convenient, isn't it?
}

// Returns the size of the circular linked list
func (cll *CircularLinkedList[CircularLinkedListNodeType]) Size() uint32 {
	return cll.size
}

// Print the entire circular linked list
func (cll *CircularLinkedList[CircularLinkedListNodeType]) Display() {
	currentNode := cll.head
	for index := 0; index < int(cll.size); index++ {
		fmt.Printf("%v -> ", currentNode.data)
		currentNode = currentNode.next
	}
	// Emphasize the circularity, so we print the head node again
	fmt.Printf("%v\n", cll.head.data)
}

func usageCircularLinkedList() {
	cll := NewCircularLinkedList[int](1)
	cll.InsertNextToHeadNode(2)
	cll.InsertNextToHeadNode(3)
	cll.InsertBeforeHeadNode(4)
	cll.InsertNextToLastNode(5)
	cll.InsertBeforeLastNode(6)
	cll.InsertNextToNodeByValue(7, 2)
	cll.InsertBeforeNodeByValue(8, 5)
	cll.DeleteNodeByValue(4)
	cll.Display()
	fmt.Println("Size:", cll.Size())
}
