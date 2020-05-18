

#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>

template <typename T>
struct ListNode
{
    ListNode<T> *prev;
    T val;
    ListNode<T> *next;
};

template <typename T>
class LList
{
    private:
        ListNode<T> *head;
        ListNode<T> *tail;

        size_t ListSize;

        void PrivateInsert(T val, size_t pos);
        bool contains(T val);
        void remove(ListNode<T> *n);

    public:
        //ctor
        LList();
        //dtor
        ~LList();

        //copy constructor
        LList(const LList<T> &inList);

        //Union
        LList<T> Union(const LList<T> &rhs);

         //Intersection
        LList<T> Intersection(const LList<T> &rhs);

        //assignment operator
        LList<T> & operator=(const LList<T> &rhs);

        //difference operator
        LList<T> & operator-(LList<T> &rhs);

        //List Insert at position 
        void Insert(T val, size_t pos);
        
        //Return a string of the list
        std::string PrettyPrint();

        //Put at the end of the list
        void Append(T val);

        //Put at the beginning of the List
        void Prepend(T val);

        //Get the size of the List
        size_t Size();

        //is the list empty 
        bool IsEmpty();

        //clear the list
        void Clear();
};

#endif