#include "headers/Huffman.hpp"


Pair Huffman::getPaddingBitsAndFSize(In& fileStream)
{
    std::streampos currentPosition = fileStream.tellg();
    fileStream.seekg(0, std::ios_base::end);
    std::streampos fileSize = fileStream.tellg();
    
    fileStream.seekg(-1,std::ios_base::cur); 
    
    char lastByte; // Здесь записано количество заполняющих нулей в предпоследнем байте
    fileStream.get(lastByte);
    fileStream.seekg(currentPosition, std::ios_base::beg);
    
    // Количество байт, которые остались в файловом потоке (для расшифровки)
    int numBytesRemaining = static_cast<int>(fileSize - currentPosition);

    // Заполняющие нули в последнем байте
    int numPaddingBits = static_cast<int>(lastByte);
    
    // Для удобства возвращаем сразу пару значений
    return Pair(numBytesRemaining, numPaddingBits); ;
}

int Huffman::decodeData(std::ifstream& inputStream, std::ofstream& outputStream, HuffmanTree& huffTree)
{
    int numDecodedBits = 0;
    const auto&[numBytesRemaining, numPaddingBits] = getPaddingBitsAndFSize(inputStream);
    char nextByte = 0;
    int bytesDecoded = 0;
    Node* currentNode = huffTree.root;

    // Выполняем цикл, пока не достигнем конца входного потока или не расшифруем все байты.
    while (inputStream.get(nextByte) && bytesDecoded < numBytesRemaining - 1)
    {
        bytesDecoded++;
        // Выполняем цикл по битам в байте, начиная с младшего бита.
        for(int i=7; i>=0; --i)
        {
            // Если мы достигли заполняющих битов в последнем байте - выходим из цикла.
            if (bytesDecoded == numBytesRemaining - 1 && i < numPaddingBits) break;

            // Если значение бита равно 1, то переходим к правому потомку узла
            if ((nextByte>>i) & 1) {   
                currentNode=currentNode->right;
            } else { // Иначе - к левому
                currentNode=currentNode->left;
            }
                       
            if (currentNode->isLeaf()) // Если текущий узел является листом
            {
                outputStream.put(currentNode->data); // записываем его в выходной поток
                ++numDecodedBits;
                currentNode=huffTree.root;  // переходим к корню дерева Хаффмана
            }
        }
    }
    return numDecodedBits;
}

void Huffman::decompress(Str inputFile, Str outputFile)
{
    In inputStream(inputFile, std::ios_base::binary);
    if (!inputStream.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для чтения!");
    }
    Out outputStream(outputFile, std::ios_base::binary);
    if (!outputStream.is_open()) {
        throw std::runtime_error("Не удалось открыть файл для записи!");
    }

    std::cout << "Расшифровка:\n";
    FreqTable freqTable = readHeader(inputStream);
    // freqTable.print();
    // std::cout << "\n";

    HuffmanTree huffTree = HuffmanTree(freqTable);

    // Инициализируем создание карты кодов пустым кодом (пустая строка)
    CodeMap codeMap(huffTree.root, Str());
    // codeMap.print();
    // std::cout << "\n";

    int numDecodedBits = decodeData(inputStream, outputStream, huffTree);

    inputStream.close();
    outputStream.close();

    std::cout << inputFile << " -> " << outputFile << "\n";
    std::cout << numDecodedBits << " бит было разкодировано!\n\n";
}