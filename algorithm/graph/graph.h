#ifndef ALGORITHM_GRAPH_H
#define ALGORITHM_GRAPH_H

#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <set>
#include <list>
#include <stdexcept>
#include <utility>

namespace myalgorithm {
    using std::istream;
    using std::ostream;
    using std::endl;
    using std::map;
    using std::vector;
    using std::set;
    using std::stack;
    using std::list;
    using std::pair;
    using std::range_error;

    // 邻接点
    struct Neighbor {
        int dest;  // 邻接点的索引
        int weight;  // 边的权重

        Neighbor(int dest = 0, int weight = 0) : dest(dest), weight(weight)
        {}

        friend bool operator<(const Neighbor &lhs, const Neighbor &rhs)
        {
            return lhs.dest < rhs.dest;
        }

        friend bool operator==(const Neighbor &lhs, const Neighbor &rhs)
        {
            return lhs.dest == rhs.dest;
        }
    };

    // 顶点信息
    template <typename T>
    struct VertexInfo {
        // 用于图算法，未被访问时，节点颜色为 WHITE，
        // 正在被访问时，颜色为 GREY，访问过的节点颜色为 BLACK
        enum class VertexColor {
            WHITE,
            GRAY,
            BLACK
        };

        typename map<T, int>::iterator vertexMapLoc;  // map 的 first 成员是顶点名，second 成员是 VertexInfo 向量索引
        set<Neighbor> neighbors;  // 当前顶点的邻接点集合
        int inDegree;  // 顶点的入度
        bool occupied;  // 当前对象当前是否表示有效顶点，当顶点被删除后，值为 false
        VertexColor color;  // 用于图算法遍历时标记
        int data;  // 存储数据
        int parent;  // 用于图算法，存储其边在当前顶点终止的顶点的父顶点

        VertexInfo() : inDegree(0), occupied(true)
        {}

        VertexInfo(const typename map<T, int>::iterator &vertexMapLoc) :
                vertexMapLoc(vertexMapLoc), inDegree(0), occupied(true)
        {}
    };

    // 图
    template <typename T>
    class Graph {
    public:
        Graph();
        Graph(const Graph<T> &obj);
        Graph<T> &operator=(const Graph &rhs);

        bool empty() const;

        // 返回边 (v1, v2) 的权重，边不存在，则返回 -1
        int getWeight(const T &vertex1, const T &vertex2) const;
        // 设置边 (v1, v2) 的权重
        void setWeight(const T &vertex1, const T &vertex2, int weight);

        // 返回与顶点 v 相邻的顶点集合
        set<T> getNeighbors(const T &vertex) const;

        // 返回顶点 v 的入度
        int inDegree(const T &vertex) const;
        // 返回顶点 v 的出度
        int outDegree(const T &vertex) const;

        // 返回图中顶点的个数
        int vectexCount() const;
        // 返回图中边数
        int edgeCount() const;

        // 将顶点 v 加入顶点集合中
        void insertVertex(const T &vertex);
        // 将权重为 weight 的边 (v1, v2) 加入边集合中
        void insertEdge(const T &vertex1, const T &vertex2, int weight);

        // 删除顶点 v
        void eraseVertex(const T &vertex);
        // 删除边 (v1, v2)
        void eraseEdge(const T &vertex1, const T &vertex2);
        // 删除图中所有的顶点和边
        void clear();

        template<typename U>
        friend istream& operator>>(istream &in, Graph<U> &graph);

        template<typename U>
        friend ostream& operator<<(ostream &out, const Graph<U> &graph);

        class Iterator;
        class ConstIterator;

        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;

        // 图的广度优先遍历
        template <typename U>
        friend set<U> bfs(Graph<U> &graph, const U &startVertex);

        // 图的深度优先访问
        template <typename U>
        friend void dfsVisit(Graph<U> &graph, const U &startVertex, list<U> &dfsList, bool checkCycle);

        // 图的深度优先遍历
        template <typename U>
        friend void dfs(Graph<U> &graph, list<U> &dfsList);

        // 确定图是否为无环图
        template <typename U>
        friend bool acyclic(Graph<U> &graph);

        // 无环图的拓扑排序
        template <typename U>
        friend void topologicalSort(Graph<U> &graph, list<U> &topologicalList);

        // 返回指定图的转置图
        template <typename U>
        friend Graph<U> transposeGraph(Graph<U> &graph);

        // 搜索图中的强联通分量
        template <typename U>
        friend void strongComponents(Graph<U> &graph, vector<set<U>> &components);

