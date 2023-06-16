#include "headers/HuffmanTree.hpp"
#include "headers/Node.hpp"
#include "headers/Printer.hpp"
#include "headers/CodeMap.hpp"
#include <fstream>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <iomanip>
#include <iterator>
#include <map>

using Str =  std::string;
using mapFrT =  std::map<char, int>;


class Huffman
{
private:
    static std::bitset<8> bitBuffer;

    static void writeSingleCharacterFile(Node *root, const Str &outputFilePath)
    {
        /*
            Принимает указатель на корень дерева Хаффманa (Node*) и ссылку на строку, представляющую путь к выходному файлу(outputFilePath).
            Первым шагом этой функции является создание объекта std::ofstream с использованием outputFilePath и флагов std::ios_base::out | std::ios_base::binary. Эти флаги гарантируют открытие файла в бинарном режиме для записи.
            Затем проверяется, был ли файл успешно открыт. Если это не так, то выбрасывается исключение.
            Далее происходит получение значения символа из узла root->data и сохранение его как unsigned char(byte). Запись значения byte производится методом write() у outputFile используя reinterpret_cast<char*>().
            Наконец, после того как данные были успешно записаны на диск, вызывается метод close() у outputFile чтобы закрыть поток вывода.
            Таким образом, данная функция может быть использованна при кодировании сообщений алгоритмом Хаффманa если остался только один символ без повторений.
        */
        std::ofstream outputFile(outputFilePath, std::ios_base::out | std::ios_base::binary);
        if (!outputFile.is_open())
            throw std::invalid_argument("Failed to open output file");

        unsigned char byte = (unsigned char)root->data;
        outputFile.write(reinterpret_cast<char *>(&byte), sizeof(byte));

        outputFile.close();
    }
    
    static mapFrT buildFrequencyTable(std::ifstream& inputStream)
    {
        /*
            Первым шагом этой функции является создание пустой unordered_map freqTable типа mapFrT (alias for std::unordered_map<char, unsigned int>), которая будет использоваться для хранения количества каждого уникального символа из inputStream.
            Далее происходит итерация через все символы в inputStream. Каждый раз, когда вызывается метод get() у inputStream и полученный результат сохраняется как переменная char c. Затем используя оператор ++freqTable[c] мы увеличиваем значение элемента соответствующего ключу c (символьное значение) на 1.
            Наконец, после того как были подсчитаны частоты всех символов из input stream заполненную таблицу частот(freqTable) передается обратно(возвращается).
            Таким образом, данная функция может быть использованна при кодировании сообщений алгоритмом Хaффмaнa чтобы определить вероятности появления каждого отдельного символа в текстовых данных.
        */
        mapFrT freqTable;

        // Iterate through all characters in input stream and count their frequencies
        char c;
        while (inputStream.get(c)) {
            ++freqTable[c];
        }

        return freqTable;
    }

    static void writeHeader(std::ofstream &outputStream, mapFrT &freqTable)
    {

        // Write size of frequency table first
        int freqTableSize = static_cast<int>(freqTable.size());
        outputStream.write(reinterpret_cast<const char *>(&freqTableSize), sizeof(freqTableSize));
        
        // // Write out each pair in turn - first character then integer count.
        for (const auto& pair : freqTable) {
            outputStream.put(pair.first);
            outputStream.write(reinterpret_cast<const char *>(&pair.second), sizeof(pair.second));
        }
    }

    static mapFrT readHeader(std::ifstream& inputStream)
    {
        mapFrT freqTable;
        // Читаем размер таблицы
        uint freqTableSize;
        inputStream.read(reinterpret_cast<char*>(&freqTableSize), sizeof(freqTableSize));
        // Read frequency table entries from input stream
        for (int i = 0; i < freqTableSize; i++) {
            // Read character as a single byte from input stream
            unsigned char c;
            inputStream.get(reinterpret_cast<char&>(c));
            // Read frequency as a 4-byte integer from input stream
            int freq;
            inputStream.read(reinterpret_cast<char*>(&freq), sizeof(freq));
            // Add entry to frequency table
            freqTable[c] = freq;
        }
        return freqTable;
    }

