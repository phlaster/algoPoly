#ifndef NODECOLOR_HPP
#define NODECOLOR_HPP
enum nodeColor {
    BLACK,
    RED
};
#endif


#ifndef NODE_HPP
#define NODE_HPP
struct Node {
    int data;
    Node *parent;
    Node *left;
    Node *right;
    int color;
};
#endif


#ifndef NODEPTR_HPP
#define NODEPTR_HPP
typedef Node *NodePtr;
#endif


#ifndef TREE_HPP
#define TREE_HPP
class Tree {
protected:
    NodePtr root;
    NodePtr ENDNULL;
};
#endif
