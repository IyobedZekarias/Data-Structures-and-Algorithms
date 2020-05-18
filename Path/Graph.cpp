//Grpah by Iyobed Zekarias

#include <iostream>
#include <string>
#include <sstream>
#include "Graph.hpp"
#include "GraphNode.hpp"

template <typename T>
Graph<T>::Graph(std::string n)
{
    maxSize = 26;
    possible_nodes = new T[maxSize];
    possibleNodesSize = 0;

    graphSize = 0;
    name = n;
}

template <typename T>
Graph<T>::~Graph()
{
    delete possible_nodes;
}

//insert doesn't actually create a graph node just inserts into the end of the arry
template <typename T>
void Graph<T>::Insert(const T name)
{
    //throw an error if trying to insert duplicage node
    for(size_t i = 0; i < possibleNodesSize; i++)
    {
        if(possible_nodes[i] == name) 
        {
            throw "ERROR: node already exists \n not inserting multiple nodes";
            return;
        }
    }
    // resize array if needed
    if(possibleNodesSize < maxSize) possible_nodes[possibleNodesSize++] = name;
    else
    {
        maxSize *= 2;
        T *temp = new T[maxSize];

        for(size_t i = 0; i < possibleNodesSize; i++) temp[i] = possible_nodes[i];
        delete[] possible_nodes;
        possible_nodes = temp;
        possible_nodes[possibleNodesSize++] = name;
    }
    
    
}


template <typename T>
void Graph<T>::Edge(const T n1, const T n2, const int weight)
{
    if(n1 == n2 && weight > 0) throw "ERROR: node to node edge not zero \n not writing edge";
    //Check if n1 and n2 are one of the possible nodes
    bool n1Available = false;
    bool n2Available = false;
    for(size_t i = 0; i < possibleNodesSize; i++)
    {
        if(possible_nodes[i] == n1) n1Available = true;
        if(possible_nodes[i] == n2) n2Available = true;
        if(n2Available && n1Available) break;
    }

    //only if n1 and n2 are possible node
    if(n1Available && n2Available)
    {
        bool n1AlreadyNode = false;
        bool n2AlreadyNode = false;
        GraphNode<T> *node1;
        GraphNode<T> *node2;

        //find out if n1 and n2 are already nodes in the graph or not 
        for(size_t i = 0; i < graphSize; i++)
        {
            if(nodes[i] -> getData() == n1) 
            {
                n1AlreadyNode = true;
                node1 = nodes[i];
            }
            if(nodes[i] -> getData() == n2) 
            {
                n2AlreadyNode = true;
                node2 = nodes[i];
            }
            if(n1AlreadyNode && n2AlreadyNode) break;
        }

        // if the two are not in the graph make them nodes and make an edge from n1->n2
        if(!n1AlreadyNode) 
        {
            node1 = new GraphNode<T>;
            node1 ->setData(n1); 
            nodes[graphSize] = node1;
            graphSize++;
        }
        if(!n2AlreadyNode) 
        {
            node2 = new GraphNode<T>; 
            node2 -> setData(n2);
            nodes[graphSize] = node2;
            graphSize++;
        }
        node1 -> addEdge(node2, weight);
    }
    //throw an error if the edge is not a possible edge
    else
    {
        if(!n1Available) throw "ERROR: input is not a possible vertex \n not writing edge";
        if(!n2Available) throw "ERROR: input is not a possible vertex \n not writing edge";
    }
    
}

//Prints in dot notation
template <typename T>
void Graph<T>::GraphViz()
{
    std::cout << "digraph " << name << " {" << std::endl;
    for(size_t i = 0; i < graphSize; i++)
    {
        nodes[i] -> GraphVizConnections();
    }
    std::cout << "}" << std::endl;
}

//This is what traverses the graph
template <typename T>
void Graph<T>::DijkstrasPrintout()
{
    std::cout << " Graph: " << name << std::endl;
    for(size_t i = 0; i < graphSize; i++)
    {
        std::cout << "," << nodes[i] -> getData() << ",";
    }
    std::cout << std::endl;

    for(size_t i = 0; i < graphSize; i++)
    {
        std::cout << ",PATH,WEIGHT";
    }
    std::cout << std::endl;

    //go through the array and find the distance to every node
    for(size_t i = 0; i < graphSize; i++)
    {
        std::cout << nodes[i] -> getData() << ",";
        int *distances = new int[graphSize];
        GraphNode<T> *Visited[graphSize];
        GraphNode<T> *UnVisited[graphSize];
        T *prevs = new T[graphSize];

        std::fill_n(Visited, graphSize, nullptr);
        std::fill_n(distances, graphSize, (1215752192-215752192));
        distances[i] = 0;
        Visited[i] = nodes[i];
        for(size_t j = 0; j < graphSize; j++) if(j != i) UnVisited[j] = nodes[j];

        //distances index correspondes with the index of each node
        //prevs index corresspondes with teh index of each node
        //pass it arrays and values that are editable

        nodes[i] -> Dijkstras(Visited, UnVisited, nodes, distances, 0, graphSize, prevs);

        //go through the nodes and display the distances
        for(size_t j = 0; j < graphSize; j++)
        {
            // std::cout << prevs[j] << std::endl;
            std::string anchor;
            std::stringstream ss; 
            ss << nodes[j]->getData();
            ss >> anchor;
            std::string *path = &anchor;
            getPath(prevs, nodes[j]->getData(), path, nodes[i]->getData());
            if(path -> find("path") == std::string::npos)
            {
                reverseStr(*path);
            } 
            std::cout << *path << ",";

            if(distances[j] == 1000000000) std::cout << "-" << ",";
            else std::cout << distances[j] << ",";
        }
        std::cout << std::endl;
        delete distances;
        delete prevs;
    }
    
}

//raverses prevs[] and links the paths together to make one long path
template <typename T>
void Graph<T>::getPath(const T *prevs, T n, std::string *sofar, T stopper)
{
    size_t index;
    for(size_t i = 0; i < graphSize; i++)
    {
        if(nodes[i]->getData() == n)
        {
            index = i;
            break;
        }
    }
    
    bool segFault = true;
    for(size_t i = 0; i < graphSize; i++)
    {
        if(prevs[index] == nodes[i]->getData()) segFault = false;
    }
    if(prevs[index] != stopper && !segFault)
    {
        std::string s;
        std::stringstream ss; 
        ss << prevs[index]; 
        ss >> s;
        sofar -> append(s);
        getPath(prevs, prevs[index], sofar, stopper);
    }
    if(segFault)
    {
        sofar->append("\bno path");
    }

    // for(size_t i = 0; i < graphSize; i++)
    // {
    //     if(nodes[i]->getData() == prevs[index])
    //     {
    //         index = i;
    //         i++;
    //         break;
    //     }
    // }

    // for(size_t i = 0; i < graphSize; i++)
    // {
    //     if(prevs[i] != stopper)
    //     {
    //         std::string s;
    //         std::stringstream ss;
    //         ss << prevs[i];
    //         ss >> s;
    //         sofar -> append(s);
    //     }
    // }
}

//make a string reverse
template <typename T>
void Graph<T>::reverseStr(std::string &str) 
{ 
    int n = str.length(); 
  
    // Swap character starting from two 
    // corners 
    for (int i = 0; i < n / 2; i++) 
        std::swap(str[i], str[n - i - 1]); 
} 
 

template class Graph<char>;
template class Graph<std::string>;