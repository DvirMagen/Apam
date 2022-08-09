#pragma once
#include "Edge.h"

/* source_vertex = parent_vertex */
/* target_vertex = index_vertex */
/* weight = min_weight */

class DisjointSet
{
private:
	Edge* s_set = nullptr;
	int set_size = 0;
public:
	DisjointSet(int set_size);
	~DisjointSet();
	void makeSet(int v) const;
	int find_P_vertex(int v);
	void union_vertex(int u, int v);

};

