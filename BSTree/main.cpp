//Program to test BSTree

#include <iostream>
#include "BSTree.hpp"
#include "Logger.hpp"

int main()
{   
    BSTree<int> myTree;

    //ensure not doing balaced insert
    myTree.DisableAVL();

    // myTree.Insert(100);
    // myTree.Insert(50);
    // myTree.Insert(150);
    // myTree.Insert(80);
    // myTree.Insert(75);

    //Insert data
    myTree.Insert(45);
    myTree.Insert(87);
    myTree.Insert(12);
    myTree.Insert(13);
    myTree.Insert(20);
    myTree.Insert(66);
    myTree.Insert(77);
    myTree.Insert(88);
    myTree.Insert(11);
    myTree.Insert(9);
    myTree.Insert(21);
    myTree.Insert(34);
    myTree.Insert(26);
    myTree.Insert(55);
    myTree.Insert(18);
    myTree.Insert(23);
    myTree.Insert(24);
    myTree.Insert(7);
    myTree.Insert(50);
    myTree.Insert(2);
    myTree.Insert(10);
    myTree.Insert(90);
    myTree.Insert(86);
    myTree.Insert(52);
    myTree.Insert(81);
    myTree.Insert(22);
    myTree.Insert(29);
    myTree.Insert(15);
    myTree.Insert(6);
    myTree.Insert(14);
    myTree.DotFormat();

    //compute and print average computational effort (ACE)
    float ace = myTree.ComputeACE();
    std::cout << "ACE: " << ace << std::endl;

    // now print a structured traversal of the tree
    std::cout << "Inorder Traversal: " << std::endl << "[";
    myTree.InOrderPrint();

    std::cout << "Preorder Traversal: " << std::endl;
    myTree.PreOrderPrint();

    std::cout << "Postorder Traversal: " << std::endl;
    myTree.PostOrderPrint();

    //Search the tree
    std::string ans = "no";
    if(myTree.Search(11))
    {
        ans = "yes";
    }
    std::cout << "Is 11 in the tree? " << ans<< std::endl;
    ans = "no";
    if(myTree.Search(15))
    {
        ans = "yes";
    }
    std::cout << "Is 15 in the tree? " << ans << std::endl;


    //now clear the tree, enable AVL property, Insert items, compute ACE, and print traversals

    myTree.Clear();
    
    myTree.EnableAVL();

    // myTree.Insert(100);
    // myTree.Insert(50);
    // myTree.Insert(150);
    // myTree.Insert(80);
    // myTree.Insert(75);

    //Insert data
    myTree.Insert(45);
    myTree.Insert(87);
    myTree.Insert(12);
    myTree.Insert(13);
    myTree.Insert(20);
    myTree.Insert(66);
    myTree.Insert(77);
    myTree.Insert(88);
    myTree.Insert(11);
    myTree.Insert(9);
    myTree.Insert(21);
    myTree.Insert(34);
    myTree.Insert(26);
    myTree.Insert(55);
    myTree.Insert(18);
    myTree.Insert(23);
    myTree.Insert(24);
    myTree.Insert(7);
    myTree.Insert(50);
    myTree.Insert(2);
    myTree.Insert(10);
    myTree.Insert(90);
    myTree.Insert(86);
    myTree.Insert(52);
    myTree.Insert(81);
    myTree.Insert(22);
    myTree.Insert(29);
    myTree.Insert(15);
    myTree.Insert(6);
    myTree.Insert(14);
    myTree.DotFormat();

    // now print a structured traversal of the tree
    std::cout << "Inorder Traversal: " << std::endl;
    myTree.InOrderPrint();

    std::cout << "Preorder Traversal: " << std::endl;
    myTree.PreOrderPrint();

    std::cout << "Postorder Traversal: " << std::endl;
    myTree.PostOrderPrint();

    //compute and print average computational effort (ACE)
    ace = myTree.ComputeACE();
    std::cout << "ACE: " << ace << std::endl;

}