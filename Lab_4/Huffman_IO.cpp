#include "headers/Huffman.hpp"


void Huffman::writeHeader(std::ofstream &outputStream, FreqTable &freqTable)
{
    mapFrT ft = freqTable.table;

    // Первый байт - длина таблицы
    outputStream << static_cast<char>(ft.size());
    
    // Write out each pair in turn - first character then integer count.
    for (const auto& [byte, n]: ft)
    {
        outputStream << byte;
        outputStream.write(reinterpret_cast<const char*>(&n), sizeof(n));
    }
}

FreqTable Huffman::readHeader(std::ifstream& inputStream)
{
    mapFrT freqTable;
    
    // Читаем первый байт - размер таблицы
    uint freqTableSize;
    inputStream.get(reinterpret_cast<char&>(freqTableSize));
    // inputStream.read(reinterpret_cast<char*>(&freqTableSize), sizeof(freqTableSize));
    
    for (int i = 0; i < freqTableSize; i++) {
        // Сначала байт
        unsigned char c;
        inputStream.get(reinterpret_cast<char&>(c));
        
        // Потом его частота
        int freq;
        inputStream.read(reinterpret_cast<char*>(&freq), sizeof(freq));
        
        // Вносим в таблицу
        freqTable[c] = freq;
    }

    return FreqTable(freqTable);
}