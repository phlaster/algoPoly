#include "structs.hpp"

#ifndef FUNCS_HPP
#define FUNCS_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>


FibonacciHeap* createHeap();
void insert(FibonacciHeap* heap, int value, int priority);
void merge(FibonacciHeap* heap1, FibonacciHeap* heap2);
void link(Node* x, Node* y);
void consolidate(FibonacciHeap* heap);
void removeMin(FibonacciHeap* heap);
void cut(FibonacciHeap* heap, Node* node);
void cascadingCut(FibonacciHeap* heap, Node* node);
void decreaseKey(FibonacciHeap* heap, Node* node, int newPriority);
void printHeap(FibonacciHeap* heap);
#endif