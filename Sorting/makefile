PROG = program
CC = g++
CPPFLAGS = -g -Wall
SUBMFILE = Zekarias_Sorting.zip

OBJS = main.o TimedSorter.o

$(PROG) : $(OBJS)
	@$(CC) -o $(PROG) $(CPPFLAGS) $(OBJS)
	#Program output here ▼
	@echo -------------------------------------------------------
	@echo
	@./$(PROG)
main.o :
	#building the main.cpp
	@$(CC) $(CPPFLAGS) -c main.cpp
TimedSorter.o : TimedSorter.hpp TimedSorter.cpp
	#building the TimedSorter
	@$(CC) $(CPPFLAGS) -c TimedSorter.cpp



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