#include <iostream>
#include <queue>

// Класс узла дерева
class TreeNode
{
    int *keys; // целочисленный массив значений в узле 
    int minDeg; // Минимальная степень узла
    TreeNode **children; // Массив указателей на детей узла
    int n; // Количество значений узла (длина массива значений)
    bool isLeaf; // Является ли узел листом

public:
    // Конструктор
    TreeNode(int _minDeg, bool _isLeaf)
    {
        minDeg = _minDeg;
        isLeaf = _isLeaf;
        keys = new int[2 * minDeg - 1];
        children = new TreeNode *[2 * minDeg];
        n = 0; // Созданный узел пока не имеет значений
    }

    // Вставка значения в узел
    void insertNonFull(int value) {
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

    // Разделяем i-того ребёнка узла на два узла
    // Первые minDeg-1 значений и указателей на детей остаются с прежним узлом
    // Остальные значения и указатели на детей передаются новому узлу newNode
    void splitChild(int i, TreeNode *node)
    {
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

    // Объявляем класс-друг, который будет иметь доступ к приватным полям
    friend class BTree;
};

// Класс b-дерева
class BTree 
{
    TreeNode *root; // Указатель на корень дерева
    int minDeg; // Минимальная степень узла
    
    // Проверка заполненности узла
    bool isFull(TreeNode *node) { return node->n == 2 * minDeg - 1;}

public:
    // Конструктор
    BTree(int _minDeg)
    {
        root = NULL;
        minDeg = _minDeg;
    }

    // Вставляет значение в дерево
    void insert(int value)
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
                // Создалим новый узел
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

    // Печатаем дерево
    void printLevelOrder()
    {
        // Для пустого дерева
        if (root == NULL)
        {
            std::cout << "Tree is empty!\n";
            return;
        }
        // Используем структуру "очередь" из стандартной библиотеки
        std::queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {   
            int n = int(q.size());
            for (int i = 0; i < n; i++)
            {
                TreeNode *node = q.front();
                q.pop();

                
                /*
                    Не самая чистая работа. Числа подбирались, чтобы более-менее адекватно
                    Отображать пример из задания и другие деревья на 10-15 элементов
                */
                if (!node->isLeaf) for (int j = 0; j < (20-7*n); j++)
                    std::cout << ' ';

                std::cout << '(';
                for (int j = 0; j < node->n; j++)
                  std::cout << node->keys[j] << ',';
                std::cout << "\b) "; // Удаляем последнюю запятую

                if (!node->isLeaf) for (int k = 0; k <= node->n; k++) q.push(node->children[k]);
            }
            std::cout << std::endl;
        }
    }
};


int main() {
    BTree t(3);
    t.insert(15);
    t.insert(50);
    t.insert(10);
    t.insert(1);
    t.insert(4);
    t.insert(5);
    t.insert(7);
    t.insert(55);
    t.insert(60);
    t.insert(63);
    t.insert(30);
    t.insert(33);
    t.insert(40);
    std::cout << "14 The B-tree is: \n";
    t.printLevelOrder();
    std::cout << std::endl;

    BTree t2(3);
    for(int i=0; i<10; i++) t2.insert(i);
    std::cout << "10 The B-tree is: \n";
    t2.printLevelOrder();
    std::cout << std::endl;

    BTree t3(3);
    for(int i=0; i<12; i++) t3.insert(i);
    std::cout << "12 The B-tree is: \n";
    t3.printLevelOrder();
    std::cout << std::endl;

    BTree t4(3);
    for(int i=0; i<15; i++) t4.insert(i);
    std::cout << "15 The B-tree is: \n";
    t4.printLevelOrder();
    std::cout << std::endl;

    BTree t5(3);
    for(int i=0; i<20; i++) t5.insert(i);
    std::cout << "20 The B-tree is: \n";
    t5.printLevelOrder();
    std::cout << std::endl;
}