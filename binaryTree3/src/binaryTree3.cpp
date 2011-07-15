#include "../include/binaryTree3.h"
#include <iostream>
#include <csetjmp>
#include <cstdlib>
#include <iterator>
#include <queue>

jmp_buf envBuffer;

bool binaryTree3::Create(const nodesDataContainer &nodesData, const BT3Node::nodeDataType &semaphore)
{
    m_error_msg.clear();

    if(m_treeTop)
    {
        m_error_msg = "Create() error: operation denied: tree already created (call Clear() first?).";
        return false;
    }

    pcContainerIterator pcIter(nodesData.begin());

    _create_pre(m_treeTop, nodesData, pcIter, semaphore);

    if(!_validate(nodesData, pcIter, semaphore))
    {
        m_error_msg = "Create() error: operation failed: tree definition error.";
        _clear(m_treeTop);
        m_treeTop = NULL;
        return false;
    }
    return true;
}

void binaryTree3::_create_pre(BT3Node *&pNode, const nodesDataContainer &nodesData,
                              pcContainerIterator &pcIter, const BT3Node::nodeDataType &semaphore)
{
    if(pcIter != nodesData.end() && *pcIter != semaphore)
    {
        if(!(pNode = new(BT3Node)))
        {
            std::cerr << "Create() error: internal error (fatal): memory error occurred." << std::endl;
            exit(EXIT_FAILURE);
        }
        pNode->data = *pcIter;
        pNode->pParent = pNode->plChild = pNode->prChild = NULL;
        if(pcIter != nodesData.end())
        {
            _create_pre(pNode->plChild, nodesData, ++pcIter, semaphore);
        }
        if(pcIter != nodesData.end())
        {
            _create_pre(pNode->prChild, nodesData, ++pcIter, semaphore);
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

bool binaryTree3::_validate(const nodesDataContainer &nodesData, pcContainerIterator pcIter,
                            const BT3Node::nodeDataType &semaphore) const
{
    if(pcIter == nodesData.end())
        return true;
    for(++pcIter; pcIter != nodesData.end(); ++pcIter)
    {
        if(*pcIter != semaphore)
            return false;
    }
    return true;
}

bool binaryTree3::Clear()
{
    m_error_msg.clear();

    if(!m_mount_table.empty())
    {
        m_error_msg = "Clear() error: operation denied: mount point(s) detected (unmount first?).";
        return false;
    }
    _clear(m_treeTop);
    m_treeTop = NULL;
    return true;
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

size_t binaryTree3::_count(const BT3Node *const pcNode) const
{
    if(!pcNode)
    {
        return 0;
    }

    size_t lCount = _count(pcNode->plChild);
    size_t rCount = _count(pcNode->prChild);

    return lCount + rCount + 1;
}

size_t binaryTree3::Depth() const
{
    return _depth(m_treeTop);
}

size_t binaryTree3::_depth(const BT3Node *const pcNode) const
{
    if(!pcNode)
    {
        return 0;
    }

    size_t lDepth = _depth(pcNode->plChild);
    size_t rDepth = _depth(pcNode->prChild);

    return ((lDepth >= rDepth) ? lDepth + 1 : rDepth + 1);
}

void binaryTree3::preOrderTraverse() const
{
    _traverse_pre(m_treeTop);
}

void binaryTree3::_traverse_pre(const BT3Node *const pcNode) const
{
    if(!pcNode)
    {
        return ;
    }
    std::cout << pcNode->data << " ";
    _traverse_pre(pcNode->plChild);
    _traverse_pre(pcNode->prChild);
}

void binaryTree3::inOrderTraverse() const
{
    _traverse_in(m_treeTop);
}

void binaryTree3::_traverse_in(const BT3Node *const pcNode) const
{
    if(!pcNode)
    {
        return ;
    }
    _traverse_in(pcNode->plChild);
    std::cout << pcNode->data << " ";
    _traverse_in(pcNode->prChild);
}

void binaryTree3::postOrderTraverse() const
{
    _traverse_post(m_treeTop);
}

void binaryTree3::_traverse_post(const BT3Node *const pcNode) const
{
    if(!pcNode)
    {
        return ;
    }
    _traverse_post(pcNode->plChild);
    _traverse_post(pcNode->prChild);
    std::cout << pcNode->data << " ";
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
        size_t nodesCount = queue.size();
        for(size_t index = 0; index < nodesCount; ++index)
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

BT3Node* binaryTree3::_find_node_level(const BT3Node *const pcNode, 
                                       const BT3Node::nodeDataType &data) const
{
    if(!pcNode)
    {
        return NULL;
    }
    std::queue<const BT3Node*> queue;
    queue.push(pcNode);
    while(!queue.empty())
    {
        if(queue.front()->data == data)
        {
            return (BT3Node *)queue.front();
        }
        if(queue.front()->plChild)
        {
            queue.push(queue.front()->plChild);
        }
        if(queue.front()->prChild)
        {
            queue.push(queue.front()->prChild);
        }
        queue.pop();
    }
    return NULL;
}

void binaryTree3::_find_node_pre(BT3Node *&pNode, const BT3Node *const pcNode, 
                                 const BT3Node::nodeDataType &data) const
{
    if(!pcNode)
    {
        return ;
    }
    if(pcNode->data == data)
    {
        pNode = (BT3Node *)pcNode;
        longjmp(envBuffer, 1);
    }
    _find_node_pre(pNode, pcNode->plChild, data);
    _find_node_pre(pNode, pcNode->prChild, data);
}

void binaryTree3::_find_node_in(BT3Node *&pNode, const BT3Node *const pcNode,
                                const BT3Node::nodeDataType &data) const
{
    if(!pcNode)
    {
        return ;
    }
    _find_node_in(pNode, pcNode->plChild, data);
    if(pcNode->data == data)
    {
        pNode = (BT3Node *)pcNode;
        longjmp(envBuffer, 1);
    }
    _find_node_in(pNode, pcNode->prChild, data);
}

void binaryTree3::_find_node_post(BT3Node *&pNode, const BT3Node *const pcNode,
                                  const BT3Node::nodeDataType &data) const
{
    if(!pcNode)
    {
        return ;
    }
    _find_node_post(pNode, pcNode->plChild, data);
    _find_node_post(pNode, pcNode->prChild, data);
    if(pcNode->data == data)
    {
        pNode = (BT3Node *)pcNode;
        longjmp(envBuffer, 1);
    }
}

bool binaryTree3::lChild(BT3Node::nodeDataType &lchild, const BT3Node::nodeDataType &data, 
                         const BT3Mode mode) const
{
    m_error_msg.clear();

    BT3Node *pNode = NULL;
    if(mode == LEVEL)
    {
        pNode = _find_node_level(m_treeTop, data);
        if(!pNode || !pNode->plChild)
        {
            m_error_msg = "lChild() error: operation failed: node does not exist or no left child.";
            return false;
        }
        lchild = pNode->plChild->data;
        return true;
    }
    else
    {
        int retCode = setjmp(envBuffer);
        if(retCode == 0 && mode == PRE)
        {
            _find_node_pre(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == IN)
        {
            _find_node_in(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == POST)
        {
            _find_node_post(pNode, m_treeTop, data);
        }
        if(retCode == 1 && pNode->plChild)
        {
            lchild = pNode->plChild->data;
            return true;
        }
        m_error_msg = "lChild() error: operation failed: node does not exist or no left child.";
        return false;
    }
}

bool binaryTree3::rChild(BT3Node::nodeDataType &rchild, const BT3Node::nodeDataType &data,
                         const BT3Mode mode) const
{
    m_error_msg.clear();

    BT3Node *pNode = NULL;
    if(mode == LEVEL)
    {
        pNode = _find_node_level(m_treeTop, data);
        if(!pNode || !pNode->prChild)
        {
            m_error_msg = "rChild() error: operation failed: node does not exist or no right child.";
            return false;
        }
        rchild = pNode->prChild->data;
        return true;
    }
    else
    {
        int retCode = setjmp(envBuffer);
        if(retCode == 0 && mode == PRE)
        {
            _find_node_pre(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == IN)
        {
            _find_node_in(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == POST)
        {
            _find_node_post(pNode, m_treeTop, data);
        }
        if(retCode == 1 && pNode->prChild)
        {
            rchild = pNode->prChild->data;
            return true;
        }
        m_error_msg = "rChild() error: operation failed: node does not exist or no right child.";
        return false;
    }
}

bool binaryTree3::lSibling(BT3Node::nodeDataType &lsibling, const BT3Node::nodeDataType &data,
                           const BT3Mode mode) const
{
    m_error_msg.clear();

    BT3Node *pNode = NULL;
    if(mode == LEVEL)
    {
        pNode = _find_node_level(m_treeTop, data);
        if(!pNode || !pNode->pParent || !pNode->pParent->plChild || (pNode->pParent->plChild == pNode))
        {
            m_error_msg = "lSibling() error: operation failed: node does not exist or no left sibling.";
            return false;
        }
        lsibling = pNode->pParent->plChild->data;
        return true;
    }
    else
    {
        int retCode = setjmp(envBuffer);
        if(retCode == 0 && mode == PRE)
        {
            _find_node_pre(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == IN)
        {
            _find_node_in(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == POST)
        {
            _find_node_post(pNode, m_treeTop, data);
        }
        if(retCode == 1 && pNode->pParent && pNode->pParent->plChild && (pNode->pParent->plChild != pNode))
        {
            lsibling = pNode->pParent->plChild->data;
            return true;
        }
        m_error_msg = "lSibling() error: operation failed: node does not exist or no left sibling.";
        return false;
    }
}

bool binaryTree3::rSibling(BT3Node::nodeDataType &rsibling, const BT3Node::nodeDataType &data,
                           const BT3Mode mode) const
{
    m_error_msg.clear();

    BT3Node *pNode = NULL;
    if(mode == LEVEL)
    {
        pNode = _find_node_level(m_treeTop, data);
        if(!pNode || !pNode->pParent || !pNode->pParent->prChild || (pNode->pParent->prChild == pNode))
        {
            m_error_msg = "rSibling() error: operation failed: node does not exist or no right sibling.";
            return false;
        }
        rsibling = pNode->pParent->prChild->data;
        return true;
    }
    else
    {
        int retCode = setjmp(envBuffer);
        if(retCode == 0 && mode == PRE)
        {
            _find_node_pre(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == IN)
        {
            _find_node_in(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == POST)
        {
            _find_node_post(pNode, m_treeTop, data);
        }
        if(retCode == 1 && pNode->pParent && pNode->pParent->prChild && (pNode->pParent->prChild != pNode))
        {
            rsibling = pNode->pParent->prChild->data;
            return true;
        }
        m_error_msg = "rSibling() error: operation failed: node does not exist or no right sibling.";
        return false;
    }
}

bool binaryTree3::Parent(BT3Node::nodeDataType &parent, const BT3Node::nodeDataType &data,
                         const BT3Mode mode) const
{
    m_error_msg.clear();

    BT3Node *pNode = NULL;
    if(mode == LEVEL)
    {
        pNode = _find_node_level(m_treeTop, data);
        if(!pNode || pNode == m_treeTop || !pNode->pParent)
        {
            m_error_msg = "Parent() error: operation failed: node does not exist or no parent.";
            return false;
        }
        parent = pNode->pParent->data;
        return true;
    }
    else
    {
        int retCode = setjmp(envBuffer);
        if(retCode == 0 && mode == PRE)
        {
            _find_node_pre(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == IN)
        {
            _find_node_in(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == POST)
        {
            _find_node_post(pNode, m_treeTop, data);
        }
        if(retCode == 1 && pNode != m_treeTop && pNode->pParent)
        {
            parent = pNode->pParent->data;
            return true;
        }
        m_error_msg = "Parent() error: operation failed: node does not exist or no parent.";
        return false;
    }
}

bool binaryTree3::Assign(const BT3Node::nodeDataType &data, const BT3Node::nodeDataType &value,
                         const BT3Mode mode) const
{
    m_error_msg.clear();

    BT3Node *pNode = NULL;
    if(mode == LEVEL)
    {
        pNode = _find_node_level(m_treeTop, data);
        if(!pNode)
        {
            m_error_msg = "Assign() error: operation failed: node does not exist.";
            return false;
        }
        pNode->data = value;
        return true;
    }
    else
    {
        int retCode = setjmp(envBuffer);
        if(retCode == 0 && mode == PRE)
        {
            _find_node_pre(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == IN)
        {
            _find_node_in(pNode, m_treeTop, data);
        }
        if(retCode == 0 && mode == POST)
        {
            _find_node_post(pNode, m_treeTop, data);
        }
        if(retCode == 1)
        {
            pNode->data = value;
            return true;
        }
        m_error_msg = "Assign() error: operation failed: node does not exist.";
        return false;
    }
}

bool binaryTree3::_mount_table_find(pcMountTableIterator &pcIter, const BT3Node *const pcNode,
                                    const BT3Mode mode) const
{
    pcIter = m_mount_table.begin();
    for(; pcIter != m_mount_table.end(); ++pcIter)
    {
        if(pcIter->pcNode == pcNode && pcIter->mode == mode)
        {
            return true;
        }
    }
    return false;
}

bool binaryTree3::Mount(binaryTree3 &BTree3, const BT3Node::nodeDataType &data,
                        const BT3Mode modeA, const BT3Mode modeB)
{
    m_error_msg.clear();

    BT3Node *pNode = NULL;
    if(modeA == LEVEL)
    {
        pNode = _find_node_level(m_treeTop, data);
    }
    else
    {
        int retCode = setjmp(envBuffer);
        if(retCode == 0 && modeA == PRE)
        {
            _find_node_pre(pNode, m_treeTop, data);
        }
        if(retCode == 0 && modeA == IN)
        {
            _find_node_in(pNode, m_treeTop, data);
        }
        if(retCode == 0 && modeA == POST)
        {
            _find_node_post(pNode, m_treeTop, data);
        }
    }

    if(!pNode)
    {
        m_error_msg = "Mount() error: operation failed: mount point does not exist.";
        return false;
    }

    pcMountTableIterator pcIter;
    if(_mount_table_find(pcIter, pNode, modeB))
    {
        mount_point_node mpNode;
        if(modeB == LEFT)
        {
            mpNode.pcValue = pNode->plChild;
            pNode->plChild = BTree3.m_treeTop;
            if(pNode->plChild)
            {
                pNode->plChild->pParent = pNode;
            }
        }
        if(modeB == RIGHT)
        {
            mpNode.pcValue = pNode->prChild;
            pNode->prChild = BTree3.m_treeTop;
            if(pNode->prChild)
            {
                pNode->prChild->pParent = pNode;
            }
        }
        mpNode.mtable = BTree3.m_mount_table;
        
        pMountTableIterator pIter(m_mount_table.begin());
        std::advance(pIter, std::distance<pcMountTableIterator>(pIter, pcIter));
        pIter->mount_point_node_list.push_front(mpNode);
    }
    else
    {
        mount_table_node mtNode;
        mount_point_node mpNode;
        mtNode.pcNode = pNode;
        mtNode.mode = modeB;
        if(modeB == LEFT)
        {
            mpNode.pcValue = pNode->plChild;
            pNode->plChild = BTree3.m_treeTop;
            if(pNode->plChild)
            {
                pNode->plChild->pParent = pNode;
            }
        }
        if(modeB == RIGHT)
        {
            mpNode.pcValue = pNode->prChild;
            pNode->prChild = BTree3.m_treeTop;
            if(pNode->prChild)
            {
                pNode->prChild->pParent = pNode;
            }
        }
        mpNode.mtable = BTree3.m_mount_table;
        mtNode.mount_point_node_list.push_front(mpNode);
        m_mount_table.push_back(mtNode);
    }

    BTree3.m_treeTop = NULL;
    BTree3.m_mount_table.clear();
    return true;
}

void binaryTree3::_cascading_unmount_pre(const BT3Node *const pcNode, binaryTree3 &BTree3, bool &bMsg, bool bCheckOnly)
{
    if(!pcNode)
    {
        return ;
    }

    pcMountTableIterator pcIter(m_mount_table.begin());
    while(pcIter != m_mount_table.end())
    {
        if(pcIter->pcNode == pcNode)
        {
            if(bCheckOnly)
            {
                longjmp(envBuffer, 1);
            }

            if(bMsg)
            {
                std::cout << "\ndownward mount point(s) detected, continue anyway?\n(C)ontinue, (A)bort: ";
                std::string choice;
                while(std::cin >> choice)
                {
                    if(choice == "C" || choice == "c")
                    {
                        bMsg = false;
                        break;
                    }
                    if(choice == "A" || choice == "a")
                    {
                        longjmp(envBuffer, 2);
                    }
                    std::cout << "\n(C)ontinue, (A)bort: ";
                }
            }
            BTree3.m_mount_table.push_back(*pcIter);
            pMountTableIterator pIter(m_mount_table.begin());
            std::advance(pIter, std::distance<pcMountTableIterator>(pIter, pcIter));
            ++pcIter;
            m_mount_table.erase(pIter);
        }
        else
        {
            ++pcIter;
        }
    }
    _cascading_unmount_pre(pcNode->plChild, BTree3, bMsg, bCheckOnly);
    _cascading_unmount_pre(pcNode->prChild, BTree3, bMsg, bCheckOnly);
}

bool binaryTree3::unMount(binaryTree3 &BTree3, const BT3Node::nodeDataType &data,
                          const BT3Mode modeA, const BT3Mode modeB)
{
    m_error_msg.clear();

    if(BTree3.m_treeTop)
    {
        m_error_msg = "unMount() error: operation denied: unmount tree is busy.(clear the unmount tree first?)";
        return false;
    }

    BT3Node *pNode = NULL;
    if(modeA == LEVEL)
    {
        pNode = _find_node_level(m_treeTop, data);
    }
    else
    {
        int retCode = setjmp(envBuffer);
        if(retCode == 0 && modeA == PRE)
        {
            _find_node_pre(pNode, m_treeTop, data);
        }
        if(retCode == 0 && modeA == IN)
        {
            _find_node_in(pNode, m_treeTop, data);
        }
        if(retCode == 0 && modeA == POST)
        {
            _find_node_post(pNode, m_treeTop, data);
        }
    }

    if(!pNode)
    {
        m_error_msg = "unMount() error: operation failed: unmount point does not exist.";
        return false;
    }

    pcMountTableIterator pcIter;
    if(!_mount_table_find(pcIter, pNode, modeB))
    {
        m_error_msg = "unMount() error: operation denied: NOT a mount point.";
        return false;
    }

    BTree3.m_mount_table = pcIter->mount_point_node_list.front().mtable;
    int retCode = setjmp(envBuffer);
    bool bMsg = true;
    if(retCode == 0 && modeB == LEFT)
    {
        _cascading_unmount_pre(pNode->plChild, BTree3, bMsg, false);
    }
    if(retCode == 0 && modeB == RIGHT)
    {
        _cascading_unmount_pre(pNode->prChild, BTree3, bMsg, false);
    }
    if(retCode == 2)
    {
        BTree3.m_mount_table.clear();
        return true;
    }

    pMountTableIterator pIter(m_mount_table.begin());
    std::advance(pIter, std::distance<pcMountTableIterator>(pIter, pcIter));
    if(modeB == LEFT)
    {
        BTree3.m_treeTop = pNode->plChild;
        if(BTree3.m_treeTop)
        {
            BTree3.m_treeTop->pParent = NULL;
        }
        pNode->plChild = (BT3Node *)(pcIter->mount_point_node_list.front().pcValue);
        if(pNode->plChild)
        {
            pNode->plChild->pParent = pNode;
        }
    }
    if(modeB == RIGHT)
    {
        BTree3.m_treeTop = pNode->prChild;
        if(BTree3.m_treeTop)
        {
            BTree3.m_treeTop->pParent = NULL;
        }
        pNode->prChild = (BT3Node *)(pcIter->mount_point_node_list.front().pcValue);
        if(pNode->prChild)
        {
            pNode->prChild->pParent = pNode;
        }
    }
    pIter->mount_point_node_list.pop_front();
    if(pIter->mount_point_node_list.empty())
    {
        m_mount_table.erase(pIter);
    }
    return true;
}

void binaryTree3::ShowMountPoints() const
{
    std::cout << "\n===============> Mount Point(s) <=============" << std::endl;
    pcMountTableIterator pcIter(m_mount_table.begin());
    for( ; pcIter != m_mount_table.end(); ++pcIter)
    {
        std::cout << " # mount point: " << pcIter->pcNode->data << " : ";
        if(pcIter->mode == LEFT)
            std::cout << "Left : ";
        if(pcIter->mode == RIGHT)
            std::cout << "Right : ";
        std::cout << pcIter->mount_point_node_list.size() << std::endl;
    }
    std::cout << "===================== END ====================" << std::endl;
}

bool binaryTree3::Remove(const BT3Node::nodeDataType &data, const BT3Mode modeA, const BT3Mode modeB)
{
    m_error_msg.clear();

    BT3Node *pNode = NULL;
    if(modeA == LEVEL)
    {
        pNode = _find_node_level(m_treeTop, data);
    }
    else
    {
        int retCode = setjmp(envBuffer);
        if(retCode == 0 && modeA == PRE)
        {
            _find_node_pre(pNode, m_treeTop, data);
        }
        if(retCode == 0 && modeA == IN)
        {
            _find_node_in(pNode, m_treeTop, data);
        }
        if(retCode == 0 && modeA == POST)
        {
            _find_node_post(pNode, m_treeTop, data);
        }
    }

    if(!pNode)
    {
        m_error_msg = "Remove() error: operation failed: node does not exist.";
        return false;
    }

    pcMountTableIterator pcIter;
    if(_mount_table_find(pcIter, pNode, modeB))
    {
        m_error_msg = "Remove() error: operation denied: attempt to remove mount point rejected.";
        return false;
    }

    BT3Node *pNodeTmp = pNode;
    while(pNodeTmp->pParent)
    {
        if((pNodeTmp->pParent->plChild == pNodeTmp && _mount_table_find(pcIter, pNodeTmp->pParent, LEFT))
           || (pNodeTmp->pParent->prChild == pNodeTmp && _mount_table_find(pcIter, pNodeTmp->pParent, RIGHT)))
        {
            m_error_msg = "Remove() error: operation denied: upward mount point(s) detected.";
            return false;
        }
        pNodeTmp = pNodeTmp->pParent;
    }

    int retCode = setjmp(envBuffer);
    if(retCode == 0)
    {
        binaryTree3 TreeTmp;
        bool bMsg = false;
        if(modeB == LEFT)
        {
            _cascading_unmount_pre(pNode->plChild, TreeTmp, bMsg, true);
        }
        if(modeB == RIGHT)
        {
            _cascading_unmount_pre(pNode->prChild, TreeTmp, bMsg, true);
        }
    }
    if(retCode == 1)
    {
        m_error_msg = "Remove() error: operation denied: downward mount point(s) detected (unmount first?).";
        return false;
    }

    if(modeB == LEFT)
    {
        _clear(pNode->plChild);
        pNode->plChild = NULL;
    }
    if(modeB == RIGHT)
    {
        _clear(pNode->prChild);
        pNode->prChild = NULL;
    }
    return true;
}

binaryTree3::~binaryTree3()
{
    _clear(m_treeTop);
    m_treeTop = NULL;
}

