//Timed sorter.hpp

#ifndef TIMED_SORTER_HPP
#define TIMED_SORTER_HPP

#include <iostream>
#include <chrono>

template <typename T>
class TimedSorter
{
    private:

        //chrono timer variables
        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point currentTime;
        std::chrono::steady_clock::duration delta_t;

        //stopwatch functions
        void startTimer();
        void checkpointTimer();
        bool timeExpired();
        long timeInMilliseconds;
        bool firstIteration;

        long timeout;
        long long comparisons;

        void heapify(T *array, int arraySize, int i);
        void merge(T *array, int l, int m, int r);
        int partition(T* array, int left, int right, T pivot);

    public:
        TimedSorter(long timeoutMilliseconds);

        //sort routines
        long long BubbleSort(T *array, size_t arraySize); 

        long long SelectionSort(T *array, size_t arraySize); 

        long long InsertionSort(T *array, size_t arraySize); 

        long long BinSort(T *array, size_t arraySize);
        
        long long HeapSort(T *array, size_t arraySize);

        long long MergeSort(T *array, int l, int r);

        long long QuickSort(T *array, int left, int right);

};

#endif //TIMED_SORTER_HPP