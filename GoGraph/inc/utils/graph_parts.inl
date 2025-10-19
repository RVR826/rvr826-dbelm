#pragma once

#include "graph_parts.inl"

namespace GoGraph::Utils
{
	template<int VertexCount, int EdgeCount>
	GraphIterator<VertexCount, EdgeCount>::GraphIterator()
		: m_currentVertex{ -1, std::vector<WeightedEdge>{} }
		, m_processOrder{}
		, m_currentVertexIdx{ 0 }
		, m_rowPtr{ nullptr }
		, m_rowIdx{ nullptr }
		, m_colPtr{ nullptr }
		, m_colIdx{ nullptr }
		, m_edgeWeights{ nullptr } {
	}
	
	template<int VertexCount, int EdgeCount>
	GraphIterator<VertexCount, EdgeCount>::GraphIterator(const std::array<int, VertexCount>& f_processOrder,
		const std::array<int, VertexCount + 1>* f_rowPtr,
		const std::array<int, EdgeCount>* f_rowIdx,
		const std::array<int, VertexCount + 1>* f_colPtr,
		const std::array<int, EdgeCount>* f_colIdx,
		const std::array<float, EdgeCount>* f_edgeWeights)
		: m_currentVertex{}
		, m_processOrder{ f_processOrder }
		, m_currentVertexIdx{ 0 }
		, m_rowPtr{ f_rowPtr }
		, m_rowIdx{ f_rowIdx }
		, m_colPtr{ f_colPtr }
		, m_colIdx{ f_colIdx }
		, m_edgeWeights{ f_edgeWeights } {

		const auto v = m_processOrder[m_currentVertexIdx];
		m_currentVertex.m_v = v;

		for (auto i = (*m_rowPtr)[v]; i < (*m_rowPtr)[v + 1]; ++i)
		{
			m_currentVertex.m_outEdges.push_back(WeightedEdge{ v, (*m_colIdx)[i], (*m_edgeWeights)[i] });
		}
	}
	
	template<int VertexCount, int EdgeCount>
	GraphIterator<VertexCount, EdgeCount>& GraphIterator<VertexCount, EdgeCount>::operator++()
	{
		m_currentVertex.m_outEdges.clear();

		if (++m_currentVertexIdx >= VertexCount)
		{
			m_currentVertex.m_v = -1;
			return *this;
		}

		const auto v = m_processOrder[m_currentVertexIdx];
		m_currentVertex.m_v = v;

		for (auto i = (*m_rowPtr)[v]; i < (*m_rowPtr)[v + 1]; ++i)
		{
			m_currentVertex.m_outEdges.push_back(WeightedEdge{ v, (*m_colIdx)[i], (*m_edgeWeights)[i] });
		}

		return *this;
	}
}