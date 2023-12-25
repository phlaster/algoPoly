#ifndef NODE_HPP
#define NODE_HPP

struct Node
{
    unsigned char byte;
    int frequency;
    Node* left;
    Node* right;

    Node(unsigned char byte, int frequency, Node* left, Node* right);

    bool isLeaf();
    bool operator>(const Node& other) const;
};
#endif