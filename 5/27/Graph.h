#pragma once

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>
#include <string>
#include <ctime>
#include <chrono>

#define INF ((1LL<<31)-1)

using namespace std;

class Graph {
public:
    int graphSize;
    int startingVertex;
    double graphDensity;

    unsigned int edges;

    vector<vector<int>> adjMatrix;
    vector<int> answer;
    vector<int> path;

    mt19937 mt;

    explicit Graph(int size);
    ~Graph();

    void generate(int size, double density);
    void generateAnswer(int size, double density, bool print);
    void inputFromFile();
    void printToFile();
    void clear();
};
