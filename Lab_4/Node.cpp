#include "headers/Node.hpp"


Node::Node(unsigned char byte, int frequency, Node* left, Node* right)
{
    this->byte = byte;
    this->frequency = frequency;
    this->left = left;
    this->right = right;
}

bool Node::isLeaf()
{
    // Узел - лист, если оба ребёнка пустые
    return (this->left == nullptr && this->right == nullptr);
}

bool Node::operator>(const Node& other) const
{
    // Перегруженный опрератор сравнения узлов по частотам
    return frequency > other.frequency;
}