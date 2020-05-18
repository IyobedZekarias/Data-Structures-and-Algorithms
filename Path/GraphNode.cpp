//GrpahNode by Iyobed Zekarias

#include "GraphNode.hpp"
#include <iostream>

template <typename T>
GraphNode<T>::GraphNode()
{
    outEdges = new int[10];
    numberOfEdges = 0;
}

template <typename T>
GraphNode<T>::~GraphNode()
{
    delete outEdges;
}

//When adding an edge all I need to know is the weight and where it's going
//Keep track of the number of outgoing edges each node has
template <typename T>
void GraphNode<T>::addEdge(GraphNode<T> *node2, int weight)
{
    outEdges[numberOfEdges] = weight;
    outNodes[numberOfEdges] = node2;
    numberOfEdges++;
}

//return the data in the node
template<typename T>
T GraphNode<T>::getData()
{
    return data;
}

//set the data this way not through a constructor because it gives the constructor
//more flexibility I need to make an array of nodes and can't do that if the constrcutor
//has input variables
template<typename T>
void GraphNode<T>::setData(const T val)
{
    data = val;
}

//print out all connections for the node
template <typename T>
void GraphNode<T>::GraphVizConnections()
{
    for(size_t i = 0; i < numberOfEdges; i++)
    {
        std::cout << "\"" << data << "\" -> \"" << outNodes[i]->getData() << "\"" << std::endl;
    }
}

//goes through dijkstras algorithm 
template <typename T>
void GraphNode<T>::Dijkstras(GraphNode<T> **Visited, GraphNode<T> **UnVisited, GraphNode<T> **allNodes, int *distances, int distance, size_t graphSize, T *prevs)
{
    //resets the algorthm to use the right distance
    //sometimes it gets off by one or two
    for(size_t i = 0; i < graphSize; i++)
    {
        if(allNodes[i] == this)
        {
            if(distances[i] < distance)
            {
                distance = distances[i];
                break;
            }
        }
    }

    //do not do the algoritm on vecotrs that do not have any out going edges
    if(numberOfEdges > 0)
    {
        //go through the number of edges and find the smallest UnVisited edge
        for(size_t k = 0; k < numberOfEdges; k++)
        {
            int smallestIndex = -1;
            int smallest = 1000000000;
            for(size_t i = 0; i < numberOfEdges; i++)
            {
                if(smallest > outEdges[i])
                {
                    bool allowed = true;
                    for(size_t j = 0; j < graphSize; j++)
                    {
                        if(Visited[j] == outNodes[i])
                        { 
                            allowed = false; 
                            break;
                        }
                    }
                    if(allowed)
                    {
                        smallestIndex = i;
                        smallest = outEdges[i];
                    }
                }

                for(size_t j = 0; j < graphSize; j++)
                {
                    if(allNodes[j] == outNodes[i])
                    {
                        if(distances[j] > (outEdges[i]+distance))
                        { 
                            distances[j] = (outEdges[i]+distance);
                            prevs[j] = data;
                        }
                        break;
                    }
                }
            }

            if(smallestIndex != -1)
            {
                for(size_t i = 0; i < graphSize; i++)
                {
                    bool breakout = false;
                    if(UnVisited[i] == outNodes[smallestIndex])
                    {
                        for(size_t j = 0; j < graphSize; j++)
                        {
                            if(Visited[j] == nullptr)
                            { 
                                Visited[j] = outNodes[smallestIndex];
                                UnVisited[i] = nullptr;
                                breakout = true;
                                break;
                            }
                        }
                    }
                    if(breakout) break;
                }

                //add the smallest outgoing edge weight to the distance then run the Dijkstra() program recursively on said node
                distance+=outEdges[smallestIndex];
                outNodes[smallestIndex] -> Dijkstras(Visited, UnVisited, allNodes, distances, distance, graphSize, prevs);
            }
        }
    }

}

template class GraphNode<char>;
template class GraphNode<std::string>;