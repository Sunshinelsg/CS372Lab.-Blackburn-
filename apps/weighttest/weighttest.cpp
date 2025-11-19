//
// File:   graphtest.cpp
// Author: Your Glorious Instructor
// Purpose:
// Use GoogleTest to unit test a set of graph classes.
//
#include <gtest/gtest.h>
#include "ALWGraph.hpp"
#include "AMWGraph.hpp"

#include <iostream>
#include <string>
#include <tuple>
#include <vector>

// Test fixtures manage the state of the test.
// Here we use it to create and delete a list of employees for testing
// purposes.   Test fixtures are subclass of the ::testing::Test class, with
// all contents set as protected.   As we are using member
// variables not allocated on the heap, no need to do any
// special setup or teardown.  Do need to use the TEST_F() macro
// rather TEST()

class WGraphTestSuite : public ::testing::Test
{
protected:
  WeightedAdjListGraph<int> testALG;
  void SetUp() override
  {
    testALG.addNode(0);
    testALG.addNode(1);
    testALG.addNode(2);
    testALG.addNode(3);

    testALG.addEdge(0, 1);
    testALG.addEdge(0, 2);
    testALG.addEdge(0, 3);

    testALG.addEdge(1, 0);
    testALG.addEdge(1, 2);
    testALG.addEdge(1, 3);

    testALG.addEdge(2, 0);
    testALG.addEdge(2, 1);
    testALG.addEdge(2, 3);

    testALG.addEdge(3, 0);
    testALG.addEdge(3, 1);
    testALG.addEdge(3, 2);

  }

  void TearDown() override
  {
    // No tear down required.
  }
};

// Test: fill an adj list graph with data
// Precondition: Graph is empty
// Postcondition: Graph is filled per test
TEST_F(WGraphTestSuite, BuildAL)
{
  WeightedAdjListGraph<int> *g = new WeightedAdjListGraph<int>();
  g->addNode(0);
  g->addNode(1);
  g->addNode(2);
  g->addNode(3);

  g->addEdge(0, 1);
  g->addEdge(0, 2);
  g->addEdge(0, 3);

  g->addEdge(1, 0);
  g->addEdge(1, 2);
  g->addEdge(1, 3);

  g->addEdge(2, 0);
  g->addEdge(2, 1);
  g->addEdge(2, 3);

  g->addEdge(3, 0);
  g->addEdge(3, 1);
  g->addEdge(3, 2);

  g->deleteEdge(2, 1);

  EXPECT_TRUE(g->adjacent(2, 0));
  EXPECT_FALSE(g->adjacent(2, 1));
  delete g;
}

// Test: fill an adj list graph with data, treating as parent class
// Precondition: Graph is empty
// Postcondition: Graph is filled per test
TEST_F(WGraphTestSuite, BuildALWithWeights)
{
  WeightedAdjListGraph<int> *g = new WeightedAdjListGraph<int>();
  g->addNode(0);
  g->addNode(1);
  g->addNode(2);
  g->addNode(3);

  g->addEdgeWithWeight(0, 1, 1);
  g->addEdgeWithWeight(0, 2, 2);
  g->addEdgeWithWeight(0, 3, 3);

  g->addEdgeWithWeight(1, 0, 1);
  g->addEdgeWithWeight(1, 2, 2);
  g->addEdgeWithWeight(1, 3, 3);

  g->addEdgeWithWeight(2, 0, 1);
  g->addEdgeWithWeight(2, 1, 2);
  g->addEdgeWithWeight(2, 3, 3);

  g->addEdgeWithWeight(3, 0, 1);
  g->addEdgeWithWeight(3, 1, 2);
  g->addEdgeWithWeight(3, 2, 3);
 
  g->deleteEdge(2, 1);

  EXPECT_TRUE(g->adjacent(2, 0));
  EXPECT_FALSE(g->adjacent(2, 1));
  delete g;
}

// Test: fill an adj list graph with data, treating as parent class
// Precondition: Graph is empty
// Postcondition: Graph is filled per test
TEST_F(WGraphTestSuite, BuildAMWithWeights)
{
    WeightedAdjMatrixGraph<int>* g = new WeightedAdjMatrixGraph<int>();
    g->addNode(0);
    g->addNode(1);
    g->addNode(2);
    g->addNode(3);

    g->addEdgeWithWeight(0, 1, 1);
    g->addEdgeWithWeight(0, 2, 2);
    g->addEdgeWithWeight(0, 3, 3);

    g->addEdgeWithWeight(1, 0, 1);
    g->addEdgeWithWeight(1, 2, 2);
    g->addEdgeWithWeight(1, 3, 3);

    g->addEdgeWithWeight(2, 0, 1);
    g->addEdgeWithWeight(2, 1, 2);
    g->addEdgeWithWeight(2, 3, 3);

    g->addEdgeWithWeight(3, 0, 1);
    g->addEdgeWithWeight(3, 1, 2);
    g->addEdgeWithWeight(3, 2, 3);

    g->deleteEdge(2, 1);

    EXPECT_TRUE(g->adjacent(2, 0));
    EXPECT_FALSE(g->adjacent(2, 1));
    delete g;
}


// 
// Test: Get a list of neighbors out of a Graph
// Precondition: Graph is empty
// Postcondition: Graph is filled per test
TEST_F(WGraphTestSuite, NeighborsInAL)
{
  std::vector<int> expected = { 1, 2, 3};
  std::vector<int> neighvec = testALG.neighbors(0);
  EXPECT_TRUE(neighvec == expected);
}


// Test: DFS traversal of a graph
// Precondition: Two graphs, an AdjList and AdjMatrix are available
// Postconition: Correct dfs generated for each graph.
TEST_F(WGraphTestSuite, DFS){
    auto visit = [&] (int n) { std::cout << n << " "; };
    std::cout << "DFS traversal:\n";
    testALG.dfs(0, visit);
}

// Test: BFS traversal of a graph
// Precondition: Two graphs, an AdjList and AdjMatrix are available
// Postconition: Correct bfs generated for each graph.
TEST_F(WGraphTestSuite, BFS){
    auto visit = [&] (int n) { std::cout << n << " "; };
    std::cout << "DFS traversal:\n";
    testALG.bfs(0, visit);
}


// Test: Confirm primary constructor behaves correctly
// Precondition: None
// Postcondition: Graph is built as expected.
TEST_F(WGraphTestSuite, TestPrimaryConstructorAL) {
	std::vector<int> nodes = { 0, 1, 2, 3 };
	std::vector<std::tuple<int, int, int>> edges = {
	  {0, 1, 1}, {0, 2, 2}, {0, 3, 3},
	  {1, 0, 4}, {1, 2, 5}, {1, 3, 6},
	  {2, 0, 7}, {2, 1, 8}, {2, 3, 9},
	  {3, 0, 10}, {3, 1, 11}, {3, 2, 12}
	};
	WeightedAdjListGraph<int> g(nodes, edges);
	EXPECT_TRUE(g.adjacent(2, 0));
	EXPECT_TRUE(g.adjacent(0, 1));
	EXPECT_TRUE(g.adjacent(3, 1));
}

