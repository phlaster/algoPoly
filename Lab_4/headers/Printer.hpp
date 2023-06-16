#ifndef PRINTERP_HPP
#define PRINTERP_HPP

#include "Node.hpp"
#include <map>
#include <string>

using mapFrT =  std::map<char, int>;
using mapCode =  std::map<char, std::string>;

class Printer
{
public:
    static void printFreq(const mapFrT &freqTable);
    static void printTree(Node *root);
    static void printCodes(const mapCode &codeMap);
};

#endif