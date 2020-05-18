//Written by Iyobed Zekarias

#include "Graph.hpp"
#include "Logger.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>

int main()
{
    // Graph<char> myGraph("1");

    // myGraph.Insert('A');
    // myGraph.Insert('B');
    // myGraph.Insert('C');
    // myGraph.Insert('D');
    // myGraph.Insert('E');
    // myGraph.Insert('F');
    // myGraph.Insert('G');
    // myGraph.Insert('H');
    // myGraph.Insert('I');

    // myGraph.Edge('A', 'B', 1);
    // myGraph.Edge('A', 'C', 2);
    // myGraph.Edge('A', 'D', 5);
    // myGraph.Edge('B', 'G', 10);
    // myGraph.Edge('B', 'H', 2);
    // myGraph.Edge('C', 'F', 1);
    // myGraph.Edge('D', 'E', 1);
    // myGraph.Edge('E', 'B', 5);
    // myGraph.Edge('E', 'G', 15);
    // myGraph.Edge('E', 'I', 2);
    // myGraph.Edge('F', 'H', 3);
    // myGraph.Edge('G', 'A', 1);
    // myGraph.Edge('H', 'C', 3);
    // myGraph.Edge('H', 'G', 1); 

    // myGraph.GraphViz();
    // std::cout << std::endl <<"Dijkstra's Printout: ";

    // myGraph.DijkstrasPrintout();

    std::string line;
    std::string title = "";
    std::ifstream myfile ("test.txt");
    int linenumber = 0;
    if (myfile.is_open())
    {
        //unitl I find the GRAPH: name= line I can't move forward
        bool graphCreated = false;
        while ( getline (myfile,title) )
        {
            linenumber++;
            if(title.rfind("GRAPH", 0) == 0)
            {
                title = title.substr((title.rfind("=") + 1), (title.length() - title.rfind("=")));
                graphCreated = true;
                break;                
            }
        }

        //Only start reading the lines if the graph has been created
        //If no name frot eh graph is give the program cannot run
        if(graphCreated)
        {
            char cstr[title.size() +1];
            std::copy(title.begin(), title.end(), cstr);
            cstr[title.size()] = '\0';

            //passing in the name this way because other wise it causees weird
            // issues when printing out lines from a txt file
            
            std::string s;
            std::stringstream ss; 
            for(size_t i = 0; i < title.size() + 1; i++)
            {
                ss << cstr[i];
            }
            ss >> s;
            
            Graph<char> Graph(s);

            while(getline (myfile, line))
            {
                linenumber++;

                if(line.rfind("VERTEX", 0) == 0)
                {
                    line = line.substr((line.rfind("=") + 1), (line.length() - line.rfind("=")));
                    
                    char cstr[line.size() +1];
                    std::copy(line.begin(), line.end(), cstr);
                    cstr[line.size()] = '\0';

                    //VERTEXs are created and inserted into the graph to be used with edges
                    try
                    {
                        Graph.Insert(cstr[0]);
                    }
                    catch(const char* c)
                    {
                        std::cout << "on line " << linenumber << ": " << c << ": " << cstr[0] << std::endl;
                    }
                }
                if(line.rfind("EDGE:", 0) == 0)
                {
                    line = line.substr((line.rfind("(") + 1), (line.length() - line.rfind("(")));
                    char cstr[line.size() +1];
                    std::copy(line.begin(), line.end(), cstr);
                    cstr[line.size()] = '\0';
                    
                    //Edges are inserted and put into the graph
                    int i = cstr[6] - '0';
                    try
                    {
                        Graph.Edge(cstr[0], cstr[3], i);
                    }
                    catch(const char* c)
                    {
                        std::cout << "on line " << linenumber << ": "<< c << std::endl;
                    }
                    
                }
            }

            std::cout << "\n";
            Graph.GraphViz();
            std::cout << std::endl <<"Dijkstra's Printout: ";
            Graph.DijkstrasPrintout();
        }
        myfile.close();
    }

    else std::cout << "Unable to open file"; 

}