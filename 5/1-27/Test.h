#pragma once

#include "Graph.h"
#include "Dijkstra.h"
#include "DijkstraOpt.h"
#include "FW.h"

using namespace std;

class Test {
public:
    void testDijkstra(Graph &graph, bool checkFW, bool checkAns, bool print, bool compare);
    void testDijkstraOpt(Graph &graph, bool checkFW, bool checkAns, bool print, bool compare);
};
