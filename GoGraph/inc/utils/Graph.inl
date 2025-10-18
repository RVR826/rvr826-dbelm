#include "graph.hpp"

namespace GoGraph::Utils
{
	template<int VertexCount, int EdgeCount>
	Graph<VertexCount, EdgeCount>::Graph(const EdgeArray& f_edges)
		: m_rowPtr{}
		, m_rowIdx{}
		, m_colPtr{}
		, m_colIdx{}
		, m_edgeWeights{}
	{
		buildAdjacencies(f_edges);
	}

	template<int VertexCount, int EdgeCount>
	std::array<int, VertexCount> Graph<VertexCount, EdgeCount>::partition(int parts) const {
		idx_t n = VertexCount;
		idx_t ncon = 1;
		idx_t nparts = parts;
		idx_t objval;

		// CSR arrays must be idx_t
		std::array<idx_t, VertexCount + 1> xadj{ m_rowPtr };
		std::array<idx_t, EdgeCount> adjncy{ m_colIdx };

		std::array<int, VertexCount> part{};

		METIS_PartGraphKway(&n, &ncon, xadj.data(), adjncy.data(),
			nullptr, nullptr, nullptr, &nparts,
			nullptr, nullptr, nullptr, &objval, part.data());

		return part;
	}

	template<int VertexCount, int EdgeCount>
	void Graph<VertexCount, EdgeCount>::buildAdjacencies(const EdgeArray& f_edges)
	{
		for (const auto& e : f_edges)
		{
			m_rowPtr[e.m_from + 1]++;
			m_colPtr[e.m_to + 1]++;
		}

		for (auto i = 1; i <= VertexCount; ++i)
		{
			m_rowPtr[i] += m_rowPtr[i - 1];
			m_colPtr[i] += m_colPtr[i - 1];
		}

		std::array<int, VertexCount + 1> tempRowPtr{ m_rowPtr };
		std::array<int, VertexCount + 1> tempColPtr{ m_colPtr };
		for (const auto& e : f_edges) 
		{
			const auto rowPos = tempRowPtr[e.m_from]++;
			
			m_colIdx[rowPos] = e.m_to;
			m_rowIdx[tempColPtr[e.m_to]++] = e.m_from;

			m_edgeWeights[rowPos] = e.m_weight;
		}
	}

	template<int VertexCount, int EdgeCount>
	void Graph<VertexCount, EdgeCount>::print() const
	{
		for (auto v = 0; v < VertexCount; ++v)
		{
			std::cout << "Outgoing neighbors of " << v << ": (" << getOutDegree(v) << ")\n";
			for (auto i = m_rowPtr[v]; i < m_rowPtr[v + 1]; ++i)
			{
				std::cout << v << " -> " << m_colIdx[i] << " w: " << m_edgeWeights[i] << "\n";
			}

			std::cout << "Incoming neighbors of " << v << ": (" << getInDegree(v) << ")\n";
			for (auto i = m_colPtr[v]; i < m_colPtr[v + 1]; ++i)
			{
				std::cout << m_rowIdx[i] << " -> " << v << "\n";
			}
			std::cout << "\n";
		}
	}

} // namespace GoGraph::Utils