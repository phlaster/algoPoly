#include "headers/Huffman.hpp"
#include <climits>



Pair Huffman::getPaddingBitsAndFSize(In& fileStream)
{
    std::streampos currentPosition = fileStream.tellg();
    fileStream.seekg(0, std::ios_base::end);
    std::streampos fileSize = fileStream.tellg();
    
    fileStream.seekg(-1,std::ios_base::cur); 
    
    char lastByte; // Здесь записано количество заполняющих нулей в предпоследнем байте
    fileStream.get(lastByte);
    fileStream.seekg(currentPosition, std::ios_base::beg);
    
    // Количество байт, которые нужно расшифровать
    int numBytesRemaining = static_cast<int>(fileSize - currentPosition);

    // Заполняющие нули в последнем байте
    int numPaddingBits = static_cast<int>(lastByte);
    
    return Pair(numBytesRemaining, numPaddingBits); ;
}

int Huffman::decodeData(std::ifstream& inputStream, std::ofstream& outputStream, CodeMap& codeMap, HuffmanTree& huffTree)
{
    int numDecodedBits = 0;
    const auto&[numBytesRemaining, numPaddingBits] = getPaddingBitsAndFSize(inputStream);
    char nextByte = 0;
    int bytesDecoded = 0;
    char bakingByte = 0; // Этот будем записывать в файл
    int bitPos = 7; // Пойдём от младшего бита к старшему
    Node* currentNode = huffTree.root;

    // Выполняем цикл, пока не достигнем конца входного потока или не расшифруем все байты.
    while (inputStream.get(nextByte) && bytesDecoded < numBytesRemaining - 1)
    {
        bytesDecoded++;
        // Выполняем цикл по битам в байте, начиная с младшего бита.
        for(int i=bitPos; i>=0; --i)
        {
            // Если мы достигли последнего байта и проходим по битам, которые нужно
            //  проигнорировать, то выходим из цикла.
            if (bytesDecoded == numBytesRemaining - 1 && i < numPaddingBits) break;

            // Если значение бита равно 1, то переходим в правого потомка текущего узла.
            if ((nextByte>>i) & 1) {   
                currentNode=currentNode->right;
            } else {
                currentNode=currentNode->left;
            }
            
            // Если текущий узел является листом, то записываем его значение в outputByte,
            // записываем outputByte в выходной поток, увеличиваем счетчик numDecodedBits и
            // переходим к корню дерева Хаффмана.
            if (currentNode->isLeaf())
            {
                bakingByte=currentNode->data;
                outputStream.put(bakingByte);
                ++numDecodedBits;
                currentNode=huffTree.root;
            }
        }
        bitPos = 7;
    }
    return numDecodedBits;
}

void Huffman::decompress(Str inputFile, Str outputFile)
{
    In inputStream(inputFile, std::ios_base::binary);
    if (!inputStream.is_open()) {
        throw std::runtime_error("Error: could not open input file!");
    }
    Out outputStream(outputFile, std::ios_base::binary);
    if (!outputStream.is_open()) {
        throw std::runtime_error("Error: could not open output file!");
    }

    std::cout << "Расшифровка:\n";
    FreqTable freqTable = readHeader(inputStream);
    freqTable.print();
    std::cout << "\n";

    HuffmanTree huffTree = HuffmanTree(freqTable);

    // Инициализируем создание карты кодов пустым кодом (пустая строка)
    CodeMap codeMap(huffTree.root, Str());
    codeMap.print();
    std::cout << "\n";

    int numDecodedBits = decodeData(inputStream, outputStream, codeMap, huffTree);
    std::cout << "\n";
    std::cout << numDecodedBits << " бит было разкодировано!\n";

    inputStream.close();
    outputStream.close();
}