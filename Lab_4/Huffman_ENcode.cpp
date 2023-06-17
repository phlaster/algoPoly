#include "headers/Huffman.hpp"


void Huffman::compress(std::string inputFile, std::string outputFile)
{
    std::ifstream inputStream(inputFile, std::ios_base::binary);
    if (!inputStream.is_open()) {
        throw std::runtime_error("Error: could not open input file!");
    }
    std::ofstream outputStream(outputFile, std::ios_base::binary);
    if (!outputStream.is_open()) {
        throw std::runtime_error("Error: could not open output file!");
    }

    FreqTable freqTable(inputFile);
    // freqTable.print();
    
    HuffmanTree huffTree = HuffmanTree(freqTable);
    // huffTree.print();

    CodeMap codeMap(huffTree.root, Str());
    writeHeader(outputStream, freqTable);
    
    // Возврат к началу файлового потока
    inputStream.clear();
    inputStream.seekg(0, inputStream.beg);
    

    int numEncodedBits = encodeData(inputStream, outputStream, codeMap, freqTable);
    
    std::cout << "\n";
    std::cout << numEncodedBits << " бит было записано!\n";
    inputStream.close();
    outputStream.close();
}

int Huffman::encodeData(std::ifstream& inputStream, std::ofstream& outputStream, const CodeMap& codeMap, FreqTable& freaqTable)
{
    int totalEncodedBits = 0;
    unsigned char bakingByte = 0; // будем печь новый байт для записи
    int numBitsInBuffer = 0;
    int numPaddingBits = 0;

    char byte;
    while (inputStream.get(byte)) // читаем по байту за раз
    {
        const Str& code = codeMap.at(byte); // получаем его код
        for (int i = 0; i < static_cast<int>(code.size()); ++i)
        {
            if (code[i] == '1')
            {
                bakingByte |= 1 << (7 - numBitsInBuffer); // месим тесто
            }

            if (++numBitsInBuffer == 8)
            { 
                outputStream.put(bakingByte); // в духовку его
                bakingByte = 0; // очищаем за собой стол
                numBitsInBuffer = 0; // сброс счётчика битов в буфере
            }
            totalEncodedBits++;
        }
    }

    // Добавляем дополнительные биты для выравнивания последнего байта
    if (numBitsInBuffer > 0)
    {
        numPaddingBits = 8 - numBitsInBuffer;
        bakingByte <<= numPaddingBits;
        outputStream.put(bakingByte);
        totalEncodedBits += numPaddingBits;
    }

    // Записываем количество дополнительных битов в последний байт
    if (numPaddingBits > 0)
    {
        outputStream.put(static_cast<unsigned char>(numPaddingBits));
    }
    freaqTable.numPaddingBits = numPaddingBits;

    return totalEncodedBits;
}
