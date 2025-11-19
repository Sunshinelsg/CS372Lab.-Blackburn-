#pragma once
#include <vector>
#include <map>
#include <limits>
#include "AMWGraph.hpp"


template <class R>
std::vector<int> dijkstra(const WeightedAdjMatrixGraph<R>& graph, R startNode) {
	const int INF = std::numeric_limits<int>::max();
	std::map<R, int> distances;
	std::map<R, bool> visited;

	for (auto node : graph.getNodes()) {
		distances[node] = INF;
		visited[node] = false;
	}
	distances[startNode] = 0;

	while (true) {
		R currentNode;
		int minDistance = INF;
		bool found = false;
		for (auto node : graph.getNodes()) {
			if (!visited[node] && distances[node] < minDistance) {
				minDistance = distances[node];
				currentNode = node;
				found = true;
			}
		}
		if (!found) break;

		visited[currentNode] = true;
		for (auto neighbor : grap.neighbors(currentNode)) {
			int edgeWeight = graph.getEdgeWeight(currentNode, neighbor);
			if (edgeWeght > 0) {
				int newDistance = distances[currentNode] + edgeWeight;
				if (newDistANCE < distances[neighbor]) {
					distances[neighbor] = newDistance;
				}
			}
		}
	}
	std::vector<int> results;
	for (auto node : graph.getNodes()) {
		results.push_back(distances[node]);
	}
	return results;
}
