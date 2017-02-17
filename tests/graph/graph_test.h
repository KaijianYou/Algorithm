#ifndef ALGORITHM_GRAPH_TEST_H
#define ALGORITHM_GRAPH_TEST_H

#include <iostream>

#include "../../algorithm/graph/graph.h"
#include "../../util/utils.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testGraph()
    {
        Graph<char> graph;
        graph.insertVertex('A');
        graph.insertVertex('B');
        graph.insertVertex('C');
        graph.insertVertex('D');
        graph.insertVertex('E');
        graph.insertVertex('F');

        graph.insertEdge('A', 'B', 5);
        graph.insertEdge('A', 'D', 15);
        graph.insertEdge('A', 'F', 20);
        graph.insertEdge('B', 'A', 5);
        graph.insertEdge('B', 'C', 2);
        graph.insertEdge('C', 'D', 7);
        graph.insertEdge('C', 'B', 2);
        graph.insertEdge('D', 'F', 3);
        graph.insertEdge('E', 'F', 3);
        graph.insertEdge('F', 'E', 3);

        cout << "Number of vertices: " << graph.vectexCount() << endl;
        cout << "Number of edges: " << graph.edgeCount() << endl;

        set<char> vertexANeighbors = graph.getNeighbors('A');
        cout << "Adjacent vertices of vertex A: ";
        printContainer(vertexANeighbors.begin(), vertexANeighbors.end());

        cout << "vertex A in-degree:" << graph.inDegree('A') << endl;
        cout << "vertex A out-degree:" << graph.outDegree('A') << endl;

        cout << "All vertices in graph: ";
        for (auto iter = graph.begin(); iter != graph.end(); ++iter) {
            cout << *iter << "  ";
        }
        cout << endl << endl;

        graph.clear();
        if (graph.empty()) {
            cout << "graph is empty" << endl;
        }
    }
}

#endif  // ALGORITHM_GRAPH_TEST_H