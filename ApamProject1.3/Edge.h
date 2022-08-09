#pragma once
#include <utility>

class Edge
{
private:
	int source_vertex = -1;
	int target_vertex = -1;
	int weight = 0;

public:
	Edge()
	{
		this->source_vertex = -1;
		this->target_vertex = -1;
		this->weight = 0;
	}
	Edge(int source_vertex, int target_vertex, int weight)
	{
		this->source_vertex = source_vertex;
		this->target_vertex = target_vertex;
		this->weight = weight;
	}

	friend void swap(Edge& lhs, Edge& rhs) noexcept
	{
		using std::swap;
		swap(lhs.source_vertex, rhs.source_vertex);
		swap(lhs.target_vertex, rhs.target_vertex);
		swap(lhs.weight, rhs.weight);
	}

	int get_source_vertex() const
	{
		return source_vertex;
	}

	int get_target_vertex() const
	{
		return target_vertex;
	}

	int get_weight() const
	{
		return weight;
	}

	void set_source_vertex(int source)
	{
		this->source_vertex = source;
	}

	void set_target_vertex(int target)
	{
		this->target_vertex = target;
	}

	void set_weight(int weight)
	{
		this->weight = weight;
	}
};
