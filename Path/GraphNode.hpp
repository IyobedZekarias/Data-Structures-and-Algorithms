//GraphNode by Iyobed Zekarias

#ifndef GRAPHNODE_HPP
#define GRAPHNODE_HPP

#include <iostream>

template <typename T>
class GraphNode
{
    private:
        T data;
        GraphNode<T> *outNodes[20];
        int *outEdges;
        size_t numberOfEdges;

    public:
        //ctor
        GraphNode();
        //dtor
        ~GraphNode();

        void addEdge(GraphNode<T> *node2, int weight);

        T getData();

        void setData(const T val);

        void GraphVizConnections();

        void Dijkstras(GraphNode<T> **Visited, GraphNode<T> **UnVisited, GraphNode<T> **allNodes, int *distances, int distance, size_t graphSize, T *prevs);
};

#endif