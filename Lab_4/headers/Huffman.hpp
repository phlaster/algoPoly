#ifndef HUFFMAN_HPP
#define HUFFMAN_HPP

#include "HuffmanTree.hpp"
#include "CodeMap.hpp"
#include "FreqTable.hpp"

#include <fstream>
#include <bitset>
#include <iostream>
#include <utility>

using In = std::ifstream;
using Out = std::ofstream;
using Str = std::string;
using Pair = std::pair<int, int>;

class Huffman
{
private:
    static int encodeData(In& inputStream, Out& outputStream, const CodeMap& codeMap);
    static int decodeData(In& inputStream, Out& outputStream, HuffmanTree& huffTree);
    static Pair getPaddingBitsAndFSize(In& fileStream);
public:
    static void compress(Str inputFile, Str outputFile);
    static void decompress(Str inputFile, Str outputFile);
    static void writeHeader(Out& outputStream, FreqTable& freqTable);
    static FreqTable readHeader(In& inputStream);
};

#endif