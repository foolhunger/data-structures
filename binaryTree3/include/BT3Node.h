#ifndef _BINARYTREE3_NODE_H_
#define _BINARYTREE3_NODE_H_

#include <string>

class BT3Node
{
public:
    BT3Node(): pParent(NULL), plChild(NULL), prChild(NULL){}
    ~BT3Node();

    std::string data;
    BT3Node *pParent;
    BT3Node *plChild;
    BT3Node *prChild;
};

#endif

