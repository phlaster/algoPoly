#ifndef HUFFTREE_HPP
#define HUFFTREE_HPP

#include "Node.hpp"
#include "FreqTable.hpp"
#include <map>
#include <queue>


using mapFrT = std::map<unsigned char, int>;
using Queue = std::priority_queue<Node*, std::vector<Node*>, bool>;


struct HuffmanTree
{
    Node* root;
    int numLeaves;
    int numNodes;
    int depth;
    HuffmanTree(const FreqTable& freqTable);
    ~HuffmanTree();
    void print();
private:
    void deleteTree(Node* node);
};

#endif