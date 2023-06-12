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
    
    static UMapFrT buildFrequencyTable(std::ifstream& inputStream)
    {
        UMapFrT freqTable;

        // Iterate through all characters in input stream and count their frequencies
        char c;
        while (inputStream.get(c)) {
            ++freqTable[c];
        }

        return freqTable;
    }

    static Node* buildHuffmanTree(const std::unordered_map<char, int>& freqTable)
    {
        auto compare = [](const Node *lhs, const Node *rhs)
        {
            return *lhs > *rhs;
        };


        // Create priority queue of single-node trees ordered by increasing frequency 
        std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> pq(compare) ;
        for (const auto& pair : freqTable) {
            pq.push(new Node(pair.first, pair.second, nullptr, nullptr));
        }

        // Combine smallest trees into larger ones until there is only one remaining - this will be our root node.
        while (pq.size() > 1) {
            Node *left = pq.top();
            pq.pop();
            
            Node *right = pq.top();
            pq.pop();
            
            int combinedFreq = left->frequency + right->frequency; 
            Node *parent = new Node('\0', combinedFreq, nullptr, nullptr);
            
            parent->left = left;
            parent->right = right;

            pq.push(parent);	
        }
    
        return pq.top(); 
    }

    static void buildCodeMap(Node *node, const Str& prefix,
	std::unordered_map<char, Str>& codeMap)
    {
        if (node->isLeaf())
        {
            codeMap[node->data] = prefix;
        } else
        {
            buildCodeMap(node->left, prefix + "0", codeMap);
            buildCodeMap(node->right, prefix + "1", codeMap);
        }
    }

    static void writeHeader(std::ofstream &outputStream, const UMapFrT &freqTable)
    {
        // Write size of frequency table first
        int freqTableSize = static_cast<int>(freqTable.size());
        outputStream.write(reinterpret_cast<const char *>(&freqTableSize), sizeof(freqTableSize));
        
        // Write out each pair in turn - first character then integer count.
        for (const auto &pair : freqTable) {
            outputStream.put(pair.first);
            outputStream.write(reinterpret_cast<const char *>(&pair.second), sizeof(pair.second));
        }
    }

    static int encodeData(std::ifstream& inputStream,
               std::ofstream& outputStream,
               const UMapCode& codeMap)
    {
        int numEncodedBits = 0;
        unsigned char buffer = 0;
        int bufferSize = 0;

        char c;
        while (inputStream.get(c)) {
            const Str& code = codeMap.at(c);
            for (int i = 0; i < static_cast<int>(code.size()); ++i) {
                if (code[i] == '1')
                {
                    buffer |= 1 << (7 - bufferSize);
                }

                if (++bufferSize == 8)
                { 
                    outputStream.put(buffer); 
                    buffer = 0; // reset buffer
                    bufferSize = 0; // reset bit size of buffer
                }
                numEncodedBits++;
            }
        }

        return numEncodedBits;
    }

    static void writeTrailingBits(std::ofstream& outputStream, int numPaddingBits)
    {
        // Pad last byte with 0s and write it out along with number of padding bits used  
        if (numPaddingBits > 0) {
            unsigned char lastByte = static_cast<unsigned char>(0);
            outputStream.put(lastByte);
        }

        // Write number of padding bits used as a single byte at end of file 
        outputStream.put(static_cast<unsigned char>(numPaddingBits));
    }

public:
    static void compress(std::string inputFile, std::string outputFile)
    {
        // Open input file for reading
        std::ifstream inputStream(inputFile, std::ios_base::binary);
        if (!inputStream.is_open()) {
            throw std::runtime_error("Error: could not open input file!");
        }
        
        // Open output file for writing
        std::ofstream outputStream(outputFile, std::ios_base::binary);
        if (!outputStream.is_open()) {
            throw std::runtime_error("Error: could not open output file!");
        }

        // Create a frequency table of characters in the input stream
        UMapFrT freqTable = buildFrequencyTable(inputStream);

        // Build Huffman tree based on frequency table 
        Node* root = buildHuffmanTree(freqTable);

        // Store mapping of characters to their respective Huffman codes in a map
        UMapCode codeMap;
        buildCodeMap(root, Str(), codeMap);

        // Write header information (frequency table) at beginning of compressed file
        writeHeader(outputStream, freqTable);

        // Reset position of input stream back to beginning before encoding data 
        inputStream.clear();
        inputStream.seekg(0, inputStream.beg);

        // Encode data using Huffman coding and write it out bit-by-bit into compressed file 
        int numEncodedBits = encodeData(inputStream, outputStream, codeMap); 

        // Pad last byte with 0s and write it out along with number of padding bits used
        int numOfPaddingBits = bitBuffer.length() % 8;
        writeTrailingBits(outputStream, numOfPaddingBits);

        // Close both files when finished.
        inputStream.close();
        outputStream.close();
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