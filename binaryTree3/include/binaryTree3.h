#ifndef _BINARYTREE3_H_
#define _BINARYTREE3_H_

#include <iostream>
#include <string>
#include <vector>
#include "BT3Node.h"

class binaryTree3
{
public:
    typedef std::vector<std::string> nodesDataContainer;
    typedef nodesDataContainer::const_iterator pcIterator;

    binaryTree3(): m_treeTop(NULL){}; 
    ~binaryTree3();

    bool Create(const nodesDataContainer &nodesData, const std::string &semaphore);
private:
    BT3Node *m_treeTop;
    std::string m_semaphore;

    void _create(BT3Node *&pNode, const nodesDataContainer &nodesData, pcIterator &pcIter);
    bool _validate(const nodesDataContainer &nodesData, pcIterator pcIter) const;
};

#endif

