//Iyobed Zekarias

#include "LStack.hpp"
#include <string>

template <typename T>
LStack<T>::LStack()
{
    //Consttructor to build LStack
    arraySize = 3;

    //initialize the array of ints
    parr = new T[arraySize];

    //set the top to zero
    top = 0;

}

template <typename T>
LStack<T>::~LStack()
{
    delete[] parr;
}

template <typename T>
void LStack<T>::Push(const T& x)
{
    //push array in if it has room
    if(top < arraySize)
    {
        parr[top++] = x;
    }
    //If array is to full resize the array 
    else
    {
        //Use temp array to resize array 
        arraySize *= 2;
        T *temp = new T[arraySize];

        for(size_t i =0; i < top; i++)
        {
            temp[i] = parr[i];
        }
        delete[] parr;
        parr = temp;
        parr[top++] = x;
    }   
    
}

template <typename T>
T& LStack<T>::Pop()
{
    //Check if stack is not empty
    if (top > 0)
    {
        return parr[--top];
    }
    //Throw an exception if array is empty 
    else throw std::out_of_range("Called Pop on an empty LStack");
}

template <typename T>
const T& LStack<T>::Top()
{
    //Peek at the top of the stack
    if (top > 0)
    {
        return parr[top - 1];
    }
    //Throw an exception if array is empty 
    else throw std::out_of_range("There is nothing in the LStack");
}

template <typename T>
bool LStack<T>::IsEmpty() 
{
    //Just check if the array is empty
    return !top;
}

template<typename T>
int LStack<T>::Size()
{
    //Returns the size of the array
    int size = top;
    return size;
}

template<typename T>
void LStack<T>::Empty()
{
    top = 0;
}

template <typename T>
void LStack<T>::PrettyPrint()
{
    //Check if there is anything in the stack 
    if(top > 0)
    {
        //Check if there is more than one item if so print all itmes
        //Otherwise print only the first item
        if(top > 1)
        {
            int temp = top;
            std::cout << "[" << parr[--temp] << " <--Top" << std::endl;
            for(int i = (temp-1); i > 0; i--)
            {
                std::cout << parr[i] << std::endl;
            }
            std::cout << parr[0] << "] <--Bottom" << std::endl;
        }
        else
        {
            std::cout << "Top --> ["<< parr[0] << "] <--Bottom" << std::endl;
        }
    }
    //If there is nothing then throw an exception
    else throw std::out_of_range("There is nothing to print int the LStack");
    
}

template class LStack<int>;
template class LStack<float>;
template class LStack<std::string>;
template class LStack<char>;