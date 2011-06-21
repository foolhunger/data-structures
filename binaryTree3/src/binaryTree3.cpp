#include "../include/binaryTree3.h"
#include <cstdlib>
#include <queue>

bool binaryTree3::Create(const nodesDataContainer &nodesData, const std::string &semaphore)
{
    if(m_treeTop)
    {
        return false;
    }
    m_semaphore = semaphore;
    pcIterator pcIter = nodesData.begin();

    _create_pre(m_treeTop, nodesData, pcIter);

    return _validate(nodesData, pcIter);
}

void binaryTree3::_create_pre(BT3Node *&pNode, const nodesDataContainer &nodesData, pcIterator &pcIter)
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
        _create_pre(pNode->plChild, nodesData, ++pcIter);
        _create_pre(pNode->prChild, nodesData, ++pcIter);
        if(pNode == m_treeTop)
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

bool binaryTree3::_validate(const nodesDataContainer &nodesData, pcIterator pcIter) const
{
    for(++pcIter; pcIter < nodesData.end(); ++pcIter)
    {
        if(*pcIter != m_semaphore)
            return false;
    }
    return true;
}

void binaryTree3::Clear()
{
    _clear(m_treeTop);
    m_treeTop = NULL;
}

void binaryTree3::_clear(BT3Node *&pNode)
{
    if(!pNode)
    {
        return ;
    }
    if(pNode->plChild)
    {
        _clear(pNode->plChild);
    }
    if(pNode->prChild)
    {
        _clear(pNode->prChild);
    }
    delete pNode;
    pNode = NULL;
}

size_t binaryTree3::Count() const
{
    return _count(m_treeTop);
}

size_t binaryTree3::_count(const BT3Node *const pNode) const
{
    if(!pNode)
    {
        return 0;
    }

    size_t lCount = _count(pNode->plChild);
    size_t rCount = _count(pNode->prChild);

    return lCount + rCount + 1;
}

size_t binaryTree3::Depth() const
{
    return _depth(m_treeTop);
}

size_t binaryTree3::_depth(const BT3Node *const pNode) const
{
    if(!pNode)
    {
        return 0;
    }

    size_t lDepth = _depth(pNode->plChild);
    size_t rDepth = _depth(pNode->prChild);

    return ((lDepth >= rDepth) ? lDepth + 1 : rDepth + 1);
}

void binaryTree3::preOrderTraverse() const
{
    _traverse_pre(m_treeTop);
}

void binaryTree3::_traverse_pre(const BT3Node *const pNode) const
{
    if(!pNode)
    {
        return ;
    }
    std::cout << pNode->data << " ";
    _traverse_pre(pNode->plChild);
    _traverse_pre(pNode->prChild);
}

void binaryTree3::inOrderTraverse() const
{
    _traverse_in(m_treeTop);
}

void binaryTree3::_traverse_in(const BT3Node *const pNode) const
{
    if(!pNode)
    {
        return ;
    }
    _traverse_in(pNode->plChild);
    std::cout << pNode->data << " ";
    _traverse_in(pNode->prChild);
}

void binaryTree3::postOrderTraverse() const
{
    _traverse_post(m_treeTop);
}

void binaryTree3::_traverse_post(const BT3Node *const pNode) const
{
    if(!pNode)
    {
        return ;
    }
    _traverse_post(pNode->plChild);
    _traverse_post(pNode->prChild);
    std::cout << pNode->data << " ";
}

void binaryTree3::levelOrderTraverse(const BT3Mode mode) const
{
    if(!m_treeTop)
    {
        return ;
    }
    std::queue<const BT3Node*> queue; 
    queue.push(m_treeTop);
    while(!queue.empty())
    {
        size_t nodes_num = queue.size();
        for(size_t index = 0; index < nodes_num; ++index)
        {
            if(!queue.front() && (mode == PRO))
            {
                std::cout << "# ";
            }
            if(queue.front())
            {
                std::cout << queue.front()->data << " ";
                queue.push(queue.front()->plChild);
                queue.push(queue.front()->prChild);
            }
            queue.pop();
        }
        if((mode == PRO) && !queue.empty())
        {
            std::cout << std::endl;
        }
    }
}

/*
BT3Node* binaryTree3::_find_node_pre(const BT3Node *const pNode, const BT3Node::nodeDataType &data) const
{
    if(!pNode)
    {
        return NULL;
    }
    if(pNode->data == data)
    {
        return pNode;
    }
    _find_node_pre(pNode->lChild);
    _find_node_pre(pNode->rChild);

    return NULL;
}
*/

