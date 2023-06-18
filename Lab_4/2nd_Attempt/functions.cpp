#include "structs.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

FibonacciHeap* createHeap()
{
    FibonacciHeap* heap = new FibonacciHeap;
    heap->min = nullptr;
    heap->count = 0;
    heap->maxDegree = 0;
    return heap;
}

void insert(FibonacciHeap* heap, int value, int priority)
{
    Node* node = new Node;
    node->value = value;
    node->priority = priority;
    node->parent = nullptr;
    node->child = nullptr;
    node->left = node;
    node->right = node;
    node->marked = false;

    heap->roots.push_back(node);
    heap->count++;

    if (heap->min == nullptr || priority < heap->min->priority)
    {
        heap->min = node;
    }
}

void merge(FibonacciHeap* heap1, FibonacciHeap* heap2)
{
    heap1->roots.insert(heap1->roots.end(), heap2->roots.begin(), heap2->roots.end());
    heap1->count += heap2->count;

    if (heap1->min == nullptr || (heap2->min != nullptr && heap2->min->priority < heap1->min->priority)) {
        heap1->min = heap2->min;
    }
}



void link(Node* x, Node* y)
{
    y->left->right = y->right;
    y->right->left = y->left;

    y->parent = x;
    y->marked = false;

    if (x->child == nullptr)
    {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }

    x->degree++;
}

void consolidate(FibonacciHeap* heap)
{
    int maxDegree = log2(heap->count) + 1;
    vector<Node*> degreeTable(maxDegree, nullptr);

    for (Node* root : heap->roots) {
        Node* x = root;
        int degree = x->child == nullptr ? 0 : 1;
         
        while (degreeTable[degree] != nullptr) {
            Node* y = degreeTable[degree];

            if (x->priority > y->priority)
            {
                swap(x, y);
            }

            link(x, y);
            degreeTable[degree] = nullptr;
            degree++;
        }

        degreeTable[degree] = x;
    }

    heap->min = nullptr;

    for (Node* root : degreeTable)
    {
        if (root != nullptr) {
            heap->roots.push_back(root);

            if (heap->min == nullptr || root->priority < heap->min->priority)
            {
                heap->min = root;
            }
        }
    }
}

void removeMin(FibonacciHeap* heap)
{
    Node* min = heap->min;

    for (Node* child = min->child; child != nullptr; child = child->right)
    {
        heap->roots.push_back(child);
        child->parent = nullptr;
    }

    heap->roots.erase(remove(heap->roots.begin(), heap->roots.end(), min), heap->roots.end());
    heap->count--;

    if (heap->count == 0) {
        heap->min = nullptr;
    } else {
        heap->min = heap->roots[0];

        for (Node* root : heap->roots) {
            if (root->priority < heap->min->priority)
            {
                heap->min = root;
            }
        }

        consolidate(heap);
    }

    delete min;
}

void cut(FibonacciHeap* heap, Node* node)
{
    node->marked = false;

    if (node->parent == nullptr) {
        return;
    }

    Node* parent = node->parent;
    parent->degree--;

    if (node->right == node) {
        parent->child = nullptr;
    } else {
        parent->child = node->right;
        node->right->left = node->left;
        node->left->right = node->right;
    }

    heap->roots.push_back(node);
}

void cascadingCut(FibonacciHeap* heap, Node* node)
{
    Node* parent = node->parent;

    if (parent != nullptr) {
        if (node->marked == false) {
            node->marked = true;
        } else {
            cut(heap, node);
            cascadingCut(heap, parent);
        }
    }
}
void decreaseKey(FibonacciHeap* heap, Node* node, int newPriority)
{
    node->priority = newPriority;

    if (node->parent != nullptr && node->priority < node->parent->priority)
    {
        cut(heap, node);
        cascadingCut(heap, node->parent);
    }

    if (node->priority < heap->min->priority)
    {
        heap->min = node;
    }
}


void printHeap(FibonacciHeap* heap) {
        cout << "Heap: ";
        if (heap->min == nullptr) {
            cout << "Empty" << endl;
            return;
        }
        Node* curr = heap->min;
        do {
            cout << curr->degree << " ";
            curr = curr->right;
        } while (curr != heap->min);
        cout << endl;
    }