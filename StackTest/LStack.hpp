//Iyobed Zekarias

#ifndef LSTACK_HPP
#define LSTACK_HPP
#include <iostream>

template <typename T>
class LStack
{
    private:
        //define array to hold ints (for now)
        T *parr;

        //The next available spot in the array 
        std::size_t top;

        //the current size of the array
        std::size_t arraySize;

    public:
        //constructor
        LStack();

        //destrutcor
        ~LStack();

        void Push(const T& x);

        T& Pop();

        const T& Top();

        bool IsEmpty();

        void PrettyPrint();

        int Size();

        void Empty();
};


#endif

