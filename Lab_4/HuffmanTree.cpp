#include "headers/HuffmanTree.hpp"


HuffmanTree::HuffmanTree(const FreqTable& freqTable)
{
    // Инициализируем переменные нулями.
    this->numLeaves = 0;
    this->numNodes = 0;

    // Создаем лямбда-функцию compare, которая будет использоваться для
    // сравнения элементов в приоритетной очереди.
    auto compare = [](const Node *lhs, const Node *rhs)
    { return *lhs > *rhs; };

    // Создаем приоритетную очередь, которая будет хранить указатели на узлы дерева.
    std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> pQueue(compare);
    
    // Добавляем в приоритетную очередь узлы-листья для каждого символа из таблицы
    // частот. Устанавливаем указатели на левый и правый потомков в nullptr.
    for (const auto& pair : freqTable.table) {
        pQueue.push(new Node(pair.first, pair.second, nullptr, nullptr));
        this->numNodes++;
        this->numLeaves++;
    }

    // Выполняем цикл, пока в приоритетной очереди не останется только один элемент.
    // Извлекаем два узла с наименьшими частотами из приоритетной очереди. Создаем
    // новый узел-родитель, устанавливаем его частоту как сумму частот левого и
    // правого потомков. Устанавливаем указатели на левый и правый потомков
    // родителя. Добавляем новый узел-родитель в приоритетную очередь.
    while (pQueue.size() > 1) {
        Node *left = pQueue.top();
        pQueue.pop();
        
        Node *right = pQueue.top();
        pQueue.pop();
        
        int combinedFreq = left->frequency + right->frequency;
        Node *parent = new Node('0', combinedFreq, nullptr, nullptr);
        
        parent->left = left;
        parent->right = right;

        pQueue.push(parent);
        this->numNodes++;
        
    }

    // Устанавливаем корень дерева как последний элемент в приоритетной очереди.
    this->root = pQueue.top();
}

void HuffmanTree::print() {
    std::cout << "Дерево Хаффмана:\n";
    std::cout << "Number of nodes: " << this->numNodes << "\n";
    std::cout << "Number of leaves: " << this->numLeaves << "\n";

    std::queue<Node*> q;
    q.push(this->root);

    while (!q.empty()) {
        int levelSize = q.size();
        for (int i = 0; i < levelSize; i++) {
            Node* curr = q.front();
            q.pop();

            if (curr->isLeaf())
            {
                std::cout << curr->data << " (" << curr->frequency << ") ";
            } else {
                std::cout << " ( ) ";
                q.push(curr->left);
                q.push(curr->right);
            }
        }
        std::cout << "\n";
    }
}

// Деструктор
HuffmanTree::~HuffmanTree() {
    deleteTree(this->root);
}

// Рекурсивный метод деструктора
void HuffmanTree::deleteTree(Node* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}
