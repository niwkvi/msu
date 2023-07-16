#pragma once

#include "Graph.h"

class DijkstraOpt {
public:
    int count;
    int graphSize;
    int startingVertex;

    vector<int> distMin;
    vector<int> path;
    vector<int> isVertexVisited;

    explicit DijkstraOpt(Graph &graph);
    ~DijkstraOpt();

    void solve(Graph &graph);
    void print();
    void clear();
};
