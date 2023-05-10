#include <queue>
#include <cstddef>
#include <iostream>
#include "Classes.hpp"


bool BTree::isFull(TreeNode *node) { return node->n == 2 * minDeg - 1;}

void BTree::destroyTree(TreeNode *node)
{
    if (node != NULL)
    {
        // Сначала удаляем детей
        for (int i = 0; i <= node->n; i++)
        {
            destroyTree(node->children[i]);
        }
        // Затем удаляем сам узел
        delete node;
    }
}

BTree::BTree(int _minDeg)
{
    root = NULL;
    minDeg = _minDeg;
}

BTree::~BTree()
{
    destroyTree(root);
}

void BTree::insert(const int value)
{   
    // Если дерево пустое, создаёт первый узел
    if (root == NULL)
    {
        root = new TreeNode(minDeg, true);
        root->keys[0] = value;
        root->n = 1;
    }
    else
    {
        // Если узел полон
        if (isFull(root))
        {
            // Создадим новый узел
            TreeNode *s = new TreeNode(minDeg, false);
            s->children[0] = root;

            // Разделим старый надвое
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < value) i++;

            // И рекурсивно вставим значение в правильное поддерево
            s->children[i]->insertNonFull(value);
            root = s;
        }
        // Если узел не заполнен, то просто вставляем значение
        else root->insertNonFull(value);
    }
}

int BTree::printLevelOrder()
{
    int n_nodes = 0;
    // Для пустого дерева
    if (root == NULL)
    {
        std::cout << "Tree is empty!\n";
        return n_nodes;
    }
    // Используем структуру "очередь" из стандартной библиотеки
    std::queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {   
        std::cout << q.size() << ": ";
        int n = int(q.size());
        for (int i = 0; i < n; i++)
        {
            TreeNode *node = q.front();
            q.pop();                
            /*
                Не самая чистая работа. Числа подбирались, чтобы более-менее адекватно
                Отображать пример из задания и другие деревья на 10-15 элементов
            */

            for (int j = 0; j < (40-7*n); j++)
                std::cout << ' ';

            std::cout << '(';
            for (int j = 0; j < node->n; j++)
                std::cout << node->keys[j] << ',';
            std::cout << "\b) "; // Удаляем последнюю запятую
            n_nodes += 1;

            if (!node->isLeaf) for (int k = 0; k <= node->n; k++) q.push(node->children[k]);
        }
        std::cout << std::endl;
    }
    return n_nodes;
}