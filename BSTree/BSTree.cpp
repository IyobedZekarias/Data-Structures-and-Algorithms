//BSTree.cpp

#include "BSTree.hpp"

//default constructor
template <typename T>
BSTree<T>::BSTree()
{
    root = nullptr;
    avlEnabled = false;
    treeSize = 0;
}

//destructor
template <typename T>
BSTree<T>::~BSTree()
{
    //will fill
    delete root;
}

//Enable and Disable AVL
template <typename T>
void BSTree<T>::EnableAVL()
{
    avlEnabled = true;
}

template <typename T>
void BSTree<T>::DisableAVL()
{
    avlEnabled = false;
}

//insert Data
template <typename T>
void BSTree<T>::Insert(const T& value)
{
    if(root == nullptr)
    {
        //this menas the tree is empty 
        root = new BSTreeNode<T>(value);
    }
    else
    {
        //this means the tree is not empty 
        if(avlEnabled)
        {
            root = root -> InsertAVL(value);
        }
        else
        {
            root -> Insert(value);
        }
    }
    treeSize++;
}

template <typename T>
void BSTree<T>::Clear()
{
    delete root;
    root = nullptr;
    avlEnabled = false;
    treeSize = 0;
}

//Inorder print left side, root, right side
template <typename T>
void BSTree<T>::InOrderPrint()
{
    if(root != nullptr)
    {
        root->InOrderPrint();
        std::cout << std::endl;
    }
    
}

//Preorder print root, left side, right side
template <typename T>
void BSTree<T>::PreOrderPrint()
{
    if(root != nullptr)
    {
        root->PreOrderPrint();
        std::cout << std::endl;
    }
}

//postorder print left side, right side, root
template <typename T>
void BSTree<T>::PostOrderPrint()
{
    if (root != nullptr)
    {
        root->PostOrderPrint();
        std::cout << std::endl;
    }
}

//dot format print
template <typename T>
void BSTree<T>::DotFormat()
{
    if (root != nullptr)
    {
        std::cout << "Graph G {" << std::endl;
        root -> DotFormat();
        std::cout << "}" << std::endl;
    }
}


template <typename T>
bool BSTree<T>::Search(const T &data)
{
    if(root != nullptr)
    {
        return root -> Search(data);
    }
    return false;
}

template <typename T>
float BSTree<T>::ComputeACE()
{
    return (root==nullptr) ? 0.0f : root->ComputeACE();
}




template class BSTree<int>;
template class BSTree<float>;