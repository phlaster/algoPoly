#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include "HuffmanTree.hpp"
#include "Node.hpp"
#include "Printer.hpp"
#include "CodeMap.hpp"
#include "FreqTable.hpp"

#include <fstream>
#include <bitset>
#include <iostream>





class Huffman
{
private:
    static std::bitset<8> bitBuffer;
    static void writeHeader(std::ofstream &outputStream, FreqTable &freqTable);
    static FreqTable readHeader(std::ifstream& inputStream);
    static int encodeData(std::ifstream& inputStream, std::ofstream& outputStream, const CodeMap& codeMap, FreqTable& freaqTable);
    static void decodeData(std::istream& inputStream, std::ostream& outputStream, CodeMap& codeMap, FreqTable& freqTable, HuffmanTree& huffTree);
    static void writeTrailingBits(std::ofstream& outputStream, int numPaddingBits, std::bitset<8>& bitBuffer);


public:
    static void compress(std::string inputFile, std::string outputFile);
    static void decompress(std::string inputFile, std::string outputFile);
};


#endif