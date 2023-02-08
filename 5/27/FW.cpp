#include "FW.h"

FW::FW(Graph &graph) : path(graph.graphSize, vector<int>(graph.graphSize)),
matrix(graph.graphSize, vector<int>(graph.graphSize)), distMin(graph.graphSize) {

    graphSize = graph.graphSize;
    startingVertex = graph.startingVertex;

    matrix = graph.adjMatrix;

    for (int i = 0; i < graphSize; i++) {
        distMin[i] = INF;
        for (int j = 0; j < graphSize; j++) {
            path[i][j] = j;
        }
    }

    distMin[startingVertex] = 0;

}

FW::~FW() {
    clear();
}

void FW::solve() {

    for (int k = 0; k < graphSize; k++) {
        for (int i = 0; i < graphSize; i++) {
            for (int j = 0; j < graphSize; j++) {
                if (matrix[i][k] + matrix[k][j] < matrix[i][j] && matrix[i][k] + matrix[k][j] > 0) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                    path[i][j] = path[i][k];
                }
            }
        }
    }

}

void FW::print() {

    ofstream f;
    f.open("C:/Users/Gondolin/CLionProjects/27/outFW.txt");

    for (int i = 0; i < graphSize; i++) {
        if (i != startingVertex) {
            f << matrix[startingVertex][i] << " ";
            distMin[i] = matrix[startingVertex][i];
        }
    }
    f << endl;

    for (int i = 0; i < graphSize; i++) {
        int u = startingVertex;
        if (i == startingVertex)
            continue;
        f << startingVertex << " ";
        while (u != i) {
            u = path[u][i];
            f << u << " ";
        }
        f << endl;
    }

    f.close();

}

void FW::clear() {

    for (int i = 0; i < graphSize; i++) {
        path[i].clear();
        matrix[i].clear();
    }

    path.clear();
    matrix.clear();

}
