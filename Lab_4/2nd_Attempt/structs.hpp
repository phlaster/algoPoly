#include <vector>


#ifndef NODE_HPP
#define NODE_HPP
struct Node
{
    int value;
    int priority;
    int degree;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    bool marked;
};
#endif

#ifndef FHEAP_HPP
#define FHEAP_HPP
struct FibonacciHeap
{
    Node* min;
    int count;
    std::vector<Node*> roots;
    int maxDegree;
};
#endif