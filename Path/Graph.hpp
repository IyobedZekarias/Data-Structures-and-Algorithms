//Graph created by Iyobed Zekarias

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include "GraphNode.hpp"

template <typename T>
class Graph
{
    private:
        T *possible_nodes;
        size_t possibleNodesSize;
        size_t maxSize;

        GraphNode<T> *nodes[50];
        size_t graphSize;

        std::string name;

        void getPath(const T *prevs, T n, std::string *sofar, T stopper);
        void reverseStr(std::string &str);
    public:
        //ctor
        Graph(std::string n);
        //dtor
        ~Graph();

        void Insert(const T name);

        void Edge(const T n1, const T n2, const int weight);

        void GraphViz();

        void DijkstrasPrintout();

};

#endif