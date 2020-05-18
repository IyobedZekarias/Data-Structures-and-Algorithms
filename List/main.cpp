//Iyobed Zekarias
//2/24/2020

#include <iostream>
#include <sstream>
#include "Logger.hpp"
#include "LList.hpp"

int main()
{
    LList<int> intList;

    intList.Insert(35,0);
    intList.Insert(42,1);
    intList.Insert(99,2);

    //Test the = operation
    LList<int> A;
    A = intList;

    //Test the copy constructor
    LList<int> B(A);
    B.Insert(25, 4);
    A.Insert(14, 5);

    Logger log("text.txt");
    log.DisableFileLogging();

    //Pretty print both lists
    log.Log("A: " + A.PrettyPrint());
    log.Log("B: " + B.PrettyPrint());

    //Test the union
    log.Log("Union: " + A.Union(B).PrettyPrint());
    //test the intersection 
    log.Log("Intersection: " + A.Intersection(B).PrettyPrint());
    //Use copy constructor to create new List
    LList<int> C(A);
    //Test the difference 
    C-B;
    log.Log("Difference (A-B): " + C.PrettyPrint());

    //Prepend and Append check
    A.Append(10);
    A.Prepend(5);
    log.Log("A: " + A.PrettyPrint());

    
    //check is empty
    log.Log("A is empty? " + A.IsEmpty());

    //Check size()
    std::stringstream s;
    s << "A is " << A.Size() << " Items long";
    log.Log(s.str());

    //Clear the list
    A.Clear();
    std::stringstream b; 
    b << "A: " << A.PrettyPrint() << " " << A.Size();
    log.Log(b.str());
    

}