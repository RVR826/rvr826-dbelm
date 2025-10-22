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
		{4, 2, 4.f}   // e → c
	}};

	GoGraph::Utils::Graph<5, 7> g{ edges };

	auto dist = GoGraph::Utils::sssp_async(g.begin({0, 1, 4, 2, 3}), g.end(), 0, true);
	std::cout << "Shortest paths:\n";
	for (auto i = 0; i < g.vertexCount(); ++i)
	{
		std::cout << "0 --" << dist[i] << "--> " << i << "\n";
	}

	std::cout << "M() value for default process order: " << GoGraph::Utils::m(g) << "\n";
	std::cout << "M() value for example process order: " << GoGraph::Utils::m(g, { 0, 1, 4, 2, 3 }) << "\n";

	return 0;
}
