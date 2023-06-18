#include "headers/Node.hpp"


Node::Node(char data, int frequency, Node* left, Node* right)
{
    this->data = data;
    this->frequency = frequency;
    this->left = left;
    this->right = right;
}

bool Node::isLeaf()
{
    return (this->left == nullptr && this->right == nullptr);
}

bool Node::operator>(const Node& other) const
{
    return frequency > other.frequency;
}