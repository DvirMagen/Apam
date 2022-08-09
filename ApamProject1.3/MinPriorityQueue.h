#pragma once
#include <fstream>

#include "Edge.h"

class MinPriorityQueue
{
private:
	Edge* heap = nullptr;
	int heap_size = 0;
	int max_size = 0;
	static int Left(int node) { return (2 * node + 1); }
	static int Right(int node) { return (2 * node + 2); }
	static int Parent(int node) { return (node - 1) / 2; }
	void fixHeap(int node);
public:
	void BuildHeap(Edge* arr, int size);
	bool IsEmpty() const { return heap_size == 0; }
	int  getHeapSize() const { return heap_size; }
	Edge Min() const { return heap[0]; }
	Edge DeleteMin(std::ofstream& output_file);
	void Insert(Edge e, std::ofstream& output_file);
	void DecreaseKey(int newKey, int Place, std::ofstream& output_file) const;
	~MinPriorityQueue() { delete[] heap; }
};



