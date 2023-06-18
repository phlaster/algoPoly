#ifndef CODEMAP_HPP
#define CODEMAP_HPP

#include "Node.hpp"
#include <map>
#include <string>
#include <iostream>


using Str = std::string;
using mapCode = std::map<char, Str>;

struct CodeMap
{
    mapCode map;
    int size;
    CodeMap(Node* root, const Str& initialCode);
    Str at(const char& c) const;
    void print();
    int minCodeLength();
private:
    void generateCodes(Node* nodePtr, const Str& currentCode);
};

#endif