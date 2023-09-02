#include <iostream>
using namespace std;

// Функция очистки вывода консоли
void Clear()
{
    #if defined _WIN32
    system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    cout << u8"\033[2J\033[1;1H";
    #elif defined (__APPLE__)
    system("clear");
    #endif
}

// Структура узла
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Функция для создания нового узла дерева
Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Ошибка при выделении памяти!" << endl;
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Функция для вставки узла в бинарное дерево
Node* insertNode(Node* root, int data) {
    // Если отсутствует -- создаём корень
    if (root == NULL) {
        root = createNode(data);
        return root;
    }

    //Вставляем потомков в соответствии с их значением
    if (data < root->data) {
        root->left = insertNode(root->left, data);
    } else if (data > root->data) {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Функция для вывода содержимого бинарного дерева в прямом порядке
// Сначала -- текущий узел (начиная с узла), затем его левое поддерево, а затем -- правое.
void displayPreorder(Node* root) {
    if (root != NULL) {
        cout << root->data << " ";
        displayPreorder(root->left);
        displayPreorder(root->right);
    }
}

// Функция для поиска минимального узла в правом поддереве
Node* findMin(Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
} 

void deleteNode(Node* &root, int data) {
    if (root == NULL) {
        return;
    }
    if (data < root->data) {
        deleteNode(root->left, data);
    } else if (data > root->data) {
        deleteNode(root->right, data);
    } else {
        // Удаление узла
        if (root->left == NULL && root->right == NULL) {
            // Узел без потомков
            delete root;
            root = NULL;
        } else if (root->left == NULL) {
            // Узел с одним правым потомком
            Node* temp = root;
            root = root->right;
            delete temp;
        } else if (root->right == NULL) {
            // Узел с одним левым потомком
            Node* temp = root;
            root = root->left;
            delete temp;
        } else {
            // Узел с двумя потомками
            Node* temp = findMin(root->right);
            root->data = temp->data;
            deleteNode(root->right, temp->data);
        }
    }
}

// Функция для вывода дерева в графическом виде
void printTree(Node* root, string indent) {
    if (root != NULL) {
        cout << indent;
        cout << "└─";
        indent += "  ";
        cout << root->data << "\n";
        printTree(root->left, indent);
        printTree(root->right, indent);
    }
}

int main() {
    Node* root = NULL;
    int choice, item;
    Clear();
    while (1) {
        cout << "---------------------------------\n";
        if (root != NULL)
            printTree(root, "");
        else
            cout << "Пустое дерево!\n\n";
        cout << "Доступные операции:\n";
        cout << "1. Вставить элемент\n";
        cout << "2. Удалить узел\n";
        cout << "3. Вывести дерево прямым порядком" << endl;
        cout << "4. Выход\n";
        cout << "---------------------------------\n";
        cout << "Введите ваш выбор: ";
        cin >> choice;

        switch (choice) {
            case 1:
                Clear();
                cout << "Введите значение для вставки: ";
                cin >> item;
                root = insertNode(root, item);
                break;
            case 2:
                Clear();
                if (root == nullptr) {
                    cout << "Дерево пустое!" << endl;
                } else {
                    cout << "Введите значение узла для удаления: ";
                    cin >> item;
                    deleteNode(root, item);
                }
                break;
            case 3:
                Clear();
                if (root == NULL) {
                    cout << "Дерево пустое!" << endl;
                } else {
                    cout << "Прямой порядок дерева: ";
                    displayPreorder(root);
                    cout << endl;
                }
                break;
            case 4:
                Clear();
                cout << "Программа завершена." << endl;
                exit(0);
                break;
            default:
                cout << "Неверный выбор. Попробуйте еще раз." << endl;
        }
    }
    return 0;
}
