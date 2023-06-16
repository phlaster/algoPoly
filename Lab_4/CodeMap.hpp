#ifndef CODEMAP_HPP
#define CODEMAP_HPP

#include <map>
#include <string>
#include "Node.hpp"

using Str = std::string;
using mapCode = std::map<char, Str>;

class CodeMap {
private:
    mapCode content;
    mapCode generateCodes(Node* nodePtr, const Str& currentCode);
public:
    /*
        Строит таблицу отображения между символами и соответствующими им кодами Хаффмана.
        Алгоритм проходится по всем узлам деревьев рекурсивно. Если данная вершина является
        листом, то она добавляет свой код к таблицe codeMap(символ -> его закодированный
        вид). Иначе же вызывается функция снова для правого потомка узла со значением "1"
        добавленным к текущей последовательности битов(code + "1"), после этого также
        вызывается функция для левого потомка узла со значением "0" прибавленным к текущей
        последовательности битов(code + "0"). В конце все значения из полученных хэш-таблиц
        объединяются в одну таблицу codeMap.
    */
    CodeMap(Node* root, const Str& initialCode);
    Str at(const char& c) const;

};

#endif