#include "headers/FreqTable.hpp"


FreqTable::FreqTable(const String& filename)
{
    std::ifstream inputStream(filename, std::ios_base::binary);
    if (!inputStream.is_open()) {
        throw std::runtime_error("Error: could not open input file!");
    }
    generateFreqTable(inputStream, this->table, this->size);
}


FreqTable::FreqTable(const mapFrT& freqTable)
{
    this->table = freqTable;
    this->size = freqTable.size();
}


void FreqTable::generateFreqTable(std::ifstream &inputStream, mapFrT& freqTable, int& size)
{
    char byte;

    // Проходим по входному файлу, подсчитывая количество встреченных разных
    while (inputStream.get(byte)) {
        ++freqTable[static_cast<unsigned char>(byte)];
    }
    size = freqTable.size();
}


void FreqTable::print()
{
    std::cout << "Таблица частот встречающихся байтов:\nДлина: ";
    std::cout << this->size << "\nASCII байт  частота\n";
    for (const auto& [ch, freq] : this->table)
    {
        uint byte = static_cast<unsigned char>(ch);
        if (33 <= byte && byte <= 126) // Если возможно - печатаем символ
        {
            std::cout << static_cast<unsigned char>(byte) << "     " ;
        } else {
            std::cout << "      ";
        }
        std::cout << byte << "   " << freq << "\n";
    }
}