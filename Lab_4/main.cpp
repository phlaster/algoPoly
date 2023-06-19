#include "headers/Huffman.hpp"

// Немного кириллицы, чтобы подтвердить работу с другими
// кодировками (да и вообще с файлами любых типов)

int main()
{
    Huffman::compress("test.txt", "output.bin");
    Huffman::decompress("output.bin", "decoded_output.txt");
    Huffman::decompress("sample.bin", "decoded_sample.txt");

    return 0;
}