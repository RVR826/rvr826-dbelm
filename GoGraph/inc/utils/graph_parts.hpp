#pragma once

#include <array>
#include <vector>

namespace GoGraph::Utils
{

	struct Edge
	{
		Edge(int f_from, int f_to)
			: m_from{ f_from }
			, m_to{ f_to } {}

		virtual ~Edge() {}

		int m_from;
		int m_to;
	};

	struct WeightedEdge : public Edge
	{
		WeightedEdge(int f_from, int f_to, float f_weight = 0.f)
			: Edge(f_from, f_to)
			, m_weight{ f_weight } {}

		float m_weight;
	};

	struct Vertex
	{
		Vertex(int f_v, std::vector<WeightedEdge>& f_outEdges, std::vector<WeightedEdge>& f_inEdges)
			: m_v{f_v}
			, m_outEdges{f_outEdges}
			, m_inEdges{f_inEdges} { }

		Vertex() = default;

		int m_v;
		std::vector<WeightedEdge> m_outEdges;
		std::vector<WeightedEdge> m_inEdges;
	};

	template<int VertexCount, int EdgeCount>
	class GraphIterator 
	{
	public:
		GraphIterator();

		GraphIterator(const std::array<int, VertexCount>& f_processOrder,
			const std::array<int, VertexCount + 1>* f_rowPtr,
			const std::array<int, EdgeCount>* f_rowIdx,
			const std::array<int, VertexCount + 1>* f_colPtr,
			const std::array<int, EdgeCount>* f_colIdx,
			const std::unordered_map<std::int64_t, float>* f_weightLookup);

		inline const Vertex* operator->() const
		{
			return &m_currentVertex;
		}

		GraphIterator& operator++();

		inline bool operator ==(const GraphIterator& f_rhs) const
		{
			return m_currentVertex.m_v == f_rhs->m_v;
		}

		inline bool operator !=(const GraphIterator& f_rhs) const
		{
			return !(f_rhs == *this);
		}

	private:
		Vertex m_currentVertex;
		
		std::array<int, VertexCount> m_processOrder;
		int m_currentVertexIdx;
		
		const std::array<int, VertexCount + 1>* m_rowPtr;
		const std::array<int, EdgeCount>* m_rowIdx;
		const std::array<int, VertexCount + 1>* m_colPtr;
		const std::array<int, EdgeCount>* m_colIdx;
		const std::unordered_map<std::int64_t, float>* m_weightLookup;
	};
}

#include "graph_parts.inl"