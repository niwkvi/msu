#include "Graph.h"

#include <random>

Graph::Graph(int size) : graphSize(size), startingVertex(0), adjMatrix(size, vector<int>(size)),
answer(size), path(size), graphDensity(0), edges(0) {

    mt.seed(time(nullptr));

}

Graph::~Graph() {
    clear();
}

void Graph::generate(int size, double density) {

    graphDensity = density;
    startingVertex = static_cast<int>(mt() % size);
    auto median = static_cast<unsigned int>(std::mt19937::max() * density);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j)
                adjMatrix[i][j] = 0;
            else if (i > j)
                adjMatrix[i][j] = adjMatrix[j][i];
            else if (mt() > median)
                adjMatrix[i][j] = INF;
            else {
                adjMatrix[i][j] = static_cast<int>(mt() % size + 1);
                edges++;
            }
        }
    }

    vector<int> chain(size);
    iota(chain.begin(), chain.end(), 0);
    shuffle(chain.begin(), chain.end(), std::mt19937(std::random_device()()));

    for (int i = 0; i < size - 1; i++) {
        if (adjMatrix[chain[i]][chain[i + 1]] == INF) {
            adjMatrix[chain[i]][chain[i + 1]] = static_cast<int>(mt() % size + 1);
            adjMatrix[chain[i + 1]][chain[i]] = adjMatrix[chain[i]][chain[i + 1]];
        }
    }

}

void Graph::inputFromFile() {

    ifstream f;
    f.open("C:/Users/Gondolin/CLionProjects/27/in.txt");

    f >> graphSize >> startingVertex;

    for (int i = 0; i < graphSize; i++) {
        for (int j = 0; j < graphSize; j++) {
            f >> adjMatrix[i][j];
        }
    }

    f.close();

}

void Graph::printToFile() {

    ofstream f;
    f.open("C:/Users/Gondolin/CLionProjects/27/in.txt");

    f << graphSize << " " << startingVertex + 1 << endl;

    for (int i = 0; i < graphSize; i++) {
        for (int j = 0; j < graphSize; j++) {
            f << adjMatrix[i][j] << " ";
        }
        f << endl;
    }

    f.close();

}

void Graph::clear() {

    for (int i = 0; i < graphSize; i++) {
        adjMatrix[i].clear();
    }

    adjMatrix.clear();

}

void Graph::generateAnswer(int size, double density, bool print) {

    graphDensity = density;
    auto median = static_cast<unsigned int>(std::mt19937::max() * density);

    vector<int> chain(size);
    iota(chain.begin(), chain.end(), 0);
    shuffle(chain.begin(), chain.end(), std::mt19937(std::random_device()()));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j)
                adjMatrix[i][j] = 0;
            else {
                adjMatrix[i][j] = INF;
                adjMatrix[j][i] = INF;
            }
        }
    }

    startingVertex = chain[0];
    path[chain[0]] = -1;

    for (int i = 0; i < size - 1; i++) {
        adjMatrix[chain[i]][chain[i + 1]] = 1;
        adjMatrix[chain[i + 1]][chain[i]] = adjMatrix[chain[i]][chain[i + 1]];
        if (i > 0) {
            answer[chain[i + 1]] = adjMatrix[chain[i]][chain[i + 1]] + answer[chain[i]];
        }
        else {
            answer[chain[i + 1]] = adjMatrix[chain[i]][chain[i + 1]];
        }

        path[chain[i + 1]] = chain[i];

        edges++;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j)
                continue;
            if (i > j)
                adjMatrix[i][j] = adjMatrix[j][i];
            else if (mt() < median && adjMatrix[i][j] == INF) {
                adjMatrix[i][j] = size + 1'000;
                edges++;
            }
        }
    }

    if (print) {

        ofstream f;
        f.open("C:/Users/Gondolin/CLionProjects/27/answer.txt");

        for (int i = 0; i < graphSize; i++) {
            if (i == startingVertex)
                continue;
            f << answer[i] << " ";
        }

        cout << endl;

        vector<int> tempPath;

        for (int i = 0; i < graphSize; i++) {
            int v = i;
            if (i == startingVertex)
                continue;
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

}