        // 寻找最短路径
        template <typename U>
        friend int shortestPath(Graph<U> &graph, const U &startVertex, const U &endVertex, list<U> &path);

        // Dijkstra 最小路径算法
        template <typename U>
        friend int minimumPath(Graph<U> &graph, const U &startVertex, const U&endVertex, list<U> &path);

        // 最小生成树
        template<typename U>
        friend int minSpanTree(Graph<U> &graph, Graph<U> &MSTree);

    private:
        map<T, int> vertexMap;
        vector<VertexInfo<T>> vertexInfo;
        int numVertices;  // 图的顶点数
        int numEdges;  // 图的边数
        stack<int> availIndexStack;  // 存储 vertexInfo 中未使用索引的栈

        // 使用 vertexMap 获得 vertexInfo 中顶点 v 的索引
        int getVertexIndex(const T &v) const;
    };

    template <typename T>
    int Graph<T>::getVertexIndex(const T &vertex) const
    {
        typename map<T, int>::const_iterator iter = vertexMap.find(vertex);
        if (iter == vertexMap.end()) {
            return -1;
        } else {
            return (*iter).second;
        }
    }

    template <typename T>
    Graph<T>::Graph() : numVertices(0), numEdges(0) {}

    template <typename T>
    Graph<T>::Graph(const Graph<T> &obj)
    {
        *this = obj;
    }

    template <typename T>
    Graph<T> &Graph<T>::operator=(const Graph<T> &rhs)
    {
        if (this != &rhs) {
            vertexMap = rhs.vertexMap;
            vertexInfo = rhs.vertexInfo;
            numVertices = rhs.numVertices;
            numEdges = rhs.numEdges;
            availIndexStack = rhs.availIndexStack;

            for (typename map<T, int>::iterator iter = vertexMap.begin();
                 iter != vertexMap.end(); ++iter) {
                vertexInfo[(*iter).second].vertexMapLoc = iter;
            }
        }

        return *this;
    }

    template <typename T>
    bool Graph<T>::empty() const
    {
        return numVertices == 0;
    }

    // 返回边 (v1, v2) 的权重，若边不存在则返回 -1
    template <typename T>
    int Graph<T>::getWeight(const T &vertex1, const T &vertex2) const
    {
        int vertexIndex1 = getVertexIndex(vertex1);
        int vertexIndex2 = getVertexIndex(vertex2);
        if (vertexIndex1 == -1 || vertexIndex2 == -1) {
            throw range_error("Graph.getWeight(): the vertex is not in the graph");
        }

        const set <Neighbor> &edgeSet = vertexInfo[vertexIndex1].neighbors;
        set<Neighbor>::const_iterator iter = edgeSet.begin();
        if ((iter = edgeSet.find(Neighbor(vertexIndex2))) != edgeSet.end()) {
            return (*iter).weight;
        } else {
            return -1;
        }
    }

    // 设置边 (v1, v2) 的权重
    template <typename T>
    void Graph<T>::setWeight(const T &vertex1, const T &vertex2, int weight)
    {
        int vertexIndex1 = getVertexIndex(vertex1);
        int vertexIndex2 = getVertexIndex(vertex2);
        if (vertexIndex1 == -1 || vertexIndex2 == -1) {
            throw range_error("Graph.setWeight(): the vertex is not in the graph");
        }

        set <Neighbor> &edgeSet = vertexInfo[vertexIndex1].neighbors;
        set<Neighbor>::iterator iter = edgeSet.begin();
        if ((iter = edgeSet.find(Neighbor(vertexIndex2))) != edgeSet.end()) {
            //(*iter).weight = weight;
        } else {
            throw range_error("Graph.setWeight(): the vertex is not in the graph");
        }
    }

    template <typename T>
    set <T> Graph<T>::getNeighbors(const T &vertex) const
    {
        int vertexIndex = getVertexIndex(vertex);
        if (vertexIndex == -1) {
            throw range_error(
                "Graph.getNeighbors(): the vertex is not in the graph");
        }

        const set <Neighbor> &edgeSet = vertexInfo[vertexIndex].neighbors;
        set <T> adjacentVertices;
        for (set<Neighbor>::const_iterator iter = edgeSet.begin();
             iter != edgeSet.end(); ++iter) {
            int adjacentVertexIndex = (*iter).dest;
            adjacentVertices.insert(
                (*(vertexInfo[adjacentVertexIndex].vertexMapLoc)).first);
        }

        return adjacentVertices;
    }

