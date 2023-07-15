#pragma once

#include "Graph.h"

class FW {
private:
    vector<vector<int>> path;
    vector<vector<int>> matrix;

    int graphSize;
    int startingVertex;

public:
    vector<int> distMin;

    explicit FW(Graph &graph);
    ~FW();

    void solve();
    void print();
    void clear();
};
