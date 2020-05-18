//Iyobed Zekarias
//2/3/2020

#include <iostream>
#include "Logger.hpp"
#include "LStack.hpp"

int main()
{

    LStack<int> myStack;

    myStack.Push(10);
    myStack.Push(20);
    myStack.Push(30);
    myStack.Push(5);
    myStack.Push(4);

    if(!myStack.IsEmpty())
    {
        myStack.PrettyPrint();
    }

}