    template <typename T>
    int Graph<T>::inDegree(const T &vertex) const
    {
        int vertexIndex = getVertexIndex(vertex);
        if (vertexIndex == -1) {
            throw range_error("Graph.inDegree(): the vertex is not in the graph");
        }

        return vertexInfo[vertexIndex].inDegree;
    }

    template <typename T>
    int Graph<T>::outDegree(const T &vertex) const
    {
        int vertexIndex = getVertexIndex(vertex);
        if (vertexIndex == -1) {
            throw range_error("Graph.outDegree(): the vertex is not in the graph");
        }

        return vertexInfo[vertexIndex].neighbors.size();
    }

    template <typename T>
    int Graph<T>::vectexCount() const
    {
        return numVertices;
    }

    template <typename T>
    int Graph<T>::edgeCount() const
    {
        return numEdges;
    }

    template <typename T>
    void Graph<T>::insertVertex(const T &vertex)
    {
        pair<typename map<T, int>::iterator, bool> result =
            vertexMap.insert(typename map<T, int>::value_type(vertex, 0));
        if (result.second) {
            int vertexIndex = 0;
            if (!availIndexStack.empty()) {
                vertexIndex = availIndexStack.top();
                availIndexStack.pop();
                vertexInfo[vertexIndex] = VertexInfo<T>(result.first);
            } else {
                vertexInfo.push_back(VertexInfo<T>(result.first));
                vertexIndex = numVertices;
            }

            (*result.first).second = vertexIndex;
            ++numVertices;
        } else {
            throw range_error("Graph.insertVertex(): the vertex already in the graph");
        }
    }

    template <typename T>
    void Graph<T>::insertEdge(const T &vertex1, const T &vertex2, int weight)
    {
        int vertexIndex1 = getVertexIndex(vertex1);
        int vertexIndex2 = getVertexIndex(vertex2);
        if (vertexIndex1 == -1 || vertexIndex2 == -1) {
            throw range_error("Graph.insertEdge(): the vertex is not in the graph");
        }

        // vertex1 和 vertex2 是同一个顶点，会产生自环
        if (vertexIndex1 == vertexIndex2) {
            throw range_error("Graph.insertEdge(): the two vertex are the same vertex");
        }

        pair<set<Neighbor>::iterator, bool> result =
            vertexInfo[vertexIndex1].neighbors
                                    .insert(Neighbor(vertexIndex2, weight));
        // 如果边集合中还不存在要添加的边，则更新
        if (result.second) {
            numEdges++;
            vertexInfo[vertexIndex2].inDegree++;
        }
    }

    template <typename T>
    void Graph<T>::eraseVertex(const T &vertex)
    {
        typename map<T, int>::iterator vertexIter = vertexMap.find(vertex);
        if (vertexIter == vertexMap.end()) {
            throw range_error("Graph.eraseVertex(): the vertex is not in the graph");
        }

        int vertexIndex = (*vertexIter).second;
        vertexMap.erase(vertexIter);
        --numVertices;

        vertexInfo[vertexIndex].occupied = false;
        availIndexStack.push(vertexIndex);

        for (int i = 0; i < vertexInfo.size(); ++i) {
            if (vertexInfo[i].occupied) {
                set <Neighbor> &edgeSet = vertexInfo[i].neighbors;
                for (set<Neighbor>::iterator neighborIter = edgeSet.begin();
                     neighborIter != edgeSet.end();) {
                    if ((*neighborIter).dest == vertexIndex) {
                        edgeSet.erase(neighborIter);
                        --numEdges;
                        break;
                    } else {
                        ++neighborIter;
                    }
                }
            }
        }

        numEdges -= vertexInfo[vertexIndex].neighbors.size();

        set <Neighbor> &edgeSet = vertexInfo[vertexIndex].neighbors;
        for (set<Neighbor>::iterator neighborIter = edgeSet.begin();
             neighborIter != edgeSet.end(); ++neighborIter) {
            vertexInfo[(*neighborIter).dest].inDegree--;
        }
        edgeSet.erase(edgeSet.begin(), edgeSet.end());
    }

