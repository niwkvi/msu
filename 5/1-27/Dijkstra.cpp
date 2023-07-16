#include "Dijkstra.h"

Dijkstra::Dijkstra(Graph &graph) : path(graph.graphSize), distMin(graph.graphSize), isVertexVisited(graph.graphSize) {
    graphSize = graph.graphSize;
    startingVertex = graph.startingVertex;

    for (int i = 0; i < graphSize; i++) {
        distMin[i] = INF;
        isVertexVisited[i] = false;
        path[i] = -1;
    }

    distMin[startingVertex] = 0;
    count = 0;
}

Dijkstra::~Dijkstra() {
    clear();
}

void Dijkstra::solve(Graph &graph) {
    count = 0;

    for (int i = 0; i < graphSize; i++) {
        int min = INF;
        int minVertex = -1;

        for (int j = 0; j < graphSize; j++) {
            if (!isVertexVisited[j] && distMin[j] < min) {
                min = distMin[j];
                minVertex = j;
            }
        }

        isVertexVisited[minVertex] = true;

        for (int j = 0; j < graphSize; j++) {
            if (!isVertexVisited[j] && graph.adjMatrix[minVertex][j] && graph.adjMatrix[minVertex][j] != INF &&
                distMin[minVertex] + graph.adjMatrix[minVertex][j] < distMin[j]) {
                
                distMin[j] = distMin[minVertex] + graph.adjMatrix[minVertex][j];
                path[j] = minVertex;
                count++;
            }
        }
    }
}

void Dijkstra::print() {
    ofstream f;
    f.open("outDijkstra.txt");

    for (int i = 0; i < graphSize; i++) {
        if (i == startingVertex) continue;
        if (distMin[i] == INF) f << -1 << " ";
        else f << distMin[i] << " ";
    }
    f << endl;

    vector<int> tempPath;

    for (int i = 0; i < graphSize; i++) {
        int v = i;

        if (i == startingVertex) continue;

        while (v != -1) {
            tempPath.push_back(v);
            v = path[v];
        }

        for (int j = int(tempPath.size()) - 1; j >= 0; j--) {
            f << tempPath[j] << " ";
        }

        f << endl;
        tempPath.clear();
    }

    f.close();
}

void Dijkstra::clear() {
    distMin.clear();
    path.clear();
    isVertexVisited.clear();
}
