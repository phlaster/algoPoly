#include "headers/CodeMap.hpp"


CodeMap::CodeMap(Node* root, const Str& initialCode) {
    generateCodes(root, initialCode);
    this->size = this->map.size();
}

Str CodeMap::at(const unsigned char& c) const
{
    return this->map.at(c);
}

void CodeMap::generateCodes(Node *nodePtr, const Str &currentPrefix)
{
    if (nodePtr == nullptr)
    {// Если указатель на узел равен nullptr, выходим из метода
        return;
    }
    // Если узел является листом, то добавляем его символ и код в таблицу
    if (nodePtr->left == nullptr && nodePtr->right == nullptr) {
        this->map[nodePtr->byte] = currentPrefix;
    }

    // Рекурсивно вызываем метод для левого поддерева, добавляя к текущему префиксу "0"
    generateCodes(nodePtr->left, currentPrefix + "0");
    // Рекурсивно вызываем метод для правого поддерева, добавляя к текущему префиксу "1"
    generateCodes(nodePtr->right, currentPrefix + "1");
}

void CodeMap::print()
{
    std::cout << "Словарь кодов Хаффмана:\nДлина:";
    std::cout << this->size << "\nASCII байт код\n";
    for (const auto& [ch, code] : this->map)
    {
        uint byte = static_cast<unsigned char>(ch);
        if (33 <= byte && byte <= 126)
        {
            std::cout << static_cast<char>(byte) << "     " ;
        } else {
            std::cout << "      ";
        }
        std::cout << (uint)static_cast<unsigned char>(ch) << "  '" << code << "'\n";
    }
}
