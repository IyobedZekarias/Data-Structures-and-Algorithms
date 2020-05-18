PROG = program
CC = g++
CPPFLAGS = -g -Wall
SUBMFILE = Zekarias_ShortestPath.zip

OBJS = main.o Logger.o Graph.o GraphNode.o

$(PROG) : $(OBJS)
	@$(CC) -o $(PROG) $(CPPFLAGS) $(OBJS)
	#Program output here ▼
	@echo -------------------------------------------------------
	@echo
	@./$(PROG)
main.o :
	#building the main.cpp
	@$(CC) $(CPPFLAGS) -c main.cpp
Logger.o : Logger.hpp Logger.cpp
	#building the logger
	@$(CC) $(CPPFLAGS) -c Logger.cpp
BSTree.o : Graph.hpp Graph.cpp
	#building the Graph
	@$(CC) $(CPPFLAGS) -c Graph.cpp
BSTreeNode.o : GraphNode.hpp GraphNode.cpp
	#building the GraphNode
	@$(CC) $(CPPFLAGS) -c GraphNode.cpp



clean: 
	#cleaning the folder of core dumps, zip files, and program files
	@rm -f core $(SUBMFILE) $(PROG) $(OBJS)
	#removing the debug file for vs
	@rm -rf Debug
	#The new contents of
	@ls

zip: clean
	#making a zip file
	@zip -r $(SUBMFILE) .