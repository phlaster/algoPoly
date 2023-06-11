#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include "Node.hpp"
#include <iomanip>

typedef std::string Str;
typedef std::unordered_map<char, int> UMapFrT;
typedef std::unordered_map<char, Str> UMapCode;


class HuffmanCoding
{
public:
    static void
    compress(const Str &inputFilePath,
             const Str &outputFilePath) {
        
        // Step 1: Read input file
        std::ifstream inputFile(inputFilePath);
        if (!inputFile.is_open()) throw std::invalid_argument("Failed to open input file");

        // Count frequencies of each character in the text
        UMapFrT freqTable;
        char c = inputFile.get();

        while (inputFile.good())
        {
            ++freqTable[c];
            c = inputFile.get();
        }

        if (c != EOF) ++freqTable[c];

        printFreq(freqTable);

        // Step 2: Build Huffman Tree
        Node *root = buildHuffmanTree(freqTable);
        printTree(root); // debug


        // Step 3: Generate bit codes for each symbol
        UMapCode codeMap = generateCodes(root, "");
        printCodes(codeMap);

        // Write compressed data to output file
        inputFile.clear(); // clear fail and eof bits
        inputFile.seekg(0, std ::ios_base ::beg);
        std::ofstream outputFile(outputFilePath, std::ios_base::out | std::ios_base::binary);

        if (!outputFile.is_open()) throw std::invalid_argument("Failed to open output file");

        char symbol = inputFile.get();
        while (inputFile.good())
        {
            const auto &code = codeMap[symbol];
            for (auto c : code)
            {
                bitBuffer += Str(1, c);
                if (bitBuffer.size() == 8) writeByte(outputFile);
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

    static void
    decompress(const Str &inputFilePath,
               const Str &outputFilePath){
        int numOfSymbols;
        unsigned char header[256];
        std::ifstream inputFile(inputFilePath, std::ios_base::in | std::ios_base::binary);

        if (!inputFile.is_open()) throw std::invalid_argument("Failed to open input file");

        unsigned char c;
        for (int i = 0; i <= 255 && !inputFile.eof(); ++i)
        {
            inputFile.read(reinterpret_cast<char *>(&c), sizeof(c));
            header[i] = c;
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

        if (!outputFile.is_open()) throw std::invalid_argument("Failed to open output file");


        for(int i=0; i<10; i++)
        {
            unsigned char x; 
            inputFile.read(reinterpret_cast<char*>(&x),sizeof(x));
            std::cout << x <<"\n";
        }


        Node *current = root;

        while (!inputFile.eof() && numOfSymbols > 0)
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

        inputFile.close();
        outputFile.close();
    }

private:
    static Str bitBuffer;

    static Node *
    buildHuffmanTree(const std ::unordered_map<char, int> &freqTable) {

        auto compare = [](const Node *lhs, const Node *rhs)
        {
            return *lhs > *rhs;
        };

        std::priority_queue<Node *, std::vector<Node *>, decltype(compare)>
            minHeap(compare);

        for (auto f : freqTable)
        {
            std::cout << f.first << " - " << f.second << "\n"; // debug
            Node *temp = new Node{f.first, f.second, nullptr, nullptr};
            minHeap.push(temp);
        }

        while (minHeap.size() > 1)
        {
            auto left = minHeap.top();
            minHeap.pop();
            auto right = minHeap.top();
            minHeap.pop();

            int sumFreq = left->frequency + right->frequency;

            Node *parent = new Node{'\0', sumFreq, left, right};
            minHeap.push(parent);
        }
        return minHeap.top();
    }

    static UMapCode
    generateCodes(Node *root, const Str &code) {
        UMapCode result;

        if (root->left != nullptr)
            generateCodes(root->left, code + "0");
        if (root->right != nullptr)
            generateCodes(root->right, code + "1");
        if (root->data != '\0')
            result[root->data] = code;

        return result;
    }

    static void
    writeByte(std::ofstream &outputFile) {
        unsigned char byte = 0;
        for (int i = 7; i >= 0; --i) // writing bits from the buffer as bytes
        {
            bool bit = bitBuffer[i] - '0';
            byte |= bit << i;
        }

        outputFile.write(reinterpret_cast<const char *>(&byte), sizeof(byte));
        bitBuffer.clear();
    }

    static void
    printTree(Node* root, int indent = 0){
        if (root != nullptr)
        {
            printTree(root->right, indent + 4);
            std::cout << std::setw(indent) << ' ';
            std::cout << root->data << ":" << root->frequency << std::endl;
            printTree(root->left, indent + 4);
        }
    }

    static void
    printCodes(UMapCode codeMap) {
        std::cout<<"Printing Codes"<< "\n";
        for(auto i : codeMap)
            std::cout <<
            i.first <<
            "\t" <<
            i.second <<
            "\n";
    }
    
    static void
    printFreq(UMapFrT freqTable) {
        for(auto it : freqTable)
            std::cout <<
            "Symbol: " <<
            it.first <<
            ", Frequency: " <<
            it.second <<
            std::endl;
    }

};