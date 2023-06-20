#include "headers/Huffman.hpp"


int Huffman::encodeData(In& inputStream, Out& outputStream, const CodeMap& codeMap)
{
    int numEncodedBits = 0;
    int numPaddingBits = 0;
    char currentByte = 0;
    char bakingByte = 0x0; // байт, который будет записан в выходной поток
    int bitPos = 0;

    while (inputStream.get(currentByte))
    {
        // Получаем код символа из карты кодов.
        Str code = codeMap.map.at(currentByte);
        for (char c : code) {
            if (c == '1')
            {
                // Если текущий символ равен '1', то переворачиваем соответствующий бит
                bakingByte |= (0x80 >> bitPos);
            }
            bitPos++;
            numEncodedBits++;

            if (bitPos > 7)
            {
                // записываем bakingByte в выходной поток, обнуляем его
                outputStream.put(bakingByte);
                bakingByte = 0;
                bitPos = 0;
            }
        }
    }
    if (bitPos > 0)
    {
        //  Если мы остановились посередине байта, записываем bakingByte,
        // т.к. в нём уже присутствуют заполняющие нули
        numPaddingBits = 8 - bitPos;
        outputStream.put(bakingByte);
    }
    outputStream.put(static_cast<unsigned char>(numPaddingBits));
    return numEncodedBits;
}


void Huffman::compress(Str inputFile, Str outputFile, bool verbose)
{
    In inputStream(inputFile, std::ios_base::binary);
    if (!inputStream.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для чтения!");
    }
    Out outputStream(outputFile, std::ios_base::binary);
    if (!outputStream.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи!");
    }

    std::cout << "Сжатие данных:\n";
    FreqTable freqTable(inputFile);
    if(verbose){
        freqTable.print();
        std::cout << "\n";
    }

    HuffmanTree huffTree = HuffmanTree(freqTable);
    if(verbose){
        huffTree.print();
        std::cout << "\n";
    }

    // Инициализируем создание карты кодов пустым кодом (пустая строка)
    CodeMap codeMap(huffTree.root, Str());
    if(verbose){
        codeMap.print();
        std::cout << "\n";
    }

    writeHeader(outputStream, freqTable);

    int numEncodedBits = encodeData(inputStream, outputStream, codeMap);

    inputStream.close();
    outputStream.close();

    std::cout << inputFile << " -> " << outputFile << "\n";
    std::cout << numEncodedBits << " бит закодировано\nИз которых ";
    std::cout << numEncodedBits % 8 << " в последнем байте\n\n";

}