#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <metis.h>

namespace GoGraph::Utils
{

struct Edge
{
	Edge(int f_from, int f_to)
		: m_from{f_from}
		, m_to{f_to} { }


	virtual ~Edge() {}
	
	int m_from;
	int m_to;
};

struct WeightedEdge : public Edge
{
	WeightedEdge(int f_from, int f_to, float f_weight = 0.f)
		: Edge(f_from, f_to)
		, m_weight{f_weight} { }

	float m_weight;
};

template<int VertexCount, int EdgeCount>
class Graph 
{
using EdgeArray = std::array<WeightedEdge, EdgeCount>;

public:
	Graph(const EdgeArray& f_edges);

	inline int vertexCount() const
	{
		return VertexCount;
	}	
	
	inline int edgeCount() const
	{
		return EdgeCount;
	}

	std::array<int, VertexCount> partition(int parts) const;

	void print() const;

	static constexpr int k_invalidVertex{ -1 };

private:
	void buildAdjacencies(const EdgeArray& f_edges);

	inline int getDegree(int v) const
	{
		return getInDegree(v) + getOutDegree(v);
	}

	inline int getInDegree(int v) const
	{
		if (v < 0 || v >= VertexCount)
		{
			return k_invalidVertex;
		}

		return m_colPtr[v + 1] - m_colPtr[v];
	}

	inline int getOutDegree(int v) const
	{
		if (v < 0 || v >= VertexCount)
		{
			return k_invalidVertex;
		}

		return m_rowPtr[v + 1] - m_rowPtr[v];
	}

	std::array<int, VertexCount + 1> m_rowPtr;
	std::array<int, EdgeCount> m_rowIdx;
	std::array<int, VertexCount + 1> m_colPtr;
	std::array<int, EdgeCount> m_colIdx;
	std::array<float, EdgeCount> m_edgeWeights;
};
} // namespace GoGraph::Utils

#include "graph.inl"