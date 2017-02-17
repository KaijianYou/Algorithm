#ifndef ALGORITHM_GRAPH_UTIL_TEST_H
#define ALGORITHM_GRAPH_UTIL_TEST_H

#include <iostream>

#include "../../algorithm/graph/graph_util.h"
#include "../../util/utils.h"

namespace myalgorithm {
    using std::cout;
    using std::endl;

    void testGraphUtil()
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

        set<char> bfsPath = bfs(graph, 'A');
        cout << "bfs path: ";
        printContainer(bfsPath.begin(), bfsPath.end());
        cout << endl;

        list<char> dfsPath;
        dfs(graph, dfsPath);
        cout << "dfs path: ";
        printContainer(dfsPath.begin(), dfsPath.end());
        cout << endl;
    }
}

#endif  // ALGORITHM_GRAPH_UTIL_TEST_H
