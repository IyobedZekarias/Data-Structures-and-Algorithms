//Iyobed Zekarias
//Sorting main

#include <iostream>
#include <random> 
#include <algorithm>

#include "TimedSorter.hpp"

int main()
{
    //Instantiate a timed sorter with ints 
    //and set the timeout to 1000
    TimedSorter<int> mySorter(600000);

    //declare an array of ints
    int *size = new int[17];

    for(int i = 7; i < 24; i++)
    {
        size[i-7] = pow(2,i);
    }

    size_t arraySize = (size_t) pow(2 , 23);
    int *myArray = new int[arraySize];

    //Use random number generator 
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uniform_rand(0, 10000);
    long long measurement;

    
    // //code to check individual sorts 2097152
    // size_t ars = 2097152;
    // int *array = new int[ars];

    // for(size_t i = 0; i < ars; i++)
    // {
    //     array[i] = i;
    // }

    // std::cout << "[";
    // for(size_t i = 0; i < ars; i++)
    // {
    //     std::cout << array[i] << ", ";
    // }
    // std::cout << "\b]" << std::endl;

    // measurement = mySorter.MergeSort(array, 0, ars-1);

    // std::cout << "[";
    // for(size_t i = 0; i < ars; i++)
    // {
    //     std::cout << array[i] << ", ";
    // }
    // std::cout << "\b\b]" << std::endl << "Comparisons: " << measurement << std::endl;
    
    for(int cases = 1; cases <= 2; cases++){
        //fill our array with random numbers 
        for (size_t i=0; i<arraySize; i++)
        {
            if(cases == 1) myArray[i] = uniform_rand(rng);
            if(cases == 2) myArray[i] = i;
        }
            if(cases == 1) std::cout << "Unsorted Array Sort" <<std::endl;
            else std::cout << "Sorted Array Sort" << std::endl;
        for(int i = 1; i <= 16; i++)
        {
            std::cout << "," << size[i];
        }
        std::cout << std::endl;

        std::string algos[] = {"Bubble", "Bin", "Selection", "Insertion", "Heap", "Quick", "Merge"};

        for(int test = 0; test <= 6; test++)
        {

            std::cout << algos[test] << ",";
            //Run all the sorts
            for(int i = 1; i <= 16; i++)
            {
                int *copyArray = new int[size[i]];
                std::copy_n(myArray, size[i], copyArray);

                std::string sort;

                    if(test == 0) measurement = mySorter.BubbleSort(copyArray, size[i]);
                else if(test == 1) measurement = mySorter.BinSort(copyArray, size[i]);
                else if(test == 2) measurement = mySorter.SelectionSort(copyArray, size[i]);
                else if(test == 3) measurement = mySorter.InsertionSort(copyArray, size[i]);
                else if(test == 4) measurement = mySorter.HeapSort(copyArray, size[i]);
                else if(test == 5) measurement = mySorter.QuickSort(copyArray, 0, size[i]-1);
                else if(test == 6) measurement = mySorter.MergeSort(copyArray, 0, size[i]-1);

                //printing out
                if(measurement < 0)
                {
                    for(int j = i; j <=12; j++)
                    {
                        std::cout << ",";
                    }
                    break;
                }
                else
                {
                    std::cout << measurement << ",";
                }
                std::cout << std::flush;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}