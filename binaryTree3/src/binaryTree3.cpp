#include "../include/binaryTree3.h"

bool binaryTree3::Create(const nodesDataContainer &nodesData, const std::string &semaphore)

    m_semaphore = semaphore;
    pcIterator pcIter = nodesData.begin();

    _create(treeTop, nodesData, pcIter);

    return _validate();
}

void binaryTree3::_create(BT3Node *&pNode, const nodesDataContainer &nodesData, pcIterator &pcIter)
{
    pNode = NULL;
    if(pcIter < nodesData.end() && *pcIter != m_semaphore)
    {
        if(!(pNode = new(BT3Node)))
        {
            std::cerr << "memory error occurred..." << std::endl;
            exit(EXIT_FAILURE);
        }
        pNode->data = *pcIter;
        _create(pNode->plChild, nodesData, ++pcIter);
        _create(pNode->prChild, nodesData, ++pcIter);
        if(pNode == treeTop)
        {
            pNode->pParent = NULL;
        }
        if(pNode->plChild)
        {
            pNode->plChild->pParent = pNode;
        }
        if(pNode->prChild)
        {
            pNode->prChild->pParent = pNode;
        }
    }
}

bool binaryTree::_validate(const nodesDataContainer &nodesData, pcIterator pcIter) const
{
    for(++pcIter; pcIter < nodesData.end(); ++pcIter)
    {
        if(*pcIter != m_semaphore)
            return false;
    }
    return true;
}

