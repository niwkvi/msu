#include "DijkstraOpt.h"

DijkstraOpt::DijkstraOpt(Graph &graph) : path(graph.graphSize), distMin(graph.graphSize), isVertexVisited(graph.graphSize) {
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

DijkstraOpt::~DijkstraOpt() {
    clear();
}

void DijkstraOpt::solve(Graph &graph) {
    count = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> PQ;

    PQ.push({0, startingVertex});

    while (!PQ.empty()) {
        int u = PQ.top().second;
        PQ.pop();

        if (isVertexVisited[u]) continue;

        isVertexVisited[u] = true;

        for (int i = 0; i < graphSize; i++) {
            if (graph.adjMatrix[u][i] != INF && distMin[u] + graph.adjMatrix[u][i] < distMin[i]) {
                distMin[i] = distMin[u] + graph.adjMatrix[u][i];
                PQ.push({distMin[i], i});
                path[i] = u;
                count++;
            }
        }
    }
}

void DijkstraOpt::print() {
    ofstream f;
    f.open("outDijkstraOpt.txt");

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

void DijkstraOpt::clear() {
    distMin.clear();
    path.clear();
    isVertexVisited.clear();
}
