#ifndef ALGORITHM_GRAPH_UTIL_H
#define ALGORITHM_GRAPH_UTIL_H

#include <set>
#include <list>
#include <vector>
#include <queue>
#include <functional>
#include <stdexcept>

#include "graph.h"

namespace myalgorithm {
    using std::set;
    using std::list;
    using std::vector;
    using std::queue;
    using std::priority_queue;

    // 图的广度优先遍历
    // 从顶点 startVertex 开始执行广度优先遍历，并返回可达顶点的集合
    template <typename T>
    set<T> bfs(Graph<T> &graph, const T &startVertex)
    {
        int currVertexIndex = graph.getVertexIndex(startVertex);
        if (currVertexIndex == -1) {
            throw range_error("bfs(): the vertex is not in the graph");
        }

        // 初始化图中所有顶点，将它们设置为未访问状态（颜色设为白色）
        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            if (graph.vertexInfo[i].occupied) {
                graph.vertexInfo[i].color = VertexInfo<T>::VertexColor::WHITE;
            }
        }

        queue<int> toBeVisitedQueue;  // 存储图中待访问的顶点
        toBeVisitedQueue.push(currVertexIndex);

        set<T> visitedSet;  // 存储访问过的顶点
        // 访问队列中各个顶点
        while (!toBeVisitedQueue.empty()) {
            currVertexIndex = toBeVisitedQueue.front();
            toBeVisitedQueue.pop();

            // 将访问过的顶点颜色设为黑色
            graph.vertexInfo[currVertexIndex].color = VertexInfo<T>::VertexColor::BLACK;

            visitedSet.insert((*(graph.vertexInfo[currVertexIndex].vertexMapLoc)).first);

            set<Neighbor> &neighbors = graph.vertexInfo[currVertexIndex].neighbors;
            for (set<Neighbor>::iterator neighborIter = neighbors.begin();
                 neighborIter != neighbors.end(); ++neighborIter) {
                int neighborVertexIndex = (*neighborIter).dest;
                if (graph.vertexInfo[neighborVertexIndex].color ==
                    VertexInfo<T>::VertexColor::WHITE) {
                    // 待访问的顶点颜色设为灰色
                    graph.vertexInfo[neighborVertexIndex].color =
                            VertexInfo<T>::VertexColor::GRAY;

                    toBeVisitedQueue.push(neighborVertexIndex);
                }
            }
        }

