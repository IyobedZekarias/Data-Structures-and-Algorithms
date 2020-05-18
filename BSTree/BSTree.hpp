//BSTree.hpp

#ifndef BSTREE_HPP
#define BSTREE_HPP

#include <iostream>
#include <string>
#include "BSTreeNode.hpp"

template <typename T>
class BSTree
{
    private:
        BSTreeNode<T> *root;
        BSTreeNode<T> *temp;
        bool avlEnabled;
        size_t treeSize;

    public:
        //ctor
        BSTree();
        //dtor
        ~BSTree();

        //copy ctor
        //BSTree(const BSTree<T> &proto);

        //assignment operator
        //const BSTree<T> & operator=(const BSTree<T> &rhs);

        //Binary Search Tree ADT methods

        //Insert data into tree
        void Insert(const T &data);

        //Look to see if tree contains a particular data element
        bool Search(const T &data);

        //the number of elements in the tree
        size_t Size();

        //clear the tree
        void Clear();

        //determine if tree is empty 
        bool IsEmpty();

        //compute the ACE
        float ComputeACE();

        //printing traversals
        void InOrderPrint();
        void PreOrderPrint();
        void PostOrderPrint();
        void DotFormat();

        //enable or disable AVL property 
        void EnableAVL();
        void DisableAVL();

};

#endif