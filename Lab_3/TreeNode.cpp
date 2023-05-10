#include <cstddef>
#include "Classes.hpp"

TreeNode::TreeNode(const int _minDeg, const bool _isLeaf)
{
    minDeg = _minDeg;
    isLeaf = _isLeaf;
    keys = new int[2 * minDeg - 1];
    children = new TreeNode *[2 * minDeg];
    n = 0; // Созданный узел пока не имеет значений
}


void TreeNode::insertNonFull(const int value) {
    int i = n - 1;
    // Если узел не заполнен, вставка в правильную позицию массива значений
    if (isLeaf) {
        while (i >= 0 && keys[i] > value) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = value;
        n++;
    }

    // Если заполнен - рекурсивно разделяем узлы потомков,
    // Вставляем в правильную позицию в получившееся поддерево
    else
    {
        while (i >= 0 && keys[i] > value) i--;
        if (children[i + 1]->n == 2 * minDeg - 1)
        {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < value) i++;
        }
        children[i + 1]->insertNonFull(value);
    }
}

void TreeNode::splitChild(const int i, TreeNode *node)
{
    // Первые minDeg-1 значений и указателей на детей остаются с прежним узлом
    // Остальные значения и указатели на детей передаются новому узлу newNode
    TreeNode *newNode = new TreeNode(node->minDeg, node->isLeaf);
    newNode->n = minDeg - 1;
    for (int j = 0; j < minDeg - 1; j++) newNode->keys[j] = node->keys[j + minDeg];
    if (!node->isLeaf) for (int j = 0; j < minDeg; j++) newNode->children[j] = node->children[j + minDeg];
    node->n = minDeg - 1;
    
    for (int j = n; j >= i + 1; j--) children[j + 1] = children[j];
    // Указатель на i+1-го ребёнка старого узла становится указателем на новый узел
    children[i + 1] = newNode; 
    
    for (int j = n - 1; j >= i; j--) keys[j + 1] = keys[j];
    
    // i-тое значение старого узла передаётся в подходящую позицию массива значений
    keys[i] = node->keys[minDeg - 1];
    n++;
}