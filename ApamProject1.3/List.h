#pragma once
#include "Edge.h"

class Node {
public:
    Edge edge = Edge(-1, -1, 0);
    Node* next = nullptr;

    // Default constructor
    Node()
    {
        next = nullptr;
    }

    Node(Edge data)
    {
        this->edge.set_source_vertex(data.get_source_vertex());
        this->edge.set_target_vertex(data.get_target_vertex());
        this->edge.set_weight(data.get_weight());
        this->next = nullptr;
    }
};

// Linked list class
class List {
public:
    Node* head;
    // Default constructor
    List() : head(nullptr) {
    }
    void insertNode(Edge insert_edge);
    void displayList() const;
};

