#include "List.h"
#include <iostream>

void List::insertNode(Edge insert_edge)
{
	Node* newNode = new Node(insert_edge);
	if (head == nullptr)
	{
		head = newNode;
		return;
	}
	Node* temp = head;
	while (temp->next != nullptr)
	{
		temp = temp->next;
	}
	// Insert at the last.
	temp->next = newNode;
}

void List::displayList() const
{
	Node* temp = head;

	// Check for empty list.
	if (head == nullptr) {
		std::cout << "List empty" << std::endl;
		return;
	}

	// Traverse the list.
	while (temp != nullptr) {
		std::cout << temp->edge.get_source_vertex() << " -> " << temp->edge.get_target_vertex() << " ,Weight: " << temp->edge.get_weight() << std::endl;
		temp = temp->next;
	}
}
