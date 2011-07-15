#include <iostream>
#include <cstdlib>
#include "../include/binaryTree3.h"

using namespace std;

int main()
{
    binaryTree3 BTree3;
    binaryTree3 BTree3_dup;
    binaryTree3::nodesDataContainer treeNodes;
    BT3Node::nodeDataType nodeData;

    cout << "Enter tree nodes:" << endl;
    while(cin >> nodeData)
    {
        treeNodes.push_back(nodeData);
    }
    cin.clear();

    cout << "===================> 1st Time Create() <================" << endl;
    if(!BTree3.Create(treeNodes, "#"))
    {
        cerr << BTree3.GetLastError() << endl;
        exit(EXIT_FAILURE);
    }

    cout << "===================> 2nd Time Create() <================" << endl;
    if(!BTree3.Create(treeNodes, "#"))
    {
        cerr << BTree3.GetLastError() << endl;
    }

    if(BTree3.Empty())
    {
        cout << "The binary tree is empty." << endl;
    }
    else
    {
        cout << "The binary tree is NOT empty." << endl;
    }

    cout << "Nodes count: " << BTree3.Count() << endl;

    cout << "Tree Depth:  " << BTree3.Depth() << endl;

    cout << "Pre:  ";
    BTree3.preOrderTraverse();
    cout << endl;
    
    cout << "In:   ";
    BTree3.inOrderTraverse();
    cout << endl;

    cout << "Post: ";
    BTree3.postOrderTraverse();
    cout << endl;

    cout << "Level:" << endl;
    BTree3.levelOrderTraverse();//binaryTree3::PRO);
    cout << endl;

    cout << "====================> lChild() and rChild() <==================" << endl;
    cout << "enter the value to find the left child: ";
    cin >> nodeData;    
    BT3Node::nodeDataType lchild;
    if(BTree3.lChild(lchild, nodeData, binaryTree3::PRE))
    {
        cout << "Pre:   Parent: " << nodeData << " -> lChild: " << lchild << endl;
    }
    else
    {
        cerr << "Pre:   " << BTree3.GetLastError() << endl;
    }
    if(BTree3.lChild(lchild, nodeData, binaryTree3::LEVEL))
    {
        cout << "Level: Parent: " << nodeData << " -> lChild: " << lchild << endl;
    }
    else
    {
        cerr << "Level: " << BTree3.GetLastError() << endl;
    }

    cout << "enter the value to find the right child: ";
    cin >> nodeData;    
    BT3Node::nodeDataType rchild;
    if(BTree3.rChild(rchild, nodeData, binaryTree3::PRE))
    {
        cout << "Pre:   Parent: " << nodeData << " -> rChild: " << rchild << endl;
    }
    else
    {
        cerr << "Pre:   " << BTree3.GetLastError() << endl;
    }
    if(BTree3.rChild(rchild, nodeData, binaryTree3::LEVEL))
    {
        cout << "Level: Parent: " << nodeData << " -> rChild: " << rchild << endl;
    }
    else
    {
        cerr << "Level: " << BTree3.GetLastError() << endl;
    }

    cout << "==================> Parent() <==================" << endl;
    cout << "enter the value to find the parent: ";
    cin >> nodeData;
    BT3Node::nodeDataType parent;
    if(BTree3.Parent(parent, nodeData, binaryTree3::PRE))
    {
        cout << "Pre:   Child: " << nodeData << " -> Parent: " << parent << endl;
    }
    else
    {
        cerr << "Pre:   " << BTree3.GetLastError() << endl;
    }
    if(BTree3.Parent(parent, nodeData, binaryTree3::LEVEL))
    {
        cout << "Level: Child: " << nodeData << " -> Parent: " << parent << endl;
    }
    else
    {
        cerr << "Level: " << BTree3.GetLastError() << endl;
    }

    cout << "enter the value to find the parent: ";
    cin >> nodeData;
    if(BTree3.Parent(parent, nodeData, binaryTree3::PRE))
    {
        cout << "Pre:   Child: " << nodeData << " -> Parent: " << parent << endl;
    }
    else
    {
        cerr << "Pre:   " << BTree3.GetLastError() << endl;
    }
    if(BTree3.Parent(parent, nodeData, binaryTree3::LEVEL))
    {
        cout << "Level: Child: " << nodeData << " -> Parent: " << parent << endl;
    }
    else
    {
        cerr << "Level: " << BTree3.GetLastError() << endl;
    }

    cout << "=====================> Mount() <=====================" << endl;
    treeNodes.clear();
    cout << "enter dup tree nodes:" << endl;
    while(cin >> nodeData)
    {
        treeNodes.push_back(nodeData);
    }
    cin.clear();

    if(!BTree3_dup.Create(treeNodes, "#"))
    {
        cerr << BTree3_dup.GetLastError() << endl;
        exit(EXIT_FAILURE);
    }
 
    cout << "Level(dup): ";
    BTree3_dup.levelOrderTraverse();//binaryTree3::PRO);
    cout << endl;

    cout << "enter the mount point: ";
    cin >> nodeData;
    if(!BTree3.Mount(BTree3_dup, nodeData, binaryTree3::LEVEL, binaryTree3::RIGHT))
    {
        cerr << BTree3.GetLastError() << endl;
    }

    cout << "Pre:  ";
    BTree3.preOrderTraverse();
    cout << endl;
    
    cout << "In:   ";
    BTree3.inOrderTraverse();
    cout << endl;

    cout << "Post: ";
    BTree3.postOrderTraverse();
    cout << endl;

    cout << "Level:" << endl;
    BTree3.levelOrderTraverse();//binaryTree3::PRO);
    cout << endl;

    cout << "Pre(dup):  ";
    BTree3_dup.preOrderTraverse();
    cout << endl;
    
    cout << "In(dup):   ";
    BTree3_dup.inOrderTraverse();
    cout << endl;

    cout << "Post(dup): ";
    BTree3_dup.postOrderTraverse();
    cout << endl;

    cout << "Level(dup):" << endl;
    BTree3_dup.levelOrderTraverse();//binaryTree3::PRO);
    cout << endl;

    cout << "=====================> 2nd Time Mount() <==================" << endl;
    treeNodes.clear();
    cout << "enter dup tree nodes:" << endl;
    while(cin >> nodeData)
    {
        treeNodes.push_back(nodeData);
    }
    cin.clear();

    if(!BTree3_dup.Create(treeNodes, "#"))
    {
        cerr << BTree3_dup.GetLastError() << endl;
        exit(EXIT_FAILURE);
    }
 
    cout << "Level(dup): ";
    BTree3_dup.levelOrderTraverse();//binaryTree3::PRO);
    cout << endl;

    cout << "enter the mount point: ";
    cin >> nodeData;
    if(!BTree3.Mount(BTree3_dup, nodeData, binaryTree3::LEVEL, binaryTree3::RIGHT))
    {
        cerr << BTree3.GetLastError() << endl;
    }

    cout << "Pre:  ";
    BTree3.preOrderTraverse();
    cout << endl;
    
    cout << "In:   ";
    BTree3.inOrderTraverse();
    cout << endl;

    cout << "Post: ";
    BTree3.postOrderTraverse();
    cout << endl;

    cout << "Level:" << endl;
    BTree3.levelOrderTraverse();//binaryTree3::PRO);
    cout << endl;

    cout << "Pre(dup):  ";
    BTree3_dup.preOrderTraverse();
    cout << endl;
    
    cout << "In(dup):   ";
    BTree3_dup.inOrderTraverse();
    cout << endl;

    cout << "Post(dup): ";
    BTree3_dup.postOrderTraverse();
    cout << endl;

    cout << "Level(dup):" << endl;
    BTree3_dup.levelOrderTraverse();//binaryTree3::PRO);
    cout << endl;

/*
    cout << "====================> 3rd Time Mount() <===================" << endl;
    treeNodes.clear();
    cout << "enter dup tree nodes:" << endl;
    while(cin >> nodeData)
    {
        treeNodes.push_back(nodeData);
    }
    cin.clear();

    if(!BTree3_dup.Create(treeNodes, "#"))
    {
        cerr << BTree3_dup.GetLastError() << endl;
        exit(EXIT_FAILURE);
    }
 
    cout << "Level(dup): ";
    BTree3_dup.levelOrderTraverse();//binaryTree3::PRO);
    cout << endl;

    cout << "enter the mount point: ";
    cin >> nodeData;
    if(!BTree3.Mount(BTree3_dup, nodeData, binaryTree3::LEVEL, binaryTree3::RIGHT))
    {
        cerr << BTree3.GetLastError() << endl;
    }

    cout << "Pre:  ";
    BTree3.preOrderTraverse();
    cout << endl;
    
    cout << "In:   ";
    BTree3.inOrderTraverse();
    cout << endl;

    cout << "Post: ";
    BTree3.postOrderTraverse();
    cout << endl;

    cout << "Level:" << endl;
    BTree3.levelOrderTraverse();//binaryTree3::PRO);
    cout << endl;

    cout << "Pre(dup):  ";
    BTree3_dup.preOrderTraverse();
    cout << endl;
    
    cout << "In(dup):   ";
    BTree3_dup.inOrderTraverse();
    cout << endl;

    cout << "Post(dup): ";
    BTree3_dup.postOrderTraverse();
    cout << endl;

    cout << "Level(dup):" << endl;
    BTree3_dup.levelOrderTraverse();//binaryTree3::PRO);
    cout << endl;
*/

    BTree3.ShowMountPoints();

    cout << "===================> unMount() <==================" << endl;
    cout << "enter the unmount point: ";
    cin >> nodeData;
    if(!BTree3.unMount(BTree3_dup, nodeData, binaryTree3::LEVEL, binaryTree3::RIGHT))
    {
        cerr << BTree3.GetLastError() << endl;
    }
    else
    {
        cout << "In:   ";
        BTree3.inOrderTraverse();
        cout << endl;

        cout << "Level:" << endl;
        BTree3.levelOrderTraverse();//binaryTree3::PRO);
        cout << endl;

        cout << "In(dup):   ";
        BTree3_dup.inOrderTraverse();
        cout << endl;

        cout << "Level(dup):" << endl;
        BTree3_dup.levelOrderTraverse();//binaryTree3::PRO);
        cout << endl;
    }

/*
    cout << "======================> 2nd Time unMount() <====================" << endl;
    cout << "enter the unmount point: ";
    cin >> nodeData;
    binaryTree3 BTree3_dup2;
    if(!BTree3.unMount(BTree3_dup2, nodeData, binaryTree3::LEVEL, binaryTree3::RIGHT))
    {
        cerr << BTree3.GetLastError() << endl;
    }
    else
    {
        cout << "In:   ";
        BTree3.inOrderTraverse();
        cout << endl;

        cout << "Level:" << endl;
        BTree3.levelOrderTraverse();//binaryTree3::PRO);
        cout << endl;

        cout << "In(dup2):   ";
        BTree3_dup2.inOrderTraverse();
        cout << endl;

        cout << "Level(dup2):" << endl;
        BTree3_dup2.levelOrderTraverse();//binaryTree3::PRO);
        cout << endl;
    }
*/

    cout << "======================> BTree3_dup unMount() <===================" << endl;
    cout << "enter the unmount point: ";
    cin >> nodeData;
    binaryTree3 BTree3_dup3;
    if(!BTree3_dup.unMount(BTree3_dup3, nodeData, binaryTree3::LEVEL, binaryTree3::RIGHT))
    {
        cerr << BTree3_dup.GetLastError() << endl;
    }
    else
    {
        cout << "In:   ";
        BTree3_dup.inOrderTraverse();
        cout << endl;

        cout << "Level:" << endl;
        BTree3_dup.levelOrderTraverse();//binaryTree3::PRO);
        cout << endl;

        cout << "In(dup3):   ";
        BTree3_dup3.inOrderTraverse();
        cout << endl;

        cout << "Level(dup3):" << endl;
        BTree3_dup3.levelOrderTraverse();//binaryTree3::PRO);
        cout << endl;
    }
    
    BTree3_dup.ShowMountPoints();
    return EXIT_SUCCESS;
}

