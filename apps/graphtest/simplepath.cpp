//
// File:   simplepath.cpp
// Author: Your Glorious Instructor
// Purpose:
// Show that a path is in fact in a graph
#include <gtest/gtest.h>

#include <iostream>
#include <functional>
#include <vector>
#include <list>
#include "AdjListGraph.hpp"

bool isValidTour(std::vector<int> maybeTour, Graph<int> &g) {
    bool isGood = true;
    int startNode = maybeTour.front();
    vector<int> neighVec = g.neighbors(startNode);
    if (startNode != maybeTour.back()) {
        isGood = false;
    }
    else {
        int currentPos = 0;
        int pathLength = maybeTour.size();
        while (currentPos != pathLength - 1) {
          int currentNode = maybeTour[currentPos];
          int nextNode = maybeTour[currentPos + 1];
          neighVec = g.neighbors(currentNode);
          std::vector<int>::iterator fIter = std::find(neighVec.begin(), neighVec.end(), nextNode );
          if (fIter == neighVec.end()) {
            isGood = false;
            break;
          }
          currentPos++;
        }
    }
    return isGood;
}

class PathTest : public ::testing::Test
{
protected:
  AdjListGraph<int> testALG;
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

// Test: Check to see if a path is correct 
// for a test graph.
// Precondition: Input path is valid
// Postcondition: A value of true is returned
TEST_F(PathTest, NormalEx) {
    std::vector<int> testPath{0, 1, 2,0};
    bool validPath = isValidTour(testPath, testALG);
    EXPECT_TRUE(validPath);
}
bool isSimpleCycle(Graph& G, const vector<int>& path) {
    int n = path.size();
    if (n < 3) return false;
    if (path[0] != path[n - 1]) return false;

    for (int i = 0; i < n - 1; i++) {
        if (!G.isEdge(path[i], path[i + 1])) return false;
        for (int j = i + 1; j < n - 1; j++) {
            if (path[i] == path[j]) return false;
        }
    }
    return true;
}
void testSimpleCycle() {
    cout << "Simple Cycle Test" << endl;

    Graph G(4);
    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(2, 0);

    vector <int> path1 = { 0,1,2,0 };
    vector <int> path2 = { 0,1,2 };
    vector <int> path3 = { 0,1,0,2,0 };

    cout << "Cycle 1: " << (isSimpleCycle(G, path1) ? "PASS" : "FAIL") << endl;
    cout << "Cycle 2: " << (isSimpleCycle(G, path2) ? "PASS" : "FAIL") << endl;
    cout << "Cycle 3: " << (isSimpleCycle(G, path3) ? "PASS" : "FAIL") << endl;
}