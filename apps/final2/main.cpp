#include <iostream>
#include <vector>
#include "AMWGraph.hpp"
#include "final2.hpp"

int main() {
	using GraphType = WeightedAdjMatrixGraph<int>;

	std::vector<int> nodes = { 1, 2, 3, 4, 5 };
	std::vector<GraphType::Edge> edges ={ 
		{1, 2, 10},
		{1, 3, 15},
		{2, 4, 12},
		{3, 5, 10},
		{4, 5, 2},
		{2, 5, 1}
	};
	GraphType graph(nodes, edges);

	int startNode = 1;
	std::vector<int> distances = dijkstra(graph, startNode);


	std::cout << "The shortest distances are: " << std::endl;
	auto nodesInGraph = graph.getEdges(startNode);
	for (size_t i = 0; i < nodes.size(); ++i) {
		std::cout << "Node " << nodes[i] << ": " << distances[i] << std::endl;
	}
	return 0;
}