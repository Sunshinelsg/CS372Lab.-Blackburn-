//
//  File:   AdjListGraph.hpp
//  Author: Your Glorious Instructor
//  Purpose:
//  Implementation of the adjacency list implementation of the graph ADT
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
class WeightedAdjListGraph:  public Graph<N> {
private:
    using Edge = tuple<N, N, int>;
    using EdgeList = list<Edge>;
    map<N, EdgeList > vertexMap;
	int numNodes = 0;
public:
    // Default constructor, create empty
    WeightedAdjListGraph() = default;

    // Get the vertex map from the Graph we're copying
    WeightedAdjListGraph(const WeightedAdjListGraph& other) {
        vertexMap = other->vertexMap;
    }

    // Don't forget to overload the assignment operator
    WeightedAdjListGraph& operator= (const WeightedAdjListGraph& source) {
        vertexMap = source.vertexMap;
        return *this;
    }

    // Add the nodes in the list to graph
    WeightedAdjListGraph(vector<N> newNodes, vector<Edge> newEdgeVec) {
        EdgeList * newEdgeList = new EdgeList();
		numNodes = newNodes.size();
        std::copy(newEdgeVec.begin(), newEdgeVec.end(), std::back_inserter(*newEdgeList));
        for (auto it = newNodes.begin();
            it < newNodes.end();
            ++it)
        {
            N node = *it;
            EdgeList* edgesForThisNode = new EdgeList();
            copy_if(
                newEdgeList->begin(),
                newEdgeList->end(),
                std::back_inserter(*edgesForThisNode),
                [node](Edge& anEdge) {
                         return(node == std::get<0>(anEdge));
                }
            );
            vertexMap[node] = *edgesForThisNode;
        }
    }


    // Clean up behind ourselves, we're not doing anything with
    // dynamic memory so can use system provided destructor.
    ~WeightedAdjListGraph() {};

    bool adjacent(N x, N y)  {
        EdgeList edges = vertexMap.at(x);
        tuple<N, N, int> searchEdge(x, y, 0);
        typename EdgeList::const_iterator begin = edges.begin();
        typename EdgeList::const_iterator end = edges.end();
        auto pos = std::find_if(begin, end,
            [&](Edge const& b) {
                bool match = (std::get<0>(b) == std::get<0>(searchEdge))
                    && std::get<1>(b) == std::get<1>(searchEdge);
                return match;
            });
        bool match = false;
        if (pos != end) { match = true; }
        return (match);
    }

    vector<N>& neighbors(N x) {
        vector<N>* nodes = new vector<N>();
        EdgeList edges = vertexMap.at(x);
        for (typename EdgeList::const_iterator it = edges.begin(); it != edges.end(); it++) {
            Edge e = *it;
            nodes->push_back(std::get<1>(e));
        }
        return *nodes;
    }

    void addNode(N node)  {
        EdgeList* newEdgeList = new EdgeList();
        vertexMap[node] = *newEdgeList;
        numNodes++;
    }

    void addEdgeWithWeight(N x, N y, int weight = 0) {
        tuple<N, N, int> forwardEdge = make_tuple(x, y, weight);
        vertexMap[x].push_back(forwardEdge);
		numNodes++;
    }

    void addEdge(N x, N y)  {
        addEdgeWithWeight(x, y, 0);
    }

    void deleteEdgeWithWeight(N x, N y, int weight) {
        Edge forwardEdge = make_tuple(x,y, weight);
        EdgeList edgesAtThisPoint = vertexMap[x];
        auto unusedIt = std::remove_if(edgesAtThisPoint.begin(), edgesAtThisPoint.end(),
            [&](Edge const& b) {
                bool match = (std::get<0>(b) == std::get<0>(forwardEdge))
                    && std::get<1>(b) == std::get<1>(forwardEdge);
                return match;
            });
        vertexMap[x] = edgesAtThisPoint;
    }

    void deleteEdge(N x, N y) {
        deleteEdgeWithWeight(x, y, 0);
    }

    int getEdgeWeight(N x, N y) const {
		EdgeList edges = vertexMap.at(x);
		Edge searchEdge(x, y, 0);
		typename EdgeList::const_iterator begin = edges.begin();
		typename EdgeList::const_iterator end = edges.end();
		auto pos = std::find_if(begin, end,
			[&](Edge const& b) {
				bool match = (std::get<0>(b) == std::get<0>(searchEdge))
					&& std::get<1>(b) == std::get<1>(searchEdge);
				return match;
			});
		int weight = 0;
		if (pos != end) { weight = std::get<2>(*pos); }
		return weight;
    }

    EdgeList getEdges(N aNode) {
		EdgeList edgesAtThisPoint = vertexMap[aNode];
		return edgesAtThisPoint;
    }

    // Traversals
    void dfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;
        stack<N> s;
        for (auto v : vertexMap) {
            visited[v.first] = false;
        }
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
            for (auto neighbor: neighVec ) {
                if (!visited[neighbor]) { s.push(neighbor); }
            }
        }
    }
    
    void bfs(N startNode, std::function<void(N)> visit) {
        map<N, bool> visited;
        for (auto v: vertexMap) {
            visited[v.first] = false;
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
            for (auto neighbor: neighVec) {
                if (!visited[neighbor]) { q.push(neighbor); }
            }
        }
    }
};
