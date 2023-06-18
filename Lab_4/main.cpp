#include "headers/Huffman.hpp"


std::bitset<8> Huffman::bitBuffer;

int main()
{
    Huffman::compress("Huffman_DEcode.cpp", "output.bin");
    Huffman::decompress("output.bin", "decoded_output.txt");

    return 0;
}