    static int encodeData(std::ifstream& inputStream, std::ofstream& outputStream, const CodeMap& codeMap)
    {
        int totalEncoded = 0; // количество закодированных битов.
        unsigned char positionInBuffer = 0; // текущий байт для записи в выходной поток.
        int numBitsInBuffer = 0;

        char c;
        while (inputStream.get(c)) { // берём по символу до конца файла
            const Str& code = codeMap.at(c); // получаем их код
            for (int i = 0; i < static_cast<int>(code.size()); ++i) {
                if (code[i] == '1')
                {
                    positionInBuffer |= 1 << (7 - numBitsInBuffer); // ставим соответствующий бит в буфере
                }

                if (++numBitsInBuffer == 8) // по заполнении буфера
                { 
                    outputStream.put(positionInBuffer); // кладём в поток
                    positionInBuffer = 0; // очищаем буфер
                    numBitsInBuffer = 0; // reset bit size of buffer
                }
                totalEncoded++;
            }
        }
        return totalEncoded;
    }

    static void decodeData(std::ifstream& inputStream, std::ofstream& outputStream, Node* root, int numPaddingBits)
    {
        Node* currentNode = root;
        unsigned char byte;
        unsigned char bit;

        while (inputStream.get(reinterpret_cast<char&>(byte))) {
            for (int i = 7; i >= 0; i--) {
                bit = (byte >> i) & 1;
                if (bit == 0) {
                    currentNode = currentNode->left;
                } else {
                    currentNode = currentNode->right;
                }
                if (currentNode->left == nullptr && currentNode->right == nullptr) {
                    outputStream.put(currentNode->data);
                    currentNode = root;
                }
            }
        }

        if (numPaddingBits > 0) {
            inputStream.get(reinterpret_cast<char&>(byte));
            byte = byte << (8 - numPaddingBits);
            for (int i = 7; i >= numPaddingBits; i--) {
                bit = (byte >> i) & 1;
                if (bit == 0) {
                    currentNode = currentNode->left;
                } else {
                    currentNode = currentNode->right;
                }
                if (currentNode->left == nullptr && currentNode->right == nullptr) {
                    outputStream.put(currentNode->data);
                    currentNode = root;
                }
            }
        }
    }

    static void writeTrailingBits(std::ofstream& outputStream, int numPaddingBits, std::bitset<8>& bitBuffer)
    {
        if (numPaddingBits > 0) {
            unsigned char lastByte = static_cast<unsigned char>(bitBuffer.to_ulong() << (8 - numPaddingBits));
            outputStream.put(lastByte);
        }
        outputStream.put(static_cast<unsigned char>(numPaddingBits));
    }


public:
    static void compress(std::string inputFile, std::string outputFile)
    {
        std::ifstream inputStream(inputFile, std::ios_base::binary);
        if (!inputStream.is_open()) {
            throw std::runtime_error("Error: could not open input file!");
        }
        std::ofstream outputStream(outputFile, std::ios_base::binary);
        if (!outputStream.is_open()) {
            throw std::runtime_error("Error: could not open output file!");
        }

        mapFrT freqTable = buildFrequencyTable(inputStream);
        HuffmanTree huffTree = HuffmanTree(freqTable);
        
        CodeMap codeMap(huffTree.tree, Str());
        writeHeader(outputStream, freqTable);
        
        inputStream.clear();
        inputStream.seekg(0, inputStream.beg);
        
        int numEncodedBits = encodeData(inputStream, outputStream, codeMap); 
        int numOfPaddingBits = (8 - numEncodedBits % 8) % 8;
        
        writeTrailingBits(outputStream, numOfPaddingBits, bitBuffer);
        inputStream.close();
        outputStream.close();
    }

    static void decompress(std::string inputFile, std::string outputFile)
    {
        std::ifstream inputStream(inputFile, std::ios_base::binary);
        if (!inputStream.is_open()) {
            throw std::runtime_error("Error: could not open input file!");
        }
        std::ofstream outputStream(outputFile, std::ios_base::binary);
        if (!outputStream.is_open()) {
            throw std::runtime_error("Error: could not open output file!");
        }

        mapFrT freqTable = readHeader(inputStream);
        Printer::printFreq(freqTable);
        HuffmanTree huffTree = HuffmanTree(freqTable);
        Printer::printTree(huffTree.tree);

///////////////////////////////////////////////////////////////////

        inputStream.close();
        outputStream.close();
    }

};