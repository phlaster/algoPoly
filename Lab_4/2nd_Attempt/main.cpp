// #include "functions.hpp"


// int main() {
//     FibonacciHeap* heap = createHeap();

//     insert(heap, 1, 5);
//     printHeap(heap);
//     insert(heap, 2, 3);
//     printHeap(heap);
//     insert(heap, 3, 7);
//     printHeap(heap);
//     insert(heap, 4, 1);
//     printHeap(heap);
//     insert(heap, 5, 9);
//     printHeap(heap);

//     removeMin(heap);

//     decreaseKey(heap, heap->roots[2]->child, 2);

//     return 0;
// }


#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <climits>

using namespace std;

struct Node {
    int key;
    int degree;
    bool marked;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
};

class FibonacciHeap {
public:
    FibonacciHeap() {
        min = nullptr;
        n = 0;
    }

    bool isEmpty() {
        return min == nullptr;
    }

    void insert(int key) {
        Node* x = new Node;
        x->key = key;
        x->degree = 0;
        x->marked = false;
        x->parent = nullptr;
        x->child = nullptr;
        if (min != nullptr) {
            (min->left)->right = x;
            x->right = min;
            x->left = min->left;
            min->left = x;
            if (x->key < min->key) {
                min = x;
            }
        } else {
            min = x;
        }
        n++;
        printHeap();
    }

    int getMinimum() {
        return min->key;
    }

    int removeMinimum() {
        Node* z = min;
        int key = z->key;
        Node* x = z->child;
        Node* tmp;
        while (x != nullptr) {
            tmp = x->right;
            (min->left)->right = x;
            x->right = min;
            x->left = min->left;
            min->left = x;
            x->parent = nullptr;
            x = tmp;
        }
        (z->left)->right = z->right;
        (z->right)->left = z->left;
        if (z == z->right) {
            min = nullptr;
        } else {
            min = z->right;
            consolidate();
        }
        n--;
        printHeap();
        return key;
    }

    void decreaseKey(Node* x, int k) {
        if (k > x->key) {
            return;
        }
        x->key = k;
        Node* y = x->parent;
        if (y != nullptr && x->key < y->key) {
            cut(x, y);
            cascadingCut(y);
        }
        if (x->key < min->key) {
            min = x;
        }
        printHeap();
    }

    void deleteNode(Node* x) {
        decreaseKey(x, INT_MIN);
        removeMinimum();
    }

    void printHeap() {
        cout << "Heap: ";
        if (min == nullptr) {
            cout << "Empty" << endl;
            return;
        }
        Node* curr = min;
        do {
            cout << curr->key << " ";
            curr = curr->right;
        } while (curr != min);
        cout << endl;
    }

private:
    Node* min;
    int n;

    void link(Node* y, Node* x) {
        (y->left)->right = y->right;
        (y->right)->left = y->left;
        y->parent = x;
        if (x->child == nullptr) {
            x->child = y;
            y->right = y;
            y->left = y;
        } else {
            y->left = x->child;
            y->right = (x->child)->right;
            ((x->child)->right)->left = y;
            x->child->right = y;
        }
        x->degree++;
        y->marked = false;
    }

    void consolidate() {
        int maxDegree = static_cast<int>(log2(n)) + 1;
        vector<Node*> A(maxDegree, nullptr);
        Node* w = min;
        Node* x;
        Node* y;
        Node* tmp;
        do {
            x = w;
            int d = x->degree;
            while (A[d] != nullptr) {
                y = A[d];
                if (x->key > y->key) {
                    tmp = x;
                    x = y;
                    y = tmp;
                }
                link(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
            w = x->right;
        } while (w != min);
        min = nullptr;
        for (int i = 0; i < maxDegree; i++) {
            if (A[i] != nullptr) {
                if (min == nullptr) {
                    min = A[i];
                } else {
                    (min->left)->right = A[i];
                    A[i]->right = min;
                    A[i]->left = min->left;
                    min->left = A[i];
                    if (A[i]->key < min->key) {
                        min = A[i];
                    }
                }
            }
        }
    }

    void cut(Node* x, Node* y) {
        (x->left)->right = x->right;
        (x->right)->left = x->left;
        y->degree--;
        if (y->child == x) {
            y->child = x->right;
        }
        if (y->degree == 0) {
            y->child = nullptr;
        }
        x->right = x;
        x->left = x;
        (min->left)->right = x;
        x->right = min;
        x->left = min->left;
        min->left = x;
        x->parent = nullptr;
        x->marked = false;
    }

    void cascadingCut(Node* y) {
        Node* z = y->parent;
        if (z != nullptr) {
            if (y->marked == false) {
                y->marked = true;
            } else {
                cut(y, z);
                cascadingCut(z);
            }
        }
    }
};

int main() {
    FibonacciHeap heap;


    heap.insert(5);
    heap.printHeap();
    heap.insert(3);
    heap.printHeap();
    heap.insert(7);
    heap.printHeap();
    heap.insert(1);
    heap.printHeap();
    heap.insert(9);
    heap.printHeap();
    heap.removeMinimum();
    heap.printHeap();
    Node* node = new Node;
    node->key = 2;
    heap.decreaseKey(node, 4);
    heap.printHeap();
    heap.deleteNode(node);
    heap.printHeap();

    return 0;
}
