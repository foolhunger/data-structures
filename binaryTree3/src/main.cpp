#include <iostream>
#include <cstdlib>
#include "../include/binaryTree3.h"

using namespace std;

int main()
{
    binaryTree3 BTree3;
    binaryTree3::nodesDataContainer treeNodes;

    string nodeData;
    std::cout << "Enter tree nodes:" << std::endl;
    while(cin >> nodeData)
    {
        treeNodes.push_back(nodeData);
    }

    if(!BTree3.Create(treeNodes, "#"))
    {
        std::cerr << "failed to create the binary tree." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Pre:  ";
    BTree3.preOrderTraverse();
    std::cout << std::endl;
    
    std::cout << "In:   ";
    BTree3.inOrderTraverse();
    std::cout << std::endl;

    std::cout << "Post: ";
    BTree3.postOrderTraverse();
    std::cout << std::endl;

    BTree3.levelOrderTraverse(binaryTree3::PRO);
    std::cout << std::endl;

    return EXIT_SUCCESS;
}

