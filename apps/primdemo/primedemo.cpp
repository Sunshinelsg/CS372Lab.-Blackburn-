//
// File:   simplepath.cpp
// Author: Your Glorious Instructor
// Purpose:
// Show that a path is in fact in a graph

#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include <limits>
#include <queue>
#include <utility>
#include "Graph.hpp"
#include "ALWGraph.hpp"

using Edge = std::tuple<int, int, int>;
const int INF = std::numeric_limits<int>::max();


std::vector<int> primMST(WeightedAdjListGraph<int>& aGraph, int startNode, int numNodes) {
	using NodeWeightPair = std::pair<int, int>;
	vector<int> parent(numNodes, 0);
	vector<int> key(numNodes, INF);
	vector<bool> inMST(numNodes, false);
	priority_queue<NodeWeightPair, std::vector<NodeWeightPair>, greater<NodeWeightPair>> pq;
	// Note that we are tacitly assuming that the start node is 0.
	key[0] = 0;
	parent[0] = -1;
	pq.push({0,0});
	while (!pq.empty()) {
		int currentNode = pq.top().second;
		pq.pop();
		inMST[currentNode] = true;
		for (auto aNeighborNode : aGraph.neighbors(currentNode)) {
			int source = currentNode;
			int dest = aNeighborNode ;
			int weight = aGraph.getEdgeWeight(source, dest);
			if (!inMST[dest] && (weight < key[dest]))
			{
				key[dest] = weight;
				parent[dest] = source;
				pq.push({ weight, dest });
			}
		}
	}
	return parent;
}

int main(int argc, char* argv[]) {
	WeightedAdjListGraph<int> aGraph;
	vector<int> nodes = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	vector<Edge> edges = {
		{0, 1, 4},
		{0, 7, 8},
		{1, 2, 8},
		{1, 7, 11},
		{2, 3, 7},
		{2, 8, 2},
		{2, 5, 4},
		{3, 4, 9},
		{3, 5, 14},
		{4, 5, 10},
		{5, 6, 2},
		{6, 7, 1},
		{6, 8, 6},
		{7, 8, 7}
	};
	aGraph = WeightedAdjListGraph<int>(nodes, edges);
	vector<int> parent = primMST(aGraph, 0, 14);
	for (int i = 0; i < parent.size(); ++i) {
		std::cout << parent[i] << std::endl;
	}
	return 0;
}