        return visitedSet;
    }

    // 图的深度优先访问
    // 只访问从起点可达的顶点
    // 从顶点 startVertex（颜色为白色）开始深度优先访问，dfsList 存储被访问过的顶点，
    // 其中顶点顺序与顶点被访问的顺序相反，checkForCycle 用于判断图中是否存在环
    template <typename T>
    void dfsVisit(Graph<T> &graph, const T &startVertex, list<T> &dfsList, bool checkCycle)
    {
        int vertexIndex = graph.getVertexIndex(startVertex);
        if (vertexIndex == -1) {
            throw range_error("dfs(): the vertex is not in the graph");
        }

        // 发现顶点时，将顶点颜色设为 GRAY
        graph.vertexInfo[vertexIndex].color = VertexInfo<T>::VertexColor::GRAY;

        // 顺序查找邻接点集合中没有发现过的顶点（颜色为白色）
        // 对每个顶点递归调用 dfs。如果找到的顶点颜色为灰色，则表明在前一次调用函数时
        // 已经发现过此顶点，而且在图中以此顶点为起点和终点，存在一个环
        set<Neighbor> &neighbors = graph.vertexInfo[vertexIndex].neighbors;
        for (set<Neighbor>::iterator neighborIter = neighbors.begin();
             neighborIter != neighbors.end(); ++neighborIter) {
            int neighborIndex = (*neighborIter).dest;
            if (graph.vertexInfo[neighborIndex].color ==
                VertexInfo<T>::VertexColor::WHITE) {
                dfsVisit(graph, (*(graph.vertexInfo[neighborIndex].vertexMapLoc)).first,
                         dfsList, checkCycle);
            } else if (graph.vertexInfo[neighborIndex].color ==
                       VertexInfo<T>::VertexColor::GRAY && checkCycle) {
                throw range_error("dfs(): graph has a cycle");
            }
        }

        // 访问顶点 startVertex，将其颜色设置为黑色，并把它添加到 dfsList 的前面
        graph.vertexInfo[vertexIndex].color = VertexInfo<T>::VertexColor::BLACK;
        dfsList.push_front((*(graph.vertexInfo[vertexIndex].vertexMapLoc)).first);
    }

    // 图的深度优先遍历
    template <typename T>
    void dfs(Graph<T> &graph, list<T> &dfsList)
    {
        dfsList.clear();

        // 初始化，将所有顶点颜色设置为白色
        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            if (graph.vertexInfo[i].occupied) {
                graph.vertexInfo[i].color = VertexInfo<T>::VertexColor::WHITE;
            }
        }

        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            if (graph.vertexInfo[i].occupied &&
                graph.vertexInfo[i].color == VertexInfo<T>::VertexColor::WHITE) {
                dfsVisit(graph, (*(graph.vertexInfo[i].vertexMapLoc)).first, dfsList, false);
            }
        }
    }

    // 确定图是否为无环图
    template <typename T>
    bool acyclic(Graph<T> &graph)
    {
        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            if (graph.vertexInfo[i].occupied) {
                graph.vertexInfo[i].color = VertexInfo<T>::VertexColor::WHITE;
            }
        }

        try {
            list<T> dfsList;
            for (int i = 0; i < graph.vertexInfo.size(); ++i) {
                if (graph.vertexInfo[i].occupied &&
                    graph.vertexInfo[i].color == VertexInfo<T>::VertexColor::WHITE) {
                    dfsVisit(graph, (*(graph.vertexInfo[i].vertexMapLoc)).first, dfsList, true);
                }
            }
        } catch (const range_error &e) {
            return false;
        }

        return true;
    }

    // 无环图的拓扑排序
    template <typename T>
    void topologicalSort(Graph<T> &graph, list<T> &topologicalList)
    {
        topologicalList.clear();

        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            if (graph.vertexInfo[i].occupied) {
                graph.vertexInfo[i].color = VertexInfo<T>::VertexColor::WHITE;
            }
        }

        try {
            for (int i = 0; i < graph.vertexInfo.size(); ++i) {
                if (graph.vertexInfo[i].occupied &&
                    graph.vertexInfo[i].color == VertexInfo<T>::VertexColor::WHITE) {
                    dfsVisit(graph, (*(graph.vertexInfo[i].vertexMapLoc)).first, topologicalList, true);
                }
            }
        } catch (const range_error &e) {
            throw range_error("topologicalSort(): graph has a cycle");
        }
    }

    // 返回指定图的转置图
    template <typename T>
    Graph<T> transposeGraph(Graph<T> &graph)
    {
        Graph<T> graphT = graph;
        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            graphT.vertexInfo[i].neighbors.erase(graphT.vertexInfo[i].neighbors.begin(),
                                                 graphT.vertexInfo[i].neighbors.end());
            graphT.vertexInfo[i].inDegree = 0;
        }

        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            if (graph.vertexInfo[i].occupied) {
                set<Neighbor> &neighbors = graph.vertexInfo[i].neighbors;
                for (auto neighborIter = neighbors.begin(); neighborIter != neighbors.end(); ++neighborIter) {
                    graphT.vertexInfo[(*neighborIter).dest]
                            .neighbors.insert(Neighbor(i, (*neighborIter).weight));
                    graphT.vertexInfo[i].inDegree++;
                }
            }
        }

        return graphT;
    }

    // 搜索图中的强联通分量
    template <typename T>
    void strongComponents(Graph<T> &graph, vector <set<T>> &components)
    {
        components.resize(0);

        // 对图深度进行深度优先遍历
        list<T> gDfsList;
        dfs(graph, gDfsList);

        Graph<T> graphT = transposeGraph(graph);

        // 将转置图中所有顶点初始化为未访问状态（颜色设为白色）
        for (int i = 0; i < graphT.vertexInfo.size(); ++i) {
            if (graphT.vertexInfo[i].occupied) {
                graphT.vertexInfo[i].color = VertexInfo<T>::VertexColor::WHITE;
            }
        }

        list<T> gTDfsList;
        set<T> component;  // 存储强连通分量
        for (auto graphIter = gDfsList.begin(); graphIter != gDfsList.end(); ++graphIter) {
            // 顶点未被访问过，对该顶点调用 dfsVisit()
            if (graphT.vertexInfo[graphT.getVertexIndex(*graphIter)].color ==
                VertexInfo<T>::VertexColor::WHITE) {
                gTDfsList.clear();
                component.clear();

                dfsVisit(graphT, *graphIter, gTDfsList, false);

                for (auto graphTIter = gTDfsList.begin(); graphTIter != gTDfsList.end(); ++graphTIter) {
                    component.insert(*graphTIter);
                }

                components.push_back(component);
            }
        }
    }

    // 寻找最短路径
    // 返回最短路径值，path 存储顶点的路径表
    template <typename T>
    int shortestPath(Graph<T> &graph, const T &startVertex, const T &endVertex, list<T> &path)
    {
        int startVertexIndex = graph.getVertexIndex(startVertex);
        int endVertexIndex = graph.getVertexIndex(endVertex);
        if (startVertexIndex == -1 || endVertexIndex == -1) {
            throw range_error("shortestPath(): the vertex is not in the graph");
        }

        // 将图中所有顶点初始化为未访问状态（颜色设为白色）
        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            if (graph.vertexInfo[i].occupied) {
                graph.vertexInfo[i].color = VertexInfo<T>::VertexColor::WHITE;
            }
        }

        graph.vertexInfo[startVertexIndex].parent = startVertex;
        graph.vertexInfo[startVertexIndex].data = 0;

        queue<int> toBeVisitedQueue;
        toBeVisitedQueue.push(startVertexIndex);

        bool foundShortestPath = false;
        while (!toBeVisitedQueue.empty() && !foundShortestPath) {
            int currVertexIndex = toBeVisitedQueue.front();
            toBeVisitedQueue.pop();

            graph.vertexInfo[currVertexIndex].color =
                VertexInfo<T>::VertexColor::BLACK;

            if (currVertexIndex == endVertexIndex) {
                foundShortestPath = true;
            } else {
                set <Neighbor>
                    &neighbors = graph.vertexInfo[currVertexIndex].neighbors;
                for (set<Neighbor>::iterator neighborIter = neighbors.begin();
                     neighborIter != neighbors.end(); ++neighborIter) {
                    int neighborVertexIndex = (*neighborIter).dest;
                    // 如果当前顶点的邻接点还未访问过，则访问该邻接点
                    if (graph.vertexInfo[neighborVertexIndex].color ==
                        VertexInfo<T>::VertexColor::WHITE) {
                        // 每个顶点的 data 存储从起点顶点到自己所经过的路径长度，每经过一个顶点，路径长度加一
                        graph.vertexInfo[neighborVertexIndex].data =
                            graph.vertexInfo[currVertexIndex].data + 1;
                        graph.vertexInfo[neighborVertexIndex].parent =
                            currVertexIndex;
                        graph.vertexInfo[neighborVertexIndex].color =
                            VertexInfo<T>::VertexColor::GRAY;

                        toBeVisitedQueue.push(neighborVertexIndex);
                    }
                }
            }
        }

        path.clear();
        // 如果找到最短路径，则从终点顶点开始，沿着每个顶点的父顶点，一直回溯到起点顶点，
        // 在这个过程中，把每个顶点按顺序加入 path 表中
        if (foundShortestPath) {
            int currVertexIndex = endVertexIndex;
            while (currVertexIndex != startVertexIndex) {
                path.push_front((*(graph.vertexInfo[currVertexIndex].vertexMapLoc)).first);
                currVertexIndex = graph.vertexInfo[currVertexIndex].parent;
            }

            path.push_front(startVertex);
            // 终点顶点的 data 值就是最短路径的长度
            return graph.vertexInfo[endVertexIndex].data;
        } else {
            return -1;
        }
    }

    struct MinPathInfo {
        int endVertexIndex;
        int pathWeight;

        friend bool operator<(const MinPathInfo &lhs, const MinPathInfo &rhs)
        {
            return lhs.pathWeight < rhs.pathWeight;
        }

        friend bool operator>(const MinPathInfo &lhs, const MinPathInfo &rhs)
        {
            return lhs.pathWeight > rhs.pathWeight;
        }
    };

    // Dijkstra 最小路径算法
    template <typename T>
    int minimumPath(Graph<T> &graph, const T &startVertex, const T &endVertex, list<T> &path)
    {
        int startVertexIndex = graph.getVertexIndex(startVertex);
        int endVertexIndex = graph.getVertexIndex(endVertex);
        if (startVertex == -1 || endVertex == -1) {
            throw range_error("minimumPath(): the vertex is not in the graph");
        }

        // 初始化所有顶点，将其颜色设置为白色，data 设置为 int 类型最大值
        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            if (graph.vertexInfo[i].occupied) {
                graph.vertexInfo[i].color = VertexInfo<T>::VertexColor::WHITE;
                graph.vertexInfo[i].data = INT_MAX;
            }
        }

        graph.vertexInfo[startVertexIndex].data = 0;
        graph.vertexInfo[startVertexIndex].parent = startVertexIndex;

        MinPathInfo pathInfo;
        pathInfo.endVertexIndex = startVertexIndex;
        pathInfo.pathWeight = 0;  // 起点顶点到起点顶点的路径权重为 0

        priority_queue <MinPathInfo, vector<MinPathInfo>, 
                        std::less<vector<MinPathInfo>::value_type>> minPathPQ;
        minPathPQ.push(pathInfo);

        bool foundMinPath = false;
        while (!minPathPQ.empty()) {
            pathInfo = minPathPQ.top();
            minPathPQ.pop();

            int currVertexIndex = pathInfo.endVertexIndex;
            if (currVertexIndex == endVertexIndex) {
                foundMinPath = true;
                break;
            }

            if (graph.vertexInfo[currVertexIndex].color !=
                VertexInfo<T>::VertexColor::BLACK) {
                graph.vertexInfo[currVertexIndex].color =
                    VertexInfo<T>::VertexColor::BLACK;

                // 查找当前顶点的所有邻接点，如果当前顶点到达邻接点的总权重小于当前顶点的 data，
                // 则创建 MinPathInfo 对象保存该邻接点和总权重，并把它插入优先级队列中
                set <Neighbor>
                    neighbors = graph.vertexInfo[currVertexIndex].neighbors;
                for (set<Neighbor>::iterator neighborIter = neighbors.begin();
                     neighborIter != neighbors.end(); ++neighborIter) {
                    int destVertexIndex = (*neighborIter).dest;
                    if (graph.vertexInfo[destVertexIndex].color ==
                        VertexInfo<T>::VertexColor::WHITE) {
                        int newMinWeight =
                            graph.vertexInfo[currVertexIndex].data +
                            (*neighborIter).weight;
                        if (newMinWeight <
                            graph.vertexInfo[destVertexIndex].data) {
                            pathInfo.endVertexIndex = destVertexIndex;
                            pathInfo.pathWeight = newMinWeight;

                            graph.vertexInfo[destVertexIndex].data =
                                newMinWeight;
                            graph.vertexInfo[destVertexIndex].parent =
                                currVertexIndex;

                            minPathPQ.push(pathInfo);
                        }
                    }
                }
            }
        }

        path.clear();
        if (foundMinPath) {
            int currVertexIndex = endVertexIndex;
            while (currVertexIndex != startVertexIndex) {
                path.push_front(
                    (*(graph.vertexInfo[currVertexIndex].vertexMapLoc)).first);
                currVertexIndex = graph.vertexInfo[currVertexIndex].parent;
            }

            path.push_front(startVertex);
            return graph.vertexInfo[endVertexIndex].data;
        } else {
            return -1;
        }
    }

    // 最小生成树
    template<typename T>
    int minSpanTree(Graph<T> &graph, Graph<T> &MSTree)
    {
        if (graph.vertexInfo.size() <= 0) {
            throw std::underflow_error("minSpanTree(): graph is empty");
        }

        int startVertexIndex = -1;
        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            if (graph.vertexInfo[i].occupied) {
                if (startVertexIndex == -1) {
                    startVertexIndex = i;
                }

                graph.vertexInfo[i].color = VertexInfo<T>::VertexColor::WHITE;
                graph.vertexInfo[i].data = INT_MAX;
            }
        }

        MinPathInfo pathInfo;
        pathInfo.endVertexIndex = startVertexIndex;
        pathInfo.pathWeight = 0;

        graph.vertexInfo[startVertexIndex].data = 0;
        graph.vertexInfo[startVertexIndex].parent = startVertexIndex;

        priority_queue <MinPathInfo, vector<MinPathInfo>,
                std::greater<vector<MinPathInfo>::value_type>> minTreePQ;
        minTreePQ.push(pathInfo);

        int minSpanTreeSize = 0;
        int minSpanTreeWeight = 0;
        while (true) {
            pathInfo = minTreePQ.top();
            minTreePQ.pop();

            int currVertexIndex = pathInfo.endVertexIndex;

            if (graph.vertexInfo[currVertexIndex].color == VertexInfo<T>::VertexColor::WHITE) {
                minSpanTreeWeight += pathInfo.pathWeight;
                ++minSpanTreeSize;

                if (minSpanTreeSize == graph.numVertices) {
                    break;
                }

                graph.vertexInfo[currVertexIndex].color = VertexInfo<T>::VertexColor::BLACK;
                set<Neighbor> &neighbors = graph.vertexInfo[currVertexIndex].neighbors;
                for (auto neighborIter = neighbors.begin(); neighborIter != neighbors.end(); ++neighborIter) {
                    int destVertexIndex = (*neighborIter).dest;
                    if (graph.vertexInfo[destVertexIndex].color == VertexInfo<T>::VertexColor::WHITE) {
                        if ((*neighborIter).weight < graph.vertexInfo[destVertexIndex].data) {
                            pathInfo.endVertexIndex = destVertexIndex;
                            pathInfo.pathWeight = (*neighborIter).weight;

                            graph.vertexInfo[destVertexIndex].data = (*neighborIter).weight;
                            graph.vertexInfo[destVertexIndex].parent = currVertexIndex;

                            minTreePQ.push(pathInfo);
                        }
                    }
                }
            }
        }

        // 清空树并向生成树中添加顶点
        MSTree.clear();
        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            if (graph.vertexInfo[i].occupied) {
                MSTree.insertVertex((*(graph.vertexInfo[i].vertexMapLoc)).first);
            }
        }

        // 向生成树中添加边
        for (int i = startVertexIndex + 1; i < graph.vertexInfo.size(); ++i) {
            if (graph.vertexInfo[i].occupied) {
                int parentIndex = graph.vertexInfo[i].parent;
                T vertexA = (*(graph.vertexInfo[parentIndex].vertexMapLoc)).first;
                T vertexB = (*(graph.vertexInfo[i].vertexMapLoc)).first;
                MSTree.insertEdge(vertexA, vertexB, graph.getWeight(vertexA, vertexB));
            }
        }

        return minSpanTreeWeight;
    }
}

#endif  // ALGORITHM_GRAPH_UTIL_H