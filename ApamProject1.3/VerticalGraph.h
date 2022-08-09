#pragma once
#include "List.h"

class VerticalGraph
{
private:
	int vertex_size = 0;
	List* Adj_array = nullptr;
	int edges_size = 0;
public:
	void makeEmptyGraph(int n, int m);
	bool isAdjacent(int u, int v) const;
	List* getAdjList(int u);
	void addEdge(int u, int v, int c) const;
	void removeEdge(int u, int v);
	void printGraph() const;
	int get_vertex_size() const;
	int get_edges_size() const;
};
