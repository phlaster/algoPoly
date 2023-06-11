#include "Huffman.cpp"

Str HuffmanCoding::bitBuffer = "";

int main()
{
    HuffmanCoding::compress("input.txt",
                            "output.bin");
    // HuffmanCoding::decompress("output.bin",
    //                             "decoded_output.txt");
    return 0;
}