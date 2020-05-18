//TimedSorter.cpp

#include <iostream>
#include <chrono>

#include <iomanip>
#include <ctime>
#include <cstdlib>

#include "TimedSorter.hpp"

#include <utility>

//constructor
template <typename T>
TimedSorter<T>::TimedSorter(long timeoutMilliseconds)
{
    timeout = timeoutMilliseconds;
    comparisons = 0;
    firstIteration = true;
}

//function to start the timer
template <typename T>
void TimedSorter<T>::startTimer()
{
    // startTime = std::chrono::system_clock::now();
    startTime = std::chrono::steady_clock::now();
}

//gets the current time
template <typename T>
void TimedSorter<T>::checkpointTimer()
{
    // currentTime = std::chrono::system_clock::now();
    currentTime = std::chrono::steady_clock::now();
    delta_t = currentTime - startTime;
}

template <typename T>
bool TimedSorter<T>::timeExpired()
{
    // timeInMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
    // //std::cout << "time in Milliseconds so far: " << timeInMilliseconds << " timeout time needed: " << timeout << std::endl;
    // if(timeInMilliseconds > timeout)
    // {
    //     return true;
    // }
    // return false;

    return std::chrono::duration_cast<std::chrono::milliseconds>(delta_t).count() > timeout;
}




//public sort functions
template <typename T>
long long TimedSorter<T>::BubbleSort(T *array, size_t arraySize)
{
    //record the start time
    startTimer();

    comparisons = 0;
    bool noSwaps = true;
    //execute the sort
    for(size_t i = 0; i < arraySize-1; i++)
    {
        //periodically check to see if we have exhausted the time
        checkpointTimer();

        if(timeExpired())
        {
            return -1;
        }
        for(size_t j = 0; j < arraySize-i-1; j++)
        {
            comparisons++;
            if(array[j] > array[j+1])
            {
                std::swap(array[j], array[j+1]);
                noSwaps = false;
            }

        }
        if(noSwaps) return comparisons;
    }

    return comparisons;
}

template<typename T>
long long TimedSorter<T>::SelectionSort(T *array, size_t arraySize)
{
    //record the start time 
    startTimer();

    comparisons = 0;

    for(size_t i = 0; i < arraySize; i++)
    {
        //periodically check to see if we have exhausted the time
        checkpointTimer();

        if(timeExpired())
        {
            return -1;
        }

        T smallest = array[i];
        size_t index = i;
        for(size_t j = i+1; j < arraySize; j++)
        {
            comparisons++;
            if(array[j] < smallest)
            {
                index = j;
                smallest = array[j];
            }
        }
        std::swap(array[i], array[index]);
    }
    return comparisons;

}

template<typename T>
long long TimedSorter<T>::InsertionSort(T *array, size_t arraySize)
{
    //record the start time
    startTimer();
    comparisons = 0;

    for(size_t i = 1; i < arraySize; i++)
    {
        //periodically check to see if we have exhausted the time
        checkpointTimer();

        if(timeExpired())
        {
            return -1;
        }

        comparisons++;
        if(array[i] < array[i-1]){
            for(size_t j = i; j > 0; j--)
            {
                comparisons++;
                if(array[j] < array[j-1]){
                    std::swap(array[j], array[j-1]);
                }
                else
                {
                    break;
                }
            }
        }
        
    }
    return comparisons;
}

template <typename T>
long long TimedSorter<T>::BinSort(T *array, size_t arraySize)
{
    startTimer();

    comparisons = 0;
    int size;
    if(arraySize > 10001) size = arraySize;
    else size = 10001;
    int *counts = new int[size];
    for(int i = 0; i < size; i++)
    {
        counts[i] = 0;
    }
    bool arrayinorder = true;
    int prev = -1;
    for(size_t i = 0; i < arraySize; i++)
    {
        int temp = array[i];
        counts[temp]++;
        comparisons++;

        if(arrayinorder && temp > prev) prev = temp;
        else arrayinorder = false;
    }

    if(arrayinorder) return comparisons;

    checkpointTimer();
    if(timeExpired()) return -1;

    int index = 0;
    
    for(size_t i = 0; i< 10001; i++)
    {
        if(counts[i] == 0) continue;

        for(size_t c = counts[i]; c>0; c--)
        {
            array[index++] = i;
            comparisons++;
        }
    }
    
    return comparisons;
}


/*
    Resources for Heap Sort
    Geeksforgeeks: https://www.geeksforgeeks.org/heap-sort/
    YouTube: https://www.youtube.com/watch?v=2DmK_H7IdTo
*/
template <typename T>
long long TimedSorter<T>::HeapSort(T *array, size_t arraySize)
{
    startTimer();
    long long comparisons = 0;
    int n = (int) arraySize;

    //Build the heap
    for(int i = (n/2) - 1; i >= 0; i--)
    {
        checkpointTimer();
        if(timeExpired()) return -1;

        heapify(array, n, i);
    }

    //remove elements from heap
    for(int i = n-1; i> 0; i--)
    {
        checkpointTimer();
        if(timeExpired()) return -1;

        comparisons++;
        //move current root to end
        std::swap (array[0], array[i]);

        //call max heapify on reduced heap
        heapify(array, i, 0);
    }

    return comparisons;
}

