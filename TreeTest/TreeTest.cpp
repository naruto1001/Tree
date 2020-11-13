#include "BST.h"
#include <iostream>

int main()
{
    //A(B(D,E(G,)),C(,F))#
    BinTree<char>* tree = new BinTree<char>('#');
    tree->CreateBinTree();
    tree->PerOrder(tree->GetRoot());
    std::cout << std::endl;
    tree->PerOrder_NoRecurvel(tree->GetRoot());
    std::cout << std::endl;
    tree->InOrder(tree->GetRoot());
    std::cout << std::endl;
    tree->InOrder_NoRecurvel(tree->GetRoot());
    std::cout << std::endl;
    tree->postOrder(tree->GetRoot());
    std::cout << std::endl;
    tree->postOrder_NoRecurve(tree->GetRoot());
} 