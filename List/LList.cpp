

#include "LList.hpp"
#include <string>
#include <sstream>

template <typename T> 
LList<T>::LList()
{
    //tart everything off
    head = nullptr;
    tail = nullptr;
    ListSize = 0;
}

template <typename T> 
LList<T>::~LList()
{
    //destroy the whole list
    ListNode<T> *caret = head;
    ListNode<T> *next = head;
    while(caret != nullptr)
    {
        next = caret->next;
        delete caret;
        caret = next;
    }
}

template <typename T>
bool LList<T>::contains(T value)
{
    //check if something is contained within the list
    ListNode<T> *caret = head;
    while(caret != nullptr)
    {
        if(caret->val == value) {return true;}
        else {caret = caret->next;}
        
    }
    return false;
}

template <typename T>
void LList<T>::Insert(T value, size_t pos)
{
    //Pass to the private insert function 
    PrivateInsert(value, pos);
}

template <typename T> 
void LList<T>::PrivateInsert(T value, size_t pos)
{
    //Case 1: Insert at beginning of List
    if(pos == 0)
    {
        //Instantiate a new ListNode struct with value set
        ListNode<T> *newNode = new ListNode<T>;
        newNode->val = value;
        newNode->next = head;
        newNode->prev = nullptr;

        if(head != nullptr)
        {
            head->prev = newNode;
        }
        else //List was empty
        {
            tail = newNode;
        }
        head = newNode;

        ListSize++;
    }
    //Case 2: Insert in the middle of the List
    else if(ListSize > pos)
    {
        ListNode<T> *newNode = new ListNode<T>;
        newNode->val = value;

        ListNode<T> *nxtNode = head;
        ListNode<T> *prvNode = head;
        for(size_t i = 0; i < ListSize; i++)
        {
            if(i == pos)
            {
                newNode->next = nxtNode;
                newNode->prev = prvNode;
                prvNode->next = newNode;
                nxtNode->prev = newNode;
                break;
            }
            if(i >= 1)
            {
                prvNode = prvNode -> next;
            }
            nxtNode = nxtNode -> next;
            
        }
        
    }

    //Case 3: insert at the end of the List
    else if(pos >= ListSize)
    {
        //Insert at the end here 
        ListNode<T> *newNode = new ListNode<T>;
        newNode->val = value;
        newNode->next = nullptr;
        
        if(head == nullptr)
        {
            newNode->prev = nullptr;
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;

        }

        ListSize++;
        
    }
}

//Remove something that might be in the list
template <typename T>
void LList<T>::remove(ListNode<T> *n)
{
    ListNode<T> *caret = head;
    while(caret != nullptr)
    {
        if(caret->val == n->val) 
        {
            n = caret;
            break;
        }
        else {caret = caret->next;}
        
    }
    //if n is head
    if(head->next == n->next)
    {
        ListNode<T> *next_n = n->next;
        next_n->prev = nullptr;
        head = next_n;
        delete n;
    }
    //if n is tail
    else if(tail->prev == n->prev)
    {
        ListNode<T> *prev_n = n->prev;
        prev_n->next = nullptr;
        tail = prev_n;
        delete n;
    }
    //if n is in the middle
    else
    {
        ListNode<T> *next_n = n->next;
        ListNode<T> *prev_n = n->prev;
        next_n->prev = prev_n;
        prev_n->next = next_n;
        delete n;
    }
    
}

//copy constructor
template <typename T>
LList<T>::LList(const LList<T> &inList)
{
    ListNode<T> *caret = inList.head;
    ListNode<T> *prev_n = nullptr;
    //for each element of inlist make a duplicate in our list and insert it
    for(size_t i = 0; i < inList.ListSize; i++)
    {
        //make a new ListNode element 
        ListNode<T> *n = new ListNode<T>;
        
        //Setting the list nodes properties
        n->val = caret->val;

        //insert listnode to the list at the end
        n->prev = prev_n;
        n->next = nullptr;
        if (prev_n != nullptr)
        {
            prev_n->next = n;
        }
        tail = n;

        //If this is the first node set the head
        if(i == 0)
        {
            head = n;
        }

        
        //increment caret to the next inlist element
        caret = caret->next;

        prev_n = n;
    }

    ListSize = inList.ListSize;

}

//assignment operator for =
template <typename T>
LList<T> & LList<T>::operator=(const LList<T> &rhs)
{
   if (this != &rhs) 
   {
       LList<T> tmp(rhs);

       std::swap(tmp.head, head);
       std::swap(tmp.tail, tail);
       std::swap(tmp.ListSize, ListSize);
   }
   return *this;

}

//assignment operator for -
template <typename T>
LList<T> & LList<T>::operator-(LList<T> &rhs)
{
    ListNode<T> *caret = rhs.tail;

    do{
        if(contains(caret->val) == true)
        {
            remove(caret);
        }
        caret = caret->prev;
    }
    while(caret != nullptr);

    return *this;
    
}

//finding th eunion of two lists
template <typename T>
LList<T> LList<T>::Union(const LList<T> &rhs)
{
    LList<T> retList(*this);

    ListNode<T> *caret = rhs.head;

    while(caret != nullptr)
    {
        if(contains(caret->val) == false)
        {
            retList.Insert(caret->val, 0);
        }
        caret = caret -> next;
    }

    return retList;
}

//Finding the intersection 
template <typename T>
LList<T> LList<T>::Intersection(const LList<T> &rhs)
{
    LList<T> retList;
    ListNode<T> *caret = rhs.head;

    while(caret != nullptr)
    {
        if(contains(caret->val) == true)
        {
            retList.Insert(caret->val, 0);
        }
        caret = caret -> next;
    }
    return retList;
}

//Return a string of the list
template <typename T>
std::string LList<T>::PrettyPrint()
{
    if(ListSize)
    {
        std::stringstream sreturn;
        sreturn << "List contains: ";

        ListNode<T> *carot = head;

        while (carot != tail)
        {
            sreturn << carot->val << ", ";
            carot = carot -> next;
        }
        sreturn << tail->val;
        return sreturn.str();
    }
    else
    {
        return "Empty List";
    }
    
}

//Put item at beginning of list
template <typename T>
void LList<T>::Append(T val)
{
    PrivateInsert(val, ListSize+1);
}

//Puts item at beginning of the list
template <typename T>
void LList<T>::Prepend(T val)
{
    PrivateInsert(val, 0);
}

//Returns the size of the list
template <typename T>
size_t LList<T>::Size()
{
    return ListSize;
}
 
//Returns if the List is empty or not
template <typename T>
bool LList<T>::IsEmpty()
{
    return !ListSize;
}

//Empty the list by setting it equal to an empty tmplist
template <typename T>
void LList<T>::Clear()
{
    LList<T> tmpList;
    *this = tmpList;
}


template class LList<int>;
template class LList<float>;
template class LList<std::string>;
template class LList<char>;

