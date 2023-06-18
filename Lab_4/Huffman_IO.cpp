#include "headers/Huffman.hpp"


void Huffman::writeHeader(Out& outputStream, FreqTable &freqTable)
{
    outputStream << static_cast<unsigned char>(freqTable.size);
    
    for (const auto& [byte, freq]: freqTable.table)
    {
        outputStream << byte;
        outputStream.write(reinterpret_cast<const char*>(&freq), sizeof(freq));
    }
}

FreqTable Huffman::readHeader(In& inputStream)
{
    mapFrT freqTable;
    char freqTableSize;
    inputStream.get(freqTableSize);

    for (char i = '\0'; i < freqTableSize; i++) {
        unsigned char c;
        inputStream.get(reinterpret_cast<char&>(c));
        
        int freq;
        inputStream.read(reinterpret_cast<char*>(&freq), sizeof(freq));
        freqTable[c] = freq;
    }
    return FreqTable(freqTable);
}