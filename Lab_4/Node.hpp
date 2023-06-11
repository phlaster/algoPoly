#ifndef NODE_HPP
#define NODE_HPP

struct Node
{
    char data;
    int frequency;
    Node* left;
    Node* right;

    Node(char data, int frequency, Node* left, Node* right)
    {
        this->data = data;
        this->frequency = frequency;
        this->left = left;
        this->right = right;
    }

    bool operator>(const Node& other) const
    {
        return frequency > other.frequency;
    }
};

#endif