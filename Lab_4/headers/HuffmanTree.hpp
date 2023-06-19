#ifndef HUFFTREE_HPP
#define HUFFTREE_HPP

#include "Node.hpp"
#include "FreqTable.hpp"
#include <queue>


struct HuffmanTree
{
    Node* root;
    int numLeaves;
    int numNodes;
    HuffmanTree(const FreqTable& freqTable);
    ~HuffmanTree();
    void print();
private:
    void deleteTree(Node* node);
};

#endif