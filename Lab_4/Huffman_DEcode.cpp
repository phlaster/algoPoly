#include "headers/Huffman.hpp"


void Huffman::decodeData(std::istream& inputStream, std::ostream& outputStream, CodeMap& codeMap, FreqTable& freqTable, HuffmanTree& huffTree)
{
    // Read the size of the frequency table from the input stream.
    char tableSize;
    inputStream.get(tableSize);

    // Decode the input stream using the Huffman tree and the code map.
    Node* currentNode = huffTree.root;
    char byte;
    while (inputStream.get(byte))
    {
        // Convert the byte to a bitset.
        std::bitset<8> bits(byte);

        // Iterate over each bit in the bitset.
        for (int i = 7; i >= 0; i--)
        {
            // Traverse the Huffman tree based on the current bit.
            currentNode = bits[i] ? currentNode->right : currentNode->left;

            // If a leaf node is reached, write the corresponding character to the output stream.
            if (!currentNode->left && !currentNode->right)
            {
                outputStream << currentNode->data;
                currentNode = huffTree.root;
            }
        }
    }

    // If the last byte contains padding bits, discard them.
    int paddingBits = freqTable.numPaddingBits;
    if (paddingBits > 0)
    {
        char lastByte;
        inputStream.seekg(-1, std::ios_base::end);
        inputStream.get(lastByte);
        inputStream.seekg(-1, std::ios_base::end);
        inputStream.putback(lastByte & ~(0xFF >> paddingBits));
    }
}

void Huffman::decompress(std::string inputFile, std::string outputFile)
{
    std::ifstream inputStream(inputFile, std::ios_base::binary);
    if (!inputStream.is_open()) {
        throw std::runtime_error("Error: could not open input file!");
    }
    std::ofstream outputStream(outputFile, std::ios_base::binary);
    if (!outputStream.is_open()) {
        throw std::runtime_error("Error: could not open output file!");
    }

    FreqTable freqTable = readHeader(inputStream);//freqTable(inputFile);
    freqTable.print();
    HuffmanTree huffTree = HuffmanTree(freqTable);
    CodeMap codeMap(huffTree.root, Str());

    decodeData(inputStream, outputStream, codeMap, freqTable, huffTree);

    inputStream.close();
    outputStream.close();
}