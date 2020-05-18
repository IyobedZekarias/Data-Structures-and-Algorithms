

#include "BSTreeNode.hpp"
#include <iostream>

//custom constructor
template <typename T>
BSTreeNode<T>::BSTreeNode(const T& value)
{
    data = value;
    leftChild = nullptr;
    rightChild = nullptr;
    parent = nullptr;
    balanceFactor = 1;
}

//destructor
template <typename T>
BSTreeNode<T>::~BSTreeNode()
{
    // what to do here
    delete leftChild;
    delete rightChild;
    
}

//Insert at the current node
template <typename T>
void BSTreeNode<T>::Insert(const T& value)
{
    // no duplicate values
    if (value == data)
    {
        return;
    }
    else if (value < data)
    {
        // value goes to the left if left child is null
        if (leftChild == nullptr)
        {
            //make a new node and make left child it
            leftChild = new BSTreeNode<T>(value);
            //subTreeSize++;
        }
        else 
        {
            leftChild -> Insert(value);
        }
    }
    else
    {
        //must mena value is greater than the data
        if (rightChild == nullptr)
        {
            rightChild = new BSTreeNode<T>(value);
            //subTreeSize++;
        }
        else 
        {
            rightChild -> Insert(value);
        }
    }
    
}

//Insert and set the balance factor 
//once inserted make sure that there are no imbalances 
//imbalances are checked by checking both sides of the node and seeing if either side is less than 
//the current nodes balance factor by a margin of 3 or more
template <typename T>
BSTreeNode<T> * BSTreeNode<T>::InsertAVL(const T& value)
{
    if(value == data)
    {
        return this;
    }
    else if(value < data)
    {
        if(leftChild == nullptr)
        {
            leftChild = new BSTreeNode<T>(value);
            leftChild->balanceFactor = 1;
            int temp = leftChild -> balanceFactor + 1;
            if(temp > balanceFactor)
            {
                balanceFactor++;
            }
            leftChild->parent = this;
        }
        else
        {
            leftChild->InsertAVL(value);
            int temp = leftChild -> balanceFactor + 1;
            if(temp > balanceFactor)
            {
                balanceFactor++;
            }
        }
        
    }
    else
    {
        if(rightChild == nullptr)
        {
            rightChild = new BSTreeNode<T>(value);
            rightChild->balanceFactor = 1;
            int temp = rightChild -> balanceFactor + 1;
            if(temp > balanceFactor)
            {
                balanceFactor++;
            }
            rightChild->parent = this;
        }
        else
        {
            rightChild -> InsertAVL(value);
            int temp = rightChild -> balanceFactor + 1;
            if(temp > balanceFactor)
            {
                balanceFactor++;
            }
        }
        
    }
    changeRoot = false;

    int leftfactor = 0;
    int rightfactor = 0;
    if(leftChild != nullptr)
    {
        leftfactor = leftChild->balanceFactor;
    }
    if(rightChild != nullptr)
    {
        rightfactor = rightChild->balanceFactor;
    }
    
    int leftSide = balanceFactor-leftfactor;
    int rightSide = balanceFactor-rightfactor;
    if(leftSide > 2)
    {
        
        int leftfactor = 0;
        int rightfactor = 0;
        if(leftChild != nullptr && leftChild->leftChild != nullptr)
        {
            leftfactor = leftChild->leftChild->balanceFactor;
        }
        if(rightChild != nullptr && rightChild->rightChild != nullptr)
        {
            rightfactor = rightChild->rightChild->balanceFactor;
        }

        //single left rotation
        if(rightfactor > leftfactor)
        {
            std::cout << "imbalance in tree at: " << data << " left rotation"  << std::endl;
            rightRotation();
        }
        else
        {
            std::cout << "imbalance in tree at: " << data << " right-left rotation" << std::endl;
            rightLeftRotation();
        }
        
    }
    if(rightSide > 2)
    {
        int leftfactor = 0;
        int rightfactor = 0;
        if(leftChild != nullptr && leftChild->leftChild != nullptr)
        {
            leftfactor = leftChild->leftChild->balanceFactor;
        }
        if(rightChild != nullptr && rightChild->rightChild != nullptr)
        {
            rightfactor = rightChild->rightChild->balanceFactor;
        }

        //single right rotation
        if(leftfactor > rightfactor)
        {
            std::cout << "imbalance in tree at: " << data << " right rotation" << std::endl;
            leftRotation();
            
        }
        else
        {
            std::cout << "imbalance in tree at: " << data << " left-right rotation" << std::endl;
            leftRightRotation();
        }
        
        
    }
    if(changeRoot)
    {
        return this->parent;
    }
    return this;

}

template <typename T>
void BSTreeNode<T>::InOrderPrint()
{
    if(leftChild != nullptr){
        leftChild->InOrderPrint();
    }
    std::cout << this->data << " ";
    if(rightChild != nullptr){
        rightChild->InOrderPrint();
    }
}

template <typename T>
void BSTreeNode<T>::PreOrderPrint()
{
    std::cout << this->data << " ";
    if(leftChild != nullptr)
    {
        leftChild -> PreOrderPrint();
    }
    if(rightChild != nullptr)
    {
        rightChild -> PreOrderPrint();
    }
}

template <typename T>
void BSTreeNode<T>::PostOrderPrint()
{
    if(leftChild != nullptr)
    {
        leftChild -> PostOrderPrint();
    }
    if(rightChild != nullptr)
    {
        rightChild -> PostOrderPrint();
    }
    std::cout << this->data << " ";
}

template <typename T>
void BSTreeNode<T>::DotFormat()
{
    if(leftChild != nullptr)
    {
        std::cout << "\"" << data << "\"";
        std::cout << " -- \"" << leftChild->data << "\"" << std::endl;
        leftChild->DotFormat();
    }
    if(rightChild != nullptr)
    {
        std::cout << "\"" << data << "\"";
        std::cout << " -- \"" << rightChild->data << "\"" << std::endl;
        rightChild->DotFormat();
    }
    if(rightChild == nullptr && leftChild == nullptr)
    {
        std::cout << "\"" << data << "\"" << std::endl;
    }
}

template <typename T>
bool BSTreeNode<T>::Search(const T &value)
{
    if(this->data == value)
    {
        return true;
    }
    else if(this->data > value)
    {
        if(this->leftChild != nullptr)
        {
            return this->leftChild->Search(value);
        }
    }
    else if(this->data < value)
    {
        if(this->leftChild)
        {
            return this->rightChild->Search(value);
        }
    }
    return false;
}

template <typename T>
void BSTreeNode<T>::rightRotation()
{
    changeRoot = false;
    if(this->parent == nullptr)
    {
        changeRoot = true;
    }
    BSTreeNode *a = this;
    BSTreeNode *b = this->rightChild;
    a->rightChild = b->leftChild;
    if(a->rightChild != nullptr)
    {
        a->rightChild->parent = a;
    }
    b->parent = a->parent;
    b->leftChild = a;
    if(b->parent != nullptr)
    {
        b->parent->rightChild = b;
    }
    a->parent = b;

    balanceFactor = b->balanceFactor - 1;
}

template <typename T>
void BSTreeNode<T>::leftRotation()
{
    
    changeRoot = false;
    if(this->parent == nullptr)
    {
        changeRoot = true;
    }

    BSTreeNode *a = this;
    BSTreeNode *b = this->leftChild;
    a->leftChild = b->rightChild;
    if(a->leftChild != nullptr)
    {
        a->leftChild->parent = a;
    }
    b->parent = a->parent;
    b->rightChild = a;
    if(b->parent != nullptr)
    {
        b->parent->leftChild = b;
    }
    a->parent = b;

    balanceFactor = b->balanceFactor - 1;
}

template <typename T>
void BSTreeNode<T>::rightLeftRotation()
{
    BSTreeNode<T> *b = this->rightChild->leftChild;
    BSTreeNode<T> *c = this->rightChild;
    b->balanceFactor = this -> balanceFactor - 1;
    c->balanceFactor = this -> balanceFactor - 2;
    b->parent = this;
    c->parent = b;
    c->leftChild = nullptr;
    this->leftChild = b;
    this->rightChild = nullptr;
    b->leftChild = c;
    leftRotation();

    // BSTreeNode *a = this;
    // BSTreeNode *b = this->rightChild;
    // BSTreeNode *c = this->rightChild->leftChild;
    // changeRoot = false;
    // if(parent == nullptr)
    // {
    //     changeRoot = true;
    // }

    // c->parent = a->parent;
    // b->parent = c;

    // if(!changeRoot)
    // {
    //     if(this->parent->rightChild == a)
    //     {
    //         this->parent->rightChild = c;
    //     }
    //     else
    //     {
    //         this->parent->leftChild = c;
    //     }
 
    // }
    // a->parent = c;

    // a->rightChild = nullptr;
    // c->rightChild = b;

    // a->leftChild = nullptr;
    // c->leftChild = a;

    // b->balanceFactor = this -> balanceFactor - 2;
    // c->balanceFactor = this -> balanceFactor - 1;
    // balanceFactor = b->balanceFactor;

}

template <typename T>
void BSTreeNode<T>::leftRightRotation()
{
    BSTreeNode<T> *b = this->leftChild->rightChild;
    BSTreeNode<T> *c = this->leftChild;
    b->balanceFactor = this -> balanceFactor - 1;
    c->balanceFactor = this -> balanceFactor - 2;
    b->parent = this;
    c->parent = b;
    c->rightChild = nullptr;
    this->rightChild = b;
    this->leftChild = nullptr;
    b->rightChild = c;
    rightRotation();
}

template <typename T>
float BSTreeNode<T>::ComputeACE()
{
    int subTreeSize = 0;
    int totalEffort = 0;
    ComputeEffort(1, totalEffort, subTreeSize);

    std::cout << "Total Effort: "  << totalEffort << std::endl << "Size: " << subTreeSize << std::endl;

    return (float) totalEffort / (float) subTreeSize;
}

template <typename T>
void BSTreeNode<T>::ComputeEffort(int level, int & totalEffort, int & size)
{
    if(leftChild != nullptr)
    {
        leftChild -> ComputeEffort(level + 1, totalEffort, size);
    }
    if(rightChild != nullptr)
    {
        rightChild -> ComputeEffort(level + 1, totalEffort, size);
    }
    size++;
    totalEffort += level;
}

template class BSTreeNode<int>;
template class BSTreeNode<float>;
