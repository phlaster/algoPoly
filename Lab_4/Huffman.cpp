#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <bitset>
#include "Types.hpp"
#include "HuffmanPrinter.cpp"
#include <iomanip>

class HuffmanCoding
{
private:
    friend HuffmanPrinter;
    static Str bitBuffer;

    static Node *buildHuffmanTree(const std ::unordered_map<char, int> &freqTable)
    {

        auto compare = [](const Node *lhs, const Node *rhs)
        {
            return *lhs > *rhs;
        };

        std::priority_queue<Node *, std::vector<Node *>, decltype(compare)>
            minHeap(compare);

        for (auto f : freqTable)
        {
            // std::cout << f.first << " - " << f.second << "\n"; // debug
            Node *temp = new Node{f.first, f.second, nullptr, nullptr};
            minHeap.push(temp);
        }

        while (minHeap.size() > 1)
        {
            Node *left = minHeap.top();
            minHeap.pop();

            Node *right = minHeap.top();
            minHeap.pop();

            int freqSum = left->frequency + right->frequency;

            Node *parentNode = new Node{'\0', freqSum, left, right};

            minHeap.push(parentNode);
        }

        Node *root = minHeap.top();
        minHeap.pop();

        return root;
    }

    static UMapCode generateCodes(Node *root, Str code)
    {
        UMapCode codeMap;

        if (root == nullptr)
        {
            return codeMap;
        }

        if (root->left == nullptr && root->right == nullptr)
        {
            codeMap[root->data] = code;
            return codeMap;
        }

        UMapCode leftMap = generateCodes(root->left, code + "0");
        UMapCode rightMap = generateCodes(root->right, code + "1");

        codeMap.insert(leftMap.begin(), leftMap.end());
        codeMap.insert(rightMap.begin(), rightMap.end());

        return codeMap;
    }

    static void writeByte(std::ofstream &outputFile)
    {
        unsigned char byte = std::bitset<8>(bitBuffer).to_ulong();
        outputFile.put(byte);
        bitBuffer.clear();
    }

    static void writeSingleCharacterFile(Node *root, const Str &outputFilePath)
    {
        std::ofstream outputFile(outputFilePath, std::ios_base::out | std::ios_base::binary);
        if (!outputFile.is_open())
            throw std::invalid_argument("Failed to open output file");

        unsigned char byte = (unsigned char)root->data;
        outputFile.write(reinterpret_cast<char *>(&byte), sizeof(byte));

        outputFile.close();
    }
    
public:
    static void compress(const Str &inputFilePath, const Str &outputFilePath)
    {
        // Step 1: Read input file
        std::ifstream inputFile(inputFilePath);
        if (!inputFile.is_open())
            throw std::invalid_argument("Failed to open input file");

        // Count frequencies of each character in the text
        UMapFrT freqTable;
        char c = inputFile.get();

        while (inputFile.good())
        {
            ++freqTable[c];
            c = inputFile.get();
        }

        if (c != EOF)
            ++freqTable[c];

        HuffmanPrinter::printFreq(freqTable);

        // Step 2: Build Huffman Tree
        Node *root = buildHuffmanTree(freqTable);
        HuffmanPrinter::printTree(root); // debug

        if (root->left == nullptr && root->right == nullptr)
        {
            // Single character input file
            writeSingleCharacterFile(root, outputFilePath);
            inputFile.close();
            return;
        }

        // Step 3: Generate bit codes for each symbol
        UMapCode codeMap = generateCodes(root, "");
        HuffmanPrinter::printCodes(codeMap);

        // Write compressed data to output file
        inputFile.clear(); // clear fail and eof bits
        inputFile.seekg(0, std::ios_base::beg);
        std::ofstream outputFile(outputFilePath, std::ios_base::out | std::ios_base::binary);

        if (!outputFile.is_open())
            throw std::invalid_argument("Failed to open output file");

        char symbol = inputFile.get();
        while (inputFile.good())
        {
            const auto &code = codeMap[symbol];
            for (auto c : code)
            {
                bitBuffer += Str(1, c);
                if (bitBuffer.size() == 8)
                    writeByte(outputFile);
            }
            symbol = inputFile.get();
        }

        // Write any remaining bits to output file
        if (bitBuffer.size() > 0)
        {
            while (bitBuffer.size() < 8)
            {
                bitBuffer.push_back('0');
            }
            writeByte(outputFile);
        }

        inputFile.close();
        outputFile.close();
    }

    static void decompress(const Str &inputFilePath, const Str &outputFilePath)
    {
        int numOfSymbols;
        unsigned char header[256];
        std::ifstream inputFile(inputFilePath, std::ios_base::in | std::ios_base::binary);
        if (!inputFile.is_open())
            throw std::invalid_argument("Failed to open input file");

        unsigned char c;
        for (int i = 0; i <= 255 && !inputFile.eof(); ++i)
        {
            inputFile.read(reinterpret_cast<char *>(&c), sizeof(c));
            header[i] = c;
            std::cout << c << "\n";
        }

        numOfSymbols = header[255];
        UMapFrT freqTable;
        for (int i = 0; i < 255; ++i)
        {
            if (header[i] != 0)
            {
                freqTable[i] = header[i];
            }
        }

        Node *root = buildHuffmanTree(freqTable);
        std::ofstream outputFile(outputFilePath);

        if (!outputFile.is_open())
            throw std::invalid_argument("Failed to open output file");

        for (int i = 0; i < 10; i++)
        {
            unsigned char x;
            inputFile.read(reinterpret_cast<char *>(&x), sizeof(x));
            std::cout << x << "\n";
        }

        Node *current = root;

        while (numOfSymbols > 0)
        {
            unsigned char byte;
            inputFile.read(reinterpret_cast<char *>(&byte), sizeof(byte));

            for (int i = 7; i >= 0; --i)
            {
                bool bit = (byte >> i) & 1;

                if (bit == false)
                {
                    current = current->left;
                    if (current->data != '\0') // Found a symbol
                    {
                        outputFile << current->data;
                        current = root;
                        --numOfSymbols;
                    }
                }
                else
                {
                    current = current->right;
                    if (current->data != '\0') // Found a symbol
                    {
                        outputFile << current->data;
                        current = root;
                        --numOfSymbols;
                    }
                }
            }
        }

        if (numOfSymbols != 0)
        {
            throw std::invalid_argument("Output file is incomplete.");
        }
    }
};