#ifndef HUFFTREE_HPP
#define HUFFTREE_HPP

#include "Node.hpp"
#include <map>

using mapFrT = std::map<char, int>;


struct HuffmanTree
{
    Node* tree;
    HuffmanTree(const mapFrT& freqTable);
    ~HuffmanTree();
    void deleteTree(Node* node);
};

#endif