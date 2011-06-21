#ifndef _BINARYTREE3_H_
#define _BINARYTREE3_H_

#include <iostream>
#include <string>
#include <vector>
#include "BT3Node.h"

class binaryTree3
{
public:
    typedef std::vector<BT3Node::nodeDataType> nodesDataContainer;
    typedef nodesDataContainer::const_iterator pcIterator;
    typedef enum BT3Mode{EXPRESS, NORM, PRO};

    binaryTree3(): m_treeTop(NULL){}; 
    ~binaryTree3(){};

    bool Create(const nodesDataContainer &nodesData, const BT3Node::nodeDataType &semaphore);
    void Clear();
    bool Empty() const;
    size_t Count() const;
    size_t Depth() const;
    void preOrderTraverse() const;
    void inOrderTraverse() const;
    void postOrderTraverse() const;
    void levelOrderTraverse(const BT3Mode mode = NORM) const;
    bool lChild(const BT3Node::nodeDataType &data) const;
    bool rChild(const BT3Node::nodeDataType &data) const;

private:
    BT3Node *m_treeTop;
    BT3Node::nodeDataType m_semaphore;

    void _create_pre(BT3Node *&pNode, const nodesDataContainer &nodesData, pcIterator &pcIter);
    bool _validate(const nodesDataContainer &nodesData, pcIterator pcIter) const;
    void _clear(BT3Node *&pNode);
    size_t _count(const BT3Node *const pNode) const;
    size_t _depth(const BT3Node *const pNode) const;
    void _traverse_pre(const BT3Node *const pNode) const;
    void _traverse_in(const BT3Node *const pNode) const;
    void _traverse_post(const BT3Node *const pNode) const;
    //BT3Node* _find_node_pre(const BT3Node::nodeDataType &data) const;
};

// ==========> inline functions <==========

inline bool binaryTree3::Empty() const
{
    return !m_treeTop;
}

#endif

