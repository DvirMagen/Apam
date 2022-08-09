#include "MinPriorityQueue.h"
#include <iostream>

void MinPriorityQueue::fixHeap(int node)
{
	int min;
	int left = Left(node);
	int right = Right(node);
	if ((left < heap_size) && heap[left].get_weight() < heap[node].get_weight())
	{
		min = left;
	}
	else
	{
		min = node;
	}
	if ((right < heap_size) && heap[right].get_weight() < heap[min].get_weight())
	{
		min = right;
	}
	if (min != node)
	{
		swap(heap[node], heap[min]);
		fixHeap(min);
	}
}

void MinPriorityQueue::BuildHeap(Edge* arr, int size)
{
	heap = new Edge[size];
	int i;
	for (i = 0; i < size; i++) {
		heap[i].set_weight(arr[i].get_weight());
		heap[i].set_source_vertex(arr[i].get_target_vertex());
	}
	heap_size = size;
}

Edge MinPriorityQueue::DeleteMin(std::ofstream& output_file)
{
	if (heap_size < 1) {
		output_file << "Invalid input!";
		std::cout << "Invalid Input!";
		output_file.close();
		exit(1);
	}
	else {
		Edge min;
		min.set_weight(heap[0].get_weight());
		min.set_source_vertex(heap[0].get_source_vertex());
		min.set_target_vertex(heap[0].get_target_vertex());
		heap_size--;
		heap[0].set_weight(heap[heap_size].get_weight());
		heap[0].set_source_vertex(heap[heap_size].get_source_vertex());
		heap[0].set_target_vertex(heap[heap_size].get_target_vertex());
		fixHeap(0);
		return min;
	}
}

void MinPriorityQueue::Insert(Edge e, std::ofstream& output_file)
{
	if (heap_size == 1000) {
		std::cout << "Invalid input!";
		output_file << "Invalid input!";
		output_file.close();
		exit(1);
	}
	else {
		int i = heap_size;
		heap_size++;
		while ((i > 0) && ((heap[Parent(i)]).get_weight() > (e.get_weight()))) // checks if my parent is smaller than item to insert.
		{
			heap[i].set_weight(heap[Parent(i)].get_weight());
			heap[i].set_source_vertex(heap[Parent(i)].get_source_vertex());
			heap[i].set_target_vertex(heap[Parent(i)].get_target_vertex());
			i = Parent(i);
		}
		heap[i].set_weight(e.get_weight());
		heap[i].set_source_vertex(e.get_source_vertex());
		heap[i].set_target_vertex(e.get_target_vertex());
	}
}

void MinPriorityQueue::DecreaseKey(int newKey, int Place, std::ofstream& output_file) const
{
	for (int i = 0; i < heap_size; i++) {
		if (heap[i].get_source_vertex() == Place) {
			heap[i].set_weight(newKey);
			while (i != 0 && heap[Parent(i)].get_weight() > heap[i].get_weight())
			{
				swap(heap[i], heap[Parent(i)]);
				i = Parent(i);
			}
			return;
		}
	}
	output_file << "Invalid input!";
	std::cout << "Invalid input!";
	output_file.close();
	exit(1);
}
