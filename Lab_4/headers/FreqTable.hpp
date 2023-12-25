#ifndef FTABLE_HPP
#define FTABLE_HPP

#include <string>
#include <map>
#include <fstream>
#include <iostream>


using Str = std::string;
using mapFrT = std::map<unsigned char, int>;
using In = std::ifstream;

struct FreqTable
{
    mapFrT table;
    size_t size;
    int numPaddingBits;
    FreqTable(const Str& filename);
    FreqTable(std::ifstream &inputStream);
    FreqTable(const mapFrT& freqTable);
    void generateFreqTable(std::ifstream &inputStream, mapFrT& freqTable, size_t& size);
    void print();
};
#endif