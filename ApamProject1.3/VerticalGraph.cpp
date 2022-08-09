#include "VerticalGraph.h"

#include <iostream>

#include "Edge.h"


void VerticalGraph::makeEmptyGraph(int n, int m)
{
    vertex_size = n;
    edges_size = m*2;/*u->v & v->u*/
    Adj_array = new List[n + 1]; /*Use 1 to n*/
}

bool VerticalGraph::isAdjacent(int u, int v) const
{
    Node* temp;
    temp = Adj_array[u].head;
    while (temp != nullptr)
    {
        if (temp->edge.get_target_vertex() == v)
            return true;
        temp = temp->next;
    }
    return false;
}

List* VerticalGraph::getAdjList(int u)
{
    return &Adj_array[u];
}

void VerticalGraph::addEdge(int u, int v, int c) const
{
    Edge new_edge(u, v, c);
    Edge _new_edge_(v, u, c);
    Adj_array[u].insertNode(new_edge);
	Adj_array[v].insertNode(_new_edge_);
}

void VerticalGraph::removeEdge(int u, int v)
{
    if (isAdjacent(u, v))
    {
        Node* temp = Adj_array[u].head;
        Node* cur = Adj_array[v].head;
        Node* prev = nullptr;
        if (temp != nullptr && temp->edge.get_target_vertex() == v)
        {
            Adj_array[u].head = temp->next;
            delete temp;
        }
        else
        {
            while (temp != nullptr && temp->edge.get_target_vertex() != v)
            {
                prev = temp;
                temp = temp->next;
            }
            if (temp == nullptr)
                return;
            prev->next = temp->next;
            delete temp;
        }
        if (cur != nullptr && cur->edge.get_target_vertex() == u)
        {
            Adj_array[v].head = cur->next;
            delete cur;
        }
        else
        {
            while (cur != nullptr && cur->edge.get_target_vertex() != u)
            {
                prev = cur;
                cur = cur->next;
            }
            if (cur == nullptr)
                return;
            prev->next = cur->next;
            delete cur;
        }
        this->edges_size-=2;
    }
}

void VerticalGraph::printGraph() const
{
    for (int v = 1; v <= vertex_size; ++v) {
        std::cout << "\n Adjacency list of vertex " << v << std::endl;
        List x = Adj_array[v];
        x.displayList();
        printf("\n");
    }
}

int VerticalGraph::get_vertex_size() const
{
    return this->vertex_size;
}

int VerticalGraph::get_edges_size() const
{
    return this->edges_size;
}
