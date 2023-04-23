#include "types.hpp"

class RedBlackTree : Tree {
private:
  void initializeNULLNode(NodePtr, NodePtr);
  void balanceAfterDelete(NodePtr); // Балансировка после удаления элемента
  void subtreeReplace(NodePtr, NodePtr); // Переукоренение веток
  void deleteNodeHelper(NodePtr, int);
  void balanceAfterInsert(NodePtr); // Балансировка после вставки
  void leftRotate(NodePtr);
  void rightRotate(NodePtr);
  NodePtr minimum(NodePtr); // Левый ребёнок, пока он есть, минимален
  NodePtr maximum(NodePtr); // Правый ребёнок, пока он есть, максимален
public:
  // Конструктор
  RedBlackTree();
  NodePtr successor(NodePtr); // Узел с наименьшим значением, которое больше, чем в данном узле
  NodePtr predecessor(NodePtr); // Узел с наибольшим значением, которое меньше, чем в данном узле
  void addNode(int);
  void deleteNode(int);
};