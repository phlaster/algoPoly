#include "headers/HuffmanTree.hpp"
#include "headers/Node.hpp"
#include <queue>

HuffmanTree::HuffmanTree(const mapFrT& freqTable)
    {
        /*
            Первым шагом этой функции является определение лямбда-функции compare, которая будет использоваться для установки порядка приоритетов элементов в очереди с приоритетами (priority_queue) . Функция принимает два указателя на узлы(Node*), и использует перегруженный оператор ">" для сравнения данных этих двух узлов.
            
            Далее происходит создание пустой priority queue - pQueue типа std::priority_queue<Node*, std::vector<Node*>, decltype(compare)>, которая будет использоваться для хранения всех односимвольных деревьев. Каждый элемент этой очереди содержит указатель на Node - это либо отдельный символ (лист дерева), либо поддерево.
            
            Затем мы проходим через все пары ключ-значение в freqTable и создаем новый лист(узел) дерева Хaффмaнa, содержащий соответствующую информацию о каждом отдельном символе: значение символа, частоту его появления и два указателя на дочерние узлы (nullptr). Затем этот новый лист добавляется в очередь с приоритетами.
            
            Далее мы начинаем объединять наименьшие(самые редкие) деревья, используя алгоритм Хaффмaнa. Непрерывно извлекаем два элемента с минимальными значениями частоты из очереди pQueue, создавая новый узел-родитель. Этот узел-родитель имеет значение '\0' (null character), общую частоту равную суммарной частотности его потомков и каждого потомка присваивает как своего левого или правого потомка.
            
            В результате последовательного объединения наименее вероятных символов вышеописанным способом строится полное дерево Хaффмана со стартовым корнем . Как только остается только один элемент в priority queue - это будет корень всего дерева.
            
            Наконец, после того как было успешно построено полное бинарное дерево Хaффмана функцией buildHuffmanTree(), она возвращает указатель на корневой узел этого дерева
        */
        auto compare = [](const Node *lhs, const Node *rhs)
        { return *lhs > *rhs; };

        // Create priority queue of single-node trees ordered by increasing frequency 
        std::priority_queue<Node*, std::vector<Node*>, decltype(compare)> pQueue(compare);
        for (const auto& pair : freqTable) {
            pQueue.push(new Node(pair.first, pair.second, nullptr, nullptr));
        }

        // Combine smallest trees into larger ones until there is only one remaining - this will be our root node.
        while (pQueue.size() > 1) {
            Node *left = pQueue.top();
            pQueue.pop();
            
            Node *right = pQueue.top();
            pQueue.pop();
            
            int combinedFreq = left->frequency + right->frequency; 
            Node *parent = new Node('\0', combinedFreq, nullptr, nullptr);
            
            parent->left = left;
            parent->right = right;

            pQueue.push(parent);	
        }
    
        this->tree = pQueue.top(); 
    }

HuffmanTree::~HuffmanTree() {
    deleteTree(this->tree);
}

void HuffmanTree::deleteTree(Node* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}
