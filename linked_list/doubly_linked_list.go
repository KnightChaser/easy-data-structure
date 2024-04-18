// Source: doubly_linked_list.go
// Compare this snippet from linked_list/circular_linked_list.go: now every node has a previous pointer
package main

import (
	"fmt"
)

type DoublyLinkedListNode[DoublyLinkedListNodeType comparable] struct {
	data     DoublyLinkedListNodeType
	next     *DoublyLinkedListNode[DoublyLinkedListNodeType]
	previous *DoublyLinkedListNode[DoublyLinkedListNodeType]
}

type DoublyLinkedList[DoublyLinkedListNodeType comparable] struct {
	head *DoublyLinkedListNode[DoublyLinkedListNodeType]
	size uint32
}

// Creates a new doubly linked list with only one initial node
func NewDoublyLinkedList[DoublyLinkedListNodeType comparable](data DoublyLinkedListNodeType) *DoublyLinkedList[DoublyLinkedListNodeType] {
	initialNode := &DoublyLinkedListNode[DoublyLinkedListNodeType]{data: data}
	return &DoublyLinkedList[DoublyLinkedListNodeType]{head: initialNode, size: 1}
}

// Inserts a new node next to the head node
func (dll *DoublyLinkedList[DoublyLinkedListNodeType]) InsertNextToHead(data DoublyLinkedListNodeType) {
	// ... <-> head <-> newNode <-> ...
	if dll.head == nil {
		fmt.Println("The head of the doubly linked list is nil")
		return
	}

	newNode := &DoublyLinkedListNode[DoublyLinkedListNodeType]{
		data:     data,
		next:     dll.head.next,
		previous: dll.head,
	}

	if dll.head.next != nil {
		dll.head.next.previous = newNode
	}

	dll.head.next = newNode
	dll.size++
}

// Inserts a new node before the head node
func (dll *DoublyLinkedList[DoublyLinkedListNodeType]) InsertBeforeHead(data DoublyLinkedListNodeType) {
	// ... <-> newNode <-> head <-> ...
	newNode := &DoublyLinkedListNode[DoublyLinkedListNodeType]{
		data:     data,
		next:     dll.head,
		previous: nil,
	}

	if dll.head != nil {
		dll.head.previous = newNode
	}

	dll.head = newNode
	dll.size++
}

// Inserts a new node after a node with a specific value
func (dll *DoublyLinkedList[DoublyLinkedListNodeType]) InsertAfterNodeByValue(data DoublyLinkedListNodeType, value DoublyLinkedListNodeType) {
	currentNode := dll.head
	for currentNode != nil {
		if currentNode.data == value {
			// Match found, insert the new node after the current node
			// ... <-> currentNode <-> newNode <-> ...
			newNode := &DoublyLinkedListNode[DoublyLinkedListNodeType]{
				data:     data,
				next:     currentNode.next,
				previous: currentNode,
			}

			// If the current node is not the last node, connect the next node to the new node
			if currentNode.next != nil {
				currentNode.next.previous = newNode
			}

			currentNode.next = newNode
			dll.size++
			return
		}
		currentNode = currentNode.next
	}

	fmt.Printf("Node with value %v not found\n", value)
}

// Deletes a node with a specific value
func (dll *DoublyLinkedList[DoublyLinkedListNodeType]) DeleteNodeByValue(value DoublyLinkedListNodeType) {
	currentNode := dll.head
	for currentNode != nil {
		if currentNode.data == value {
			// Match found, delete the current node
			// ... <-> previousNode <-> currentNode <-> nextNode <-> ...
			if currentNode.previous != nil {
				currentNode.previous.next = currentNode.next
			}

			// If the current node is not the last node, connect the previous node to the next node
			if currentNode.next != nil {
				currentNode.next.previous = currentNode.previous
			}

			dll.size--
			return
		}
		currentNode = currentNode.next
	}

	fmt.Printf("Node with value %v not found\n", value)
}

// Displays the doubly linked list
func (dll *DoublyLinkedList[DoublyLinkedListNodeType]) Display() {
	if dll.size == 0 {
		fmt.Println("The doubly linked list is empty")
		return
	}
	currentNode := dll.head
	for currentNode.next != nil {
		fmt.Printf("%v <-> ", currentNode.data)
		currentNode = currentNode.next
	}

	// Emphasize circularity
	fmt.Printf("%v\n", dll.head.data)
}

func useDoublyLinkedList() {
	dll := NewDoublyLinkedList(1)
	dll.InsertNextToHead(2)
	dll.Display()

	dll.InsertBeforeHead(3)
	dll.Display()

	dll.InsertBeforeHead(4)
	dll.Display()

	dll.InsertAfterNodeByValue(5, 3)
	dll.Display()

	dll.InsertAfterNodeByValue(6, 2)
	dll.Display()

	dll.DeleteNodeByValue(3)
	dll.Display()
}

// 1 <-> 1
// 3 <-> 1 <-> 3
// 4 <-> 3 <-> 1 <-> 4
// 4 <-> 3 <-> 5 <-> 1 <-> 4
// 4 <-> 3 <-> 5 <-> 1 <-> 2 <-> 4
// 4 <-> 5 <-> 1 <-> 2 <-> 4
