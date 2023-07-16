#include "Test.h"

int main() {
    Test test;

    bool test1 = false;
    bool test2 = true;
    bool test3 = false;

    cout << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "Testing" << endl;
    cout << "--------------------------------------------------------------" << endl;

    ofstream f1, f2;
    f1.open("table1.csv");
    f2.open("table2.csv");

    f1 << "steps,time,avgTime,size,density,edges" << endl;
    f2 << "steps,time,avgTime,size,density,edges" << endl;

    f1.close();
    f2.close();

    if (test1) {
        cout << "Test 1" << endl;
        cout << "--------------------------------------------------------------" << endl;

        int test1Num1 = 100;
        int test1Num2 = 100;
        int test1Size1 = 10;
        int test1Size2 = 10'000;
        int test1Size1Increase = 10;
        int test1Size2Increase = 100;
        double test1Density = 0.5;

        cout << "FW" << endl;

        for (int i = 1; i <= test1Num1; i++) {
            cout << "--------------------------------------------------------------" << endl;
            cout << "Test #" << i << endl << endl;
            cout << "Size: " << test1Size1 << endl;
            cout << "Density: " << test1Density << endl;

            Graph graph(test1Size1);
            graph.generate(test1Size1, test1Density);

            cout << "Starting vertex: " << graph.startingVertex << endl << endl;

            test.testDijkstra(graph, true, false, false, false);
            test.testDijkstraOpt(graph, true, false, false, false);

            cout << endl;
            cout << "Test #" << i << " is over" << endl;

            test1Size1 += test1Size1Increase;
        }

        cout << "--------------------------------------------------------------" << endl;
        cout << "Generated Answer" << endl;

        for (int i = 1; i <= test1Num2; i++) {
            cout << "--------------------------------------------------------------" << endl;
            cout << "Test #" << i << endl << endl;
            cout << "Size: " << test1Size2 << endl;
            cout << "Density: " << test1Density << endl;

            Graph graph(test1Size2);
            graph.generateAnswer(test1Size2, test1Density, false);

            cout << "Starting vertex: " << graph.startingVertex << endl << endl;

            test.testDijkstra(graph, false, true, false, false);
            test.testDijkstraOpt(graph, false, true, false, false);

            cout << endl;
            cout << "Test #" << i << " is over" << endl;

            test1Size2 += test1Size2Increase;
        }
        cout << "--------------------------------------------------------------" << endl;
    }

    if (test2) {
        cout << "Test 2" << endl;
        cout << "--------------------------------------------------------------" << endl;

        int test2Num = 5;
        int test2Size = 18'000;
        int test2SizeIncrease = 1000;
        double test2Density = 0.5;
        double test2DensityIncrease = 0;

        cout << "Hyperbola (5 tests)" << endl;

        for (int i = 1; i <= test2Num; i++) {
            cout << "--------------------------------------------------------------" << endl;
            cout << "Test #" << i << endl << endl;
            cout << "Size: " << test2Size << endl;
            cout << "Density: " << test2Density << endl;

            Graph graph(test2Size);
            graph.generate(test2Size, test2Density);

            cout << "Starting vertex: " << graph.startingVertex << endl << endl;

            test.testDijkstra(graph, false, false, true, false);
            test.testDijkstraOpt(graph, false, false, true, false);

            cout << endl;
            cout << "Test #" << i << " is over" << endl;

            test2Size += test2SizeIncrease;
            test2Density += test2DensityIncrease;
        }
        cout << "--------------------------------------------------------------" << endl;
    }

    if (test3) {
        cout << "Test 3" << endl;
        cout << "--------------------------------------------------------------" << endl;

        int test3Num = 100;
        int test3Size = 5'000;
        int test3SizeIncrease = 10;
        double test3Density = 0.5;

        cout << "Comparing" << endl;

        for (int i = 1; i <= test3Num; i++) {
            cout << "--------------------------------------------------------------" << endl;
            cout << "Test #" << i << endl << endl;
            cout << "Size: " << test3Size << endl;
            cout << "Density: " << test3Density << endl;

            Graph graph(test3Size);
            graph.generate(test3Size, test3Density);

            cout << "Starting vertex: " << graph.startingVertex << endl << endl;

            test.testDijkstra(graph, false, false, false, true);
            test.testDijkstraOpt(graph, false, false, false, true);

            cout << endl;
            cout << "Test #" << i << " is over" << endl;

            test3Size += test3SizeIncrease;
        }
    }

    cout << "--------------------------------------------------------------" << endl;
    cout << "Testing is over" << endl;
    cout << "--------------------------------------------------------------" << endl;

    return 0;
}