template <typename T>
void TimedSorter<T>::heapify(T *array, int arraySize, int i)
{
    int largest = i; //largest is the root
    int l = 2 * i + 1; //left
    int r = 2 * i + 2; //right

    // If left child is larger than root 
    comparisons++;
    if (l < arraySize && array[l] > array[largest]) 
        largest = l; 
  
    // If right child is larger than largest so far 
    comparisons++;
    if (r < arraySize && array[r] > array[largest]) 
        largest = r; 

    // If the largest is not the root
    comparisons++;
    if (largest != i)
    {
        std::swap(array[i], array[largest]);

        //recursively heapify
        heapify(array, arraySize, largest);
    }
}

/*
    Resources for Merge Sort
    Geeksforgeeks: https://www.geeksforgeeks.org/merge-sort/
    StackOverflow: https://codereview.stackexchange.com/questions/77707/is-this-an-optimal-implementation-of-merge-sort
*/
template <typename T>
long long TimedSorter<T>::MergeSort(T *array, int l, int r)
{
    startTimer();
    comparisons = 0;
    
    checkpointTimer();
    if(timeExpired()) return -1;
    comparisons++;
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l+(r-l)/2; 

        // Sort first and second halves 
        MergeSort(array, l, m); 
        MergeSort(array, m+1, r); 
  
        merge(array, l, m, r);

        checkpointTimer();
        if(timeExpired()) return -1; 
    } 
    return comparisons;
}

template<typename T>
void TimedSorter<T>::merge(T *array, int l, int m, int r)
{
    int i, j, k;
    int n1 = m-l+1;
    int n2 = r-m;

    //temp arrays
    int *L = new int[n1];
    int *R = new int[n2];

    for(i=0; i < n1; i++)
    {
        checkpointTimer();
        if(timeExpired()) return;
        L[i] = array[l + i];
    }
    for(j=0; j< n2; j++)
    {
        checkpointTimer();
        if(timeExpired()) return;
        R[j] = array[m+1+j];
    }

    //merge the temp arrays in order
    i = 0;
    j = 0; 
    k = l;

    while ( i < n1 && j < n2)
    {
        checkpointTimer();
        if(timeExpired()) return;
        comparisons++;
        if(L[i] <= R[j])
        {
            array[k] = L[i];
            i++;
        }
        else
        {
            array[k] = R[j];
            j++;
        }
        k++;
        
    }

    //Finish the remaining elements of L[]
    while (i < n1)
    {
        checkpointTimer();
        if(timeExpired()) return;
        comparisons++;
        array[k] = L[i];
        i++;
        k++;
    }

    //finish the remaining elements of R[]
    while (j < n2)
    {
        checkpointTimer();
        if(timeExpired()) return;
        comparisons++;
        array[k] = R[j];
        j++;
        k++;
    }
}

/*
    Resources for QuickSort:
    GeeksForGeeks: https://www.geeksforgeeks.org/quick-sort/
    YouTube: https://www.youtube.com/watch?v=SLauY6PpjW4
*/
template<typename T>
long long TimedSorter<T>::QuickSort(T *array, int left, int right)
{
    startTimer();
    if(firstIteration)
    {
        comparisons = 0;
        firstIteration = false;
    }

    if(left >= right)
    {
        return -1;
    }
    //Make the median the pivot of the Sort
    long long size = right - left;
    long long average, current_distance;
    long long pivot, sum;
    pivot = 0;
    sum = 0;
    average = 0; 
    current_distance = 0;

    for(int i = left; i < right; i++)
    {
        sum += array[i];
        checkpointTimer();
        if(timeExpired()) return -1;
    }
    average = sum/size;

    current_distance = sum;
    for(int i = left; i < right; i++)
    {
        checkpointTimer();
        if(timeExpired()) return -1;
        comparisons++;
        if(abs(average - array[i]) < current_distance)
        {
            current_distance = abs(average - array[i]);
            pivot = array[i];
        }
    }

    //use partition to find where the portion of the array is that needs to be ordered
    int index = partition(array, left, right, pivot);

    checkpointTimer();
    if(timeExpired()) return -1;

    //recursively call self to find pivot then sort
    QuickSort(array, left, index-1);

    checkpointTimer();
    if(timeExpired()) return -1;

    QuickSort(array, index, right);

    checkpointTimer();
    if(timeExpired()) return -1;
    return comparisons;
}

template<typename T>
int TimedSorter<T>::partition(T* array, int left, int right, T pivot)
{
    //swap left number and right number in the array if right number is smaller than left number
    while(left < right)
    {   
        while(array[left] < pivot) 
        {
            left++; 
            comparisons++;
            checkpointTimer();
            if(timeExpired()) return -1;
        }
        while(array[right] > pivot) 
        {
            right--; 
            comparisons++;
            checkpointTimer();
            if(timeExpired()) return -1;
        }


        comparisons++;
        if(left <= right)
        {
            checkpointTimer();
            if(timeExpired()) return -1;
            std::swap(array[right], array[left]);
            left++;
            right--;
        }
    }
    return left;
}



template class TimedSorter<int>;
template class TimedSorter<float>;






























