#include <cstddef>


#ifndef TREENODE_HPP
#define TREENODE_HPP
class TreeNode
{
    int *keys; // целочисленный массив значений в узле 
    int minDeg; // Минимальная степень узла
    TreeNode **children; // Массив указателей на детей узла
    int n; // Количество значений узла (длина массива значений)
    bool isLeaf; // Является ли узел листом
public:
    // Конструктор
    TreeNode(const int _minDeg, const bool _isLeaf);
    
    // Вставка значения в узел
    void insertNonFull(const int value);

    
    // Разделяем i-того ребёнка узла на два узла
    void splitChild(const int i, TreeNode *node);

    // Объявляем класс-друг, который будет иметь доступ к приватным полям
    friend class BTree;
};
#endif



#ifndef BTREE_HPP
#define BTREE_HPP
class BTree 
{
    TreeNode *root; // Указатель на корень дерева
    int minDeg; // Минимальная степень узла  
    
    // Проверка заполненности узла
    bool isFull(TreeNode *node);
    
    // Рекурсивно удаляет все узлы дерева
    void destroyTree(TreeNode *node);
public:
    // Конструктор
    BTree(int _minDeg);

    // Деструктор
    ~BTree();
    
    // Вставляет значение в дерево
    void insert(const int value);
    
    // Печатаем дерево, возвращает количество узлов
    int printLevelOrder();
};
#endif