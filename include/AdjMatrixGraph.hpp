//
//  File:   AdjMatrixGraph.hpp
//  Author: Your Glorious Instructor
//  Purpose:
//  Implementation of the adjacency list implementation of the graph ADT
//
#pragma once
#include <iostream>
#include <vector>
#include <list>
#include "Graph.hpp"

template <class N>
class AdjMatrixGraph: public Graph<N>  {
private:
	std::vector<N> nodes;
    const static int maxSize = 10;
    short adjMatrix[maxSize][maxSize] = {};
    int numNodes = 0;
    int findNodeInMatrix(N x){
        for (int j=0; j < numNodes; ++j)
        {
            if (x == nodes[j])
            {
                return j;
            }
        }
        return -1;
    }
public:
    using Edge = std::pair<N, N>;
    // Default constructor, create empty
	AdjMatrixGraph() = default;

    // Add the nodes in the list to graph
    AdjMatrixGraph(std::vector<N> newNodes, std::vector<Edge> newEdges)
    {
        for (typename std::vector<N>::const_iterator it = newNodes.begin();
             it < newNodes.end();
             ++it)
        {
			numNodes++;
            nodes.push_back(*it);
        }
        for (typename std::vector<pair<N,N>>::const_iterator it = newEdges.begin();
             it < newEdges.end();
             ++it)
        {
            std::pair<N,N> edge = *it;
            int sourceIndex = findNodeInMatrix(edge.first);
            int destIndex = findNodeInMatrix(edge.second);
            if (sourceIndex != -1)
            {
                if (destIndex != -1)
                {
                    adjMatrix[sourceIndex][destIndex] = 1;
                }
            }
        }
    }

    // Clean up behind ourselves
    virtual ~AdjMatrixGraph() = default;
    
    virtual bool adjacent(N x, N y)
    {
        bool result = false;
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        if ((xIndex != -1) && (yIndex != -1))
        {
            short xy = adjMatrix[xIndex][yIndex];
            if (xy == 1) {result = true; };
        }
        return(result);
    }

    virtual std::vector<N>  neighbors(N x)
    {
        std::vector<N> v;
        int xIndex = findNodeInMatrix(x);
        if (xIndex != -1)
        {
            for (int i=0; i < numNodes; ++i) {
                if (adjMatrix[xIndex][i] > 0) {
                    v.push_back(nodes[i]);
                }
            }
        }
        return v;
    }
    virtual void addNode(N node)
    {
        nodes.push_back(node);
        numNodes++;

    }
    virtual void addEdge(N x, N y){
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        if ((xIndex != -1) && (yIndex != -1))
        {
            adjMatrix[xIndex][yIndex] = 1;
        }
    }
    virtual void deleteEdge(N x, N y)
    {
        int xIndex = findNodeInMatrix(x);
        int yIndex = findNodeInMatrix(y);
        adjMatrix[xIndex][yIndex] = 0;
    }

    // Traversals
    void dfs(N startNode, std::function<void(N)> visit) {
        std::map<N, bool> visited;

         for (int i = 0; i < numNodes; ++i){
            visited[nodes[i]] = false;
        }
        std::stack<N> s;
        s.push(startNode);
        while (!s.empty()) {
            N currentNode = s.top();
            s.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            std::vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor: neighVec ) {
                if (!visited[neighbor]) { s.push(neighbor); }
            }
        }
    }
    
    void bfs(N startNode, std::function<void(N)> visit) {
        std::map<N, bool> visited;
        for (int i = 0; i < numNodes; ++i){
            visited[nodes[i]]= false;
        }
        std::queue<N> q;
        q.push(startNode);
        while (!q.empty()) {
            N currentNode = q.front();
            q.pop();
            bool beenVisited = visited[currentNode];
            if (!beenVisited) {
                visit(currentNode);
                visited[currentNode] = true;
            }
            std::vector<N> neighVec = neighbors(currentNode);
            for (auto neighbor: neighVec) {
                if (!visited[neighbor]) { q.push(neighbor); }
            }
        }
    }
};
