#ifndef _BINARYTREE3_H_
#define _BINARYTREE3_H_

#include <string>
#include <vector>
#include <list>
#include "BT3Node.h"

class binaryTree3
{
public:
    typedef std::vector<BT3Node::nodeDataType> nodesDataContainer;
    typedef nodesDataContainer::iterator pContainerIterator;
    typedef nodesDataContainer::const_iterator pcContainerIterator;
    enum BT3Mode{NORM, PRO, RECURSIVE, PRE, IN, POST, LEVEL, LEFT, RIGHT};

    binaryTree3(): m_treeTop(NULL){}; 
    ~binaryTree3();

    bool Create(const nodesDataContainer &nodesData, const BT3Node::nodeDataType &semaphore);
    bool Clear();
    bool Empty() const;
    size_t Count() const;
    size_t Depth() const;
    bool Root(BT3Node::nodeDataType &root) const;
    void preOrderTraverse() const;
    void inOrderTraverse() const;
    void postOrderTraverse() const;
    void levelOrderTraverse(const BT3Mode mode = NORM) const;
    bool lChild(BT3Node::nodeDataType &lchild, const BT3Node::nodeDataType &data, 
                const BT3Mode mode = LEVEL) const;
    bool rChild(BT3Node::nodeDataType &rchild, const BT3Node::nodeDataType &data, 
                const BT3Mode mode = LEVEL) const;
    bool lSibling(BT3Node::nodeDataType &lsibling, const BT3Node::nodeDataType &data,
                const BT3Mode mode = LEVEL) const;
    bool rSibling(BT3Node::nodeDataType &rsibling, const BT3Node::nodeDataType &data,
                const BT3Mode mode = LEVEL) const;
    bool Parent(BT3Node::nodeDataType &parent, const BT3Node::nodeDataType &data,
                const BT3Mode mode = LEVEL) const;
    bool Assign(const BT3Node::nodeDataType &data, const BT3Node::nodeDataType &value,
                const BT3Mode mode = LEVEL) const;
    bool Mount(binaryTree3 &BTree3, const BT3Node::nodeDataType &data, 
               const BT3Mode modeA = LEVEL, const BT3Mode modeB = LEFT);
    bool unMount(binaryTree3 &BTree3, const BT3Node::nodeDataType &data,
               const BT3Mode modeA = LEVEL, const BT3Mode modeB = LEFT);
    void ShowMountPoints() const;
    bool Remove(const BT3Node::nodeDataType &data, const BT3Mode modeA = LEVEL,
                const BT3Mode modeB = LEFT);
    const std::string& GetLastError() const;

private:
    struct mount_table_node;

    struct mount_point_node
    { 
        const BT3Node *pcValue;
        std::list<mount_table_node> mtable;
    };

    struct mount_table_node
    {
        const BT3Node *pcNode;
        BT3Mode mode;
        std::list<mount_point_node> mount_point_node_list;
    };

    typedef std::list<mount_table_node> mountTableList;
    typedef mountTableList::iterator pMountTableIterator;
    typedef mountTableList::const_iterator pcMountTableIterator;

    mountTableList m_mount_table;
    BT3Node *m_treeTop;
    mutable std::string m_error_msg;
    
    void _create_pre(BT3Node *&pNode, const nodesDataContainer &nodesData,
                     pcContainerIterator &pcIter, const BT3Node::nodeDataType &semaphore);
    bool _validate(const nodesDataContainer &nodesData, pcContainerIterator pcIter,
                   const BT3Node::nodeDataType &semaphore) const;
    void _clear(BT3Node *&pNode);
    size_t _count(const BT3Node *const pcNode) const;
    size_t _depth(const BT3Node *const pcNode) const;
    void _traverse_pre(const BT3Node *const pcNode) const;
    void _traverse_in(const BT3Node *const pcNode) const;
    void _traverse_post(const BT3Node *const pcNode) const;
    void _find_node_pre(BT3Node *&pNode, const BT3Node *const pcNode,
                       const BT3Node::nodeDataType &data) const;
    void _find_node_in(BT3Node *&pNode, const BT3Node *const pcNode,
                       const BT3Node::nodeDataType &data) const;
    void _find_node_post(BT3Node *&pNode, const BT3Node *const pcNode,
                       const BT3Node::nodeDataType &data) const;
    BT3Node* _find_node_level(const BT3Node *const pcNode, 
                       const BT3Node::nodeDataType &data) const;
    bool _mount_table_find(pcMountTableIterator &pcIter, const BT3Node *const pcNode,
                           const BT3Mode mode) const;
    void _cascading_unmount_pre(const BT3Node *const pcNode, binaryTree3 &BTree3, bool &bMsg, bool bCheckOnly);
};

// ==========> inline functions <==========

inline bool binaryTree3::Empty() const
{
    return !m_treeTop;
}

inline bool binaryTree3::Root(BT3Node::nodeDataType &root) const
{
    m_error_msg.clear();

    if(m_treeTop)
    {
        root = m_treeTop->data;
        return true;
    }

    m_error_msg = "Root() error: operation failed: no root element (empty tree?).";
    return false;
}

inline const std::string& binaryTree3::GetLastError() const
{
    return m_error_msg;
}

#endif

