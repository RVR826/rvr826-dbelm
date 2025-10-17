#include "utils/Graph.hpp"

using Edge = GoGraph::Utils::Edge;
using WeightedEdge = GoGraph::Utils::WeightedEdge;

int main()
{
	std::array<WeightedEdge, 6> weightedEdges = {
		WeightedEdge{0, 1, 0.3f}, WeightedEdge{0, 2, 1.1f}, WeightedEdge{1, 2, 0.1f}, WeightedEdge{2, 3, 2.f}, WeightedEdge{3, 4, 1.25f}, WeightedEdge{4, 1, 0.67f}
	};

	GoGraph::Utils::Graph<5, 6> g2{ weightedEdges };

	std::cout << "vc: " << g2.vertexCount() << ", ec: " << g2.edgeCount() << "\n";
	g2.print();

	return 0;
}
