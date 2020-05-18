
#ifndef BSTREENODE_HPP
#define BSTREENODE_HPP

#include <string>
template <typename T>
class BSTreeNode
{
    private:
        T data;
        BSTreeNode<T> *rightChild;
        BSTreeNode<T> *leftChild;
        //using parent node to determine when the root has to be adjusted
        BSTreeNode<T> *parent;

        int balanceFactor;
        // if change root is true then the root gets adjusted
        bool changeRoot;

        void rightRotation();
        void leftRotation();
        void leftRightRotation();
        void rightLeftRotation();
        void ComputeEffort(int level, int & totalEffort, int & size);
    public:
        BSTreeNode(const T& value); //custom constructor

        ~BSTreeNode();

        BSTreeNode<T> & operator=(const BSTreeNode<T> rhs);

        //delegate target for BSTree's version in Insert
        void Insert(const T& value);

        //the AVL version of Insert
        BSTreeNode<T> * InsertAVL(const T& value);

        // more here from BSTree.hpp
        bool Search(const T& value);

        void InOrderPrint();
        void PostOrderPrint();
        void PreOrderPrint();
        void DotFormat();

        float ComputeACE();

};


#endif