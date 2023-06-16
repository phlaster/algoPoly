#include "Printer.hpp"
#include <iostream>


void Printer::printFreq(const mapFrT &freqTable)
{
    std::cout << "Frequency Table: \n";
    for (auto f : freqTable)
    {
        if (f.first == '\n')
            std::cout << "\\n - ";
        if (f.first == '\t')
            std::cout << "\\t - ";
        if (f.first == '\r')
            std::cout << "\\r - ";
        if (f.first == '\b')
            std::cout << "\\b - ";
        if (f.first == '\e')
            std::cout << "\\e - ";
        if (f.first == '\0')
            std::cout << "\\0 - ";
        else
            std::cout << f.first << " - ";
        std::cout << f.second << "\n";
    }
}

void Printer::printTree(Node *root)
{
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr){
        std::cout << "Leaf node: " <<
        root->data << " - " <<
        root->frequency << "\n";
    }
    else
        std::cout << "Internal node: " << root->frequency << "\n";
    printTree(root->left);
    printTree(root->right);
}

void Printer::printCodes(const mapCode &codeMap)
{
    std::cout << "Huffman Codes:\n";
    for (auto c : codeMap)
    {
        if (c.first == '\n')
            std::cout << "\\n - ";
        if (c.first == '\t')
            std::cout << "\\t - ";
        if (c.first == '\b')
            std::cout << "\\b - ";
        if (c.first == '\r')
            std::cout << "\\r - ";
        if (c.first == '\0')
            std::cout << "\\0 - ";
        if (c.first == '\e')
            std::cout << "\\e - ";
        else
            std::cout << c.first << " - ";
        std::cout << c.second << "\n";
    }
}