#pragma once

#include "Graph.h"

class Dijkstra {
public:
    int count;
    int graphSize;
    int startingVertex;

    vector<int> distMin;
    vector<int> path;
    vector<bool> isVertexVisited;

    explicit Dijkstra(Graph &graph);
    ~Dijkstra();

    void solve(Graph &graph);
    void print();
    void clear();
};
