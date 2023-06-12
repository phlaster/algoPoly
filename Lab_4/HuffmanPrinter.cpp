#include "Types.hpp"
#include <iostream>
#include <vector>


class HuffmanPrinter
{
public:
    static void printFreq(const UMapFrT &freqTable)
    {
        std::cout << "Frequency Table: \n";
        for (auto f : freqTable)
        {
            if (f.first == '\n')
            {
                std::cout << "\n"
                          << " - ";
            }
            else
            {
                std::cout << f.first << " - ";
            }
            std::cout << f.second << "\n";
        }
    }

    static void printTree(Node *root)
    {
        if (root == nullptr)
            return;

        if (root->left == nullptr && root->right == nullptr)
        {
            std::cout << "Leaf node: " << root->data << " - " << root->frequency << "\n";
        }
        else
        {
            std::cout << "Internal node: " << root->frequency << "\n";
        }
        printTree(root->left);
        printTree(root->right);
    }

    static void printCodes(const UMapCode &codeMap)
    {
        std::cout << "Huffman Codes:\n";
        for (auto c : codeMap)
        {
            if (c.first == '\n')
                std::cout << "\\n - ";
            else
                std::cout << c.first << " - ";

            std::cout << c.second << "\n";
        }
    }
};