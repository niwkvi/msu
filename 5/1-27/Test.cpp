#include "Test.h"

using namespace std::chrono;

void Test::testDijkstra(Graph &graph, bool checkFW, bool checkAns, bool print, bool compare) {

    Dijkstra dijkstra(graph);

    cout << "Dijkstra is being tested..." << endl;

    auto t1 = high_resolution_clock::now();
    dijkstra.solve(graph);
    auto t2 = high_resolution_clock::now();

    auto t3 = duration_cast<milliseconds>(t2 - t1).count();
    auto t3NANO = duration_cast<microseconds>(t2 - t1).count();
    cout << "Dijkstra Time: " << t3 << " ms." << endl;

    if (print) {

        dijkstra.print();

        ofstream f1;
        f1.open("C:/Users/Gondolin/CLionProjects/27/table1.csv", ios_base::app);

        auto ratio = t3NANO / dijkstra.count;
        f1 << dijkstra.count << "," << t3NANO << "," << ratio << ","
           << graph.graphSize << "," << graph.graphDensity << ","
           << graph.edges << endl;

        f1.close();

    }

    if (compare) {

        dijkstra.print();

        ofstream f1;
        f1.open("C:/Users/Gondolin/CLionProjects/27/table11.csv", ios_base::app);

        auto ratio = t3NANO / dijkstra.count;
        f1 << dijkstra.count << "," << t3NANO << "," << ratio << ","
           << graph.graphSize << "," << graph.graphDensity << ","
           << graph.edges << endl;

        f1.close();

    }

    if (checkFW) {

        cout << "FW is checking..." << endl;

        FW fw(graph);
        fw.solve();
        fw.print();

        if (dijkstra.distMin == fw.distMin) {
            cout << "Correct!" << endl;
        }
        else {
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!! Error! Incorrect! !!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        }

    }

    if (checkAns) {

        cout << "Answer is being checked..." << endl;

        if (dijkstra.distMin == graph.answer && dijkstra.path == graph.path) {
            cout << "Correct!" << endl;
        }
        else {
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!! Error! Incorrect! !!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        }

    }

    cout << endl;

}

void Test::testDijkstraOpt(Graph &graph, bool checkFW, bool checkAns, bool print, bool compare) {

    DijkstraOpt dijkstraOpt(graph);

    cout << "DijkstraOpt is being tested..." << endl;

    auto t1 = high_resolution_clock::now();
    dijkstraOpt.solve(graph);
    auto t2 = high_resolution_clock::now();

    auto t3 = duration_cast<milliseconds>(t2 - t1).count();
    auto t3NANO = duration_cast<microseconds>(t2 - t1).count();
    cout << "DijkstraOpt Time: " << t3 << " ms." << endl;

    if (print) {

        dijkstraOpt.print();

        ofstream f2;
        f2.open("C:/Users/Gondolin/CLionProjects/27/table2.csv", ios_base::app);

        auto ratio = t3NANO / dijkstraOpt.count;
        f2 << dijkstraOpt.count << "," << t3NANO << "," << ratio << ","
           << graph.graphSize << "," << graph.graphDensity << ","
           << graph.edges << endl;

        f2.close();

    }

    if (compare) {

        dijkstraOpt.print();

        ofstream f2;
        f2.open("C:/Users/Gondolin/CLionProjects/27/table22.csv", ios_base::app);

        auto ratio = t3NANO / dijkstraOpt.count;
        f2 << dijkstraOpt.count << "," << t3NANO << "," << ratio << ","
           << graph.graphSize << "," << graph.graphDensity << ","
           << graph.edges << endl;

        f2.close();

    }

    if (checkFW) {

        cout << "FW is checking..." << endl;

        FW fw(graph);
        fw.solve();
        fw.print();

        if (dijkstraOpt.distMin == fw.distMin) {
            cout << "Correct!" << endl;
        }
        else {
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!! Error! Incorrect! !!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        }

    }

    if (checkAns) {

        cout << "Answer is being checked..." << endl;

        if (dijkstraOpt.distMin == graph.answer && dijkstraOpt.path == graph.path) {
            cout << "Correct!" << endl;
        }
        else {
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!! Error! Incorrect! !!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
        }

    }

}
