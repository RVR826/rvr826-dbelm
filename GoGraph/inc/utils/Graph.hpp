#pragma once

#include <algorithm>
#include <iostream>
#include <metis.h>
#include "graph_parts.hpp"

namespace GoGraph::Utils
{

	template<int VertexCount, int EdgeCount>
	class Graph 
	{
		using EdgeArray = std::array<WeightedEdge, EdgeCount>;

	public:
		Graph(const EdgeArray& f_edges);

		inline GraphIterator<VertexCount, EdgeCount> begin() const
		{
			std::array<int, VertexCount> processOrder{};
			for (int i = 0; i < VertexCount; i++)
			{
				processOrder[i] = i;
			}

			return GraphIterator<VertexCount, EdgeCount>{
				processOrder, & m_rowPtr, & m_rowIdx, & m_colPtr, & m_colIdx, & m_edgeWeights
			};
		}

		inline GraphIterator<VertexCount, EdgeCount> end() const
		{
			return GraphIterator<VertexCount, EdgeCount>();
		}

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