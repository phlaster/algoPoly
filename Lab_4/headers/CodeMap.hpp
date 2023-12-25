#ifndef CODEMAP_HPP
#define CODEMAP_HPP

#include "Node.hpp"
#include <map>
#include <string>
#include <iostream>


using Str = std::string;
using mapCode = std::map<unsigned char, Str>;

struct CodeMap
{
    mapCode map;
    size_t size;
    CodeMap(Node* root, const Str& initialCode);
    Str at(const unsigned char& c) const;
    void print();
private:
    void generateCodes(Node* nodePtr, const Str& currentCode);
};

#endif