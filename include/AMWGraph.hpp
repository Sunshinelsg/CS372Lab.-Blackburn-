//
//  File:   WeightedAdjMatrixGraph.hpp
//  Author: Your Glorious Instructor
//  Purpose:
//  Implementation of the adjacency list representation of the weighted graph ADT
//

#pragma once
#include <map>
#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <stack>
#include <queue>
#include <tuple>
#include <functional>
#include "Graph.hpp"

using namespace std;

template <class N>
class WeightedAdjMatrixGraph: public Graph<N> {
private:
    using Edge = tuple<N, N, int>;
    std::vector<N> nodes;
    const static int maxSize = 10;
    short adjMatrix[maxSize][maxSize] = {};
    int numNodes = 0;
    int findNodeInMatrix(N x) {
        for (int j = 0; j < numNodes; ++j)
        {
            if (x == nodes[j])
            {
                return j;
            }
        }
        return -1;
    }
public:
    // Default constructor, create empty
    WeightedAdjMatrixGraph() {};

    // Add the nodes in the list to graph
    WeightedAdjMatrixGraph(vector<N> newNodes, vector<Edge> newEdgeVec) {
        for (typename vector<N>::const_iterator it = newNodes.begin();
            it < newNodes.end();
            ++it)
        {
            numNodes++;
            nodes.push_back(*it);
        }
        for (typename vector<Edge>::const_iterator it = newEdgeVec.begin();
            it < newEdgeVec.end();
            ++it)
        {
            Edge edge = *it;
            int sourceIndex = findNodeInMatrix(std::get<0>(edge));
            int destIndex = findNodeInMatrix(std::get<1>(edge));
            if (sourceIndex != -1)
            {
                if (destIndex != -1)
                {
                    adjMatrix[sourceIndex][destIndex] = std::get<2>(edge);
                }
            }
        }
    }


    // Clean up behind ourselves, we're not doing anything with
    // dynamic memory so can use system provided destructor.
    ~WeightedAdjMatrixGraph() {};

    bool adjacent(N x, N y) {
        bool result = false;
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        if ((xIndex != -1) && (yIndex != -1))
        {
            short xy = adjMatrix[xIndex][yIndex];
            if (xy == 1) { result = true; };
        }
        return(result);
    }

    vector<N>& neighbors(N x)  {
        vector<N>* v = new vector<N>();
        int xIndex = findNodeInMatrix(x);
        if (xIndex != -1)
        {
            for (int i = 0; i < numNodes; ++i) {
                if (adjMatrix[xIndex][i] > 0) {
                    v->push_back(nodes[i]);
                }
            }
        }
        return *v;
    }

    void addNode(N node)  {
        nodes.push_back(node);
        numNodes++;
    }

    void addEdgeWithWeight(N x, N y, int weight = 0) {
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        if ((xIndex != -1) && (yIndex != -1))
        {
            adjMatrix[xIndex][yIndex] = weight;
        }
    }

	void addEdge(N x, N y) {
        addEdgeWithWeight(x, y, 0);
	}

    void deleteEdgeWithWeight(N x, N y, int weight = 0) {
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        adjMatrix[xIndex][yIndex] = 0;
    }

	void deleteEdge(N x, N y) {
        deleteEdgeWithWeight(x, y, 0);
	}

	int getEdgeWeight(N x, N y) const {
		int xIndex = findNodeInMatrix(x);
		int yIndex = findNodeInMatrix(y);
		return adjMatrix[xIndex][yIndex];
	}

	EdgeList getEdges(N aNode) {
		EdgeList edges;
		int xIndex = findNodeInMatrix(aNode);
		if (xIndex != -1)
		{
			for (int i = 0; i < numNodes; ++i) {
				if (adjMatrix[xIndex][i] > 0) {
					edges.push_back(make_tuple(aNode, nodes[i], adjMatrix[xIndex][i]));
				}
			}
		}
		return edges;
    }

    // Traversals
    void dfs(N startNode, std::function<void(N)> visit)  {
        map<N, bool> visited;

        for (int i = 0; i < numNodes; ++i) {
            visited[nodes[i]] = false;
        }
        stack<N> s;
        s.push(startNode);
        while (!s.empty()) {
            N currentNode = s.top();
            s.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor : neighVec) {
                if (!visited[neighbor]) { s.push(neighbor); }
            }
        }
    }
    
    void bfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;
        for (int i = 0; i < numNodes; ++i) {
            visited[nodes[i]] = false;
        }
        queue<N> q;
        q.push(startNode);
        while (!q.empty()) {
            N currentNode = q.front();
            q.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor : neighVec) {
                if (!visited[neighbor]) { q.push(neighbor); }
            }
        }

    }
};