    template <typename T>
    void Graph<T>::eraseEdge(const T &vertex1, const T &vertex2)
    {
        int vertexIndex1 = getVertexIndex(vertex1);
        int vertexIndex2 = getVertexIndex(vertex2);
        if (vertexIndex1 == -1 || vertexIndex2 == -1) {
            throw range_error("Graph.eraseEdge(): the vertex is not in the graph");
        }

        set <Neighbor> &edgeSet = vertexInfo[vertexIndex1].neighbors;
        set<Neighbor>::iterator
            neighborIter = edgeSet.find(Neighbor(vertexIndex2));
        if (neighborIter != edgeSet.end()) {
            edgeSet.erase(neighborIter);
            vertexInfo[vertexIndex2].inDegree--;
            numEdges--;
        } else {
            throw range_error("Graph.eraseEdge(): the edge is not in the graph");
        }
    }

    template <typename T>
    void Graph<T>::clear()
    {
        vertexInfo.erase(vertexInfo.begin(), vertexInfo.end());
        vertexMap.erase(vertexMap.begin(), vertexMap.end());
        while (!availIndexStack.empty()) {
            availIndexStack.pop();
        }

        numVertices = 0;
        numEdges = 0;
    }

    template <typename T>
    istream& operator>>(istream &in, Graph<T> &graph)
    {
        if (graph.numVertices > 0) {
            graph.clear();
        }

        int numVertices;
        in >> numVertices;

        T vertex1;
        for (int i = 0; i < numVertices; ++i) {
            in >> vertex1;
            graph.insertVertex(vertex1);
        }

        int numEdges;
        in >> numEdges;

        T vertex2;
        int weight;
        for (int i = 0; i < numEdges; ++i) {
            in >> vertex1;
            in >> vertex2;
            in >> weight;
            graph.insertEdge(vertex1, vertex2, weight);
        }

        return in;
    }

    template <typename T>
    ostream& operator<<(ostream &out, const Graph<T> &graph)
    {
        for (int i = 0; i < graph.vertexInfo.size(); ++i) {
            VertexInfo<T> vertexInfo = graph.vertexInfo[i];
            if (vertexInfo.occupied) {
                out << (*(vertexInfo.vertexMapLoc)).first << ": in-degree "
                    << vertexInfo.inDegree
                    << "  out-degree " << (vertexInfo.neighbors).size() << endl;
                out << "   Edges: ";

                set <Neighbor> &edgeSet = vertexInfo.neighbors;
                for (set<Neighbor>::iterator neighborIter = edgeSet.begin();
                     neighborIter != edgeSet.end(); ++neighborIter) {
                    out << (*(graph.vertexInfo[(*neighborIter).dest]
                        .vertexMapLoc)).first
                        << " (" << (*neighborIter).weight << ")  ";
                }
                out << endl;
            }
        }

        return out;
    }

    template <typename T>
    class Graph<T>::Iterator : public map<T, int>::iterator {
    public:
        Iterator();
        Iterator(typename map<T, int>::iterator iter);

        const T& operator*();
    };

    template <typename T>
    Graph<T>::Iterator::Iterator()
    {}

    template <typename T>
    Graph<T>::Iterator::Iterator(typename map<T, int>::iterator iter)
    {
        *((typename map<T, int>::iterator *)this) = iter;
    }

    template <typename T>
    const T& Graph<T>::Iterator::operator*()
    {
        typename map<T, int>::iterator iter = *this;
        return (*iter).first;
    }

    template <typename T>
    class Graph<T>::ConstIterator : public map<T, int>::const_iterator {
    public:
        ConstIterator();
        ConstIterator(typename map<T, int>::const_iterator iter);

        const T& operator*() const;
    };

    template <typename T>
    Graph<T>::ConstIterator::ConstIterator()
    {}

    template <typename T>
    Graph<T>::ConstIterator::ConstIterator(
        typename map<T, int>::const_iterator iter)
    {
        *((typename map<T, int>::const_iterator *)this) = iter;
    }

    template <typename T>
    const T& Graph<T>::ConstIterator::operator*() const
    {
        typename map<T, int>::const_iterator iter = *this;
        return (*iter).first;
    }

    template <typename T>
    typename Graph<T>::Iterator Graph<T>::begin()
    {
        return Graph<T>::Iterator(vertexMap.begin());
    }

    template <typename T>
    typename Graph<T>::Iterator Graph<T>::end()
    {
        return Graph<T>::Iterator(vertexMap.end());
    }

    template <typename T>
    typename Graph<T>::ConstIterator Graph<T>::begin() const
    {
        return Graph<T>::ConstIterator(vertexMap.begin());
    }

    template <typename T>
    typename Graph<T>::ConstIterator Graph<T>::end() const
    {
        return Graph<T>::ConstIterator(vertexMap.end());
    }
}

#endif  // ALGORITHM_GRAPH_H