#include "utils/graph.hpp"
#include "utils/algorithms.hpp"

using WeightedEdge = GoGraph::Utils::WeightedEdge;

int main()
{
	std::array<WeightedEdge, 7> edges = { {
		{0, 1, 1.f},  // a → b
		{0, 4, 4.f},  // a → e
		{1, 2, 6.f},  // b → c
		{1, 4, 1.f},  // b → e
		{4, 3, 2.f},  // e → d
		{3, 2, 1.f},  // d → c
		{2, 4, 4.f}   // c → e
	}};

	GoGraph::Utils::Graph<5, 7> g{ edges };

	GoGraph::Utils::sssp_async(g.begin(), g.end(), 0, true);

	return 0;
}
