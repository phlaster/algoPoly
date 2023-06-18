#ifndef FTABLE_HPP
#define FTABLE_HPP

#include <string>
#include <map>
#include <fstream>
#include <iostream>


using String = std::string;
using mapFrT = std::map<unsigned char, int>;


struct FreqTable
{
    mapFrT table;
    int size;
    int numPaddingBits;
    FreqTable(const String& filename);
    FreqTable(std::ifstream &inputStream);
    FreqTable(const mapFrT& freqTable);
    void generateFreqTable(std::ifstream &inputStream, mapFrT& freqTable, int& size);
    void print();
};

#endif