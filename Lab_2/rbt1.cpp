#include <iostream>
#include "Class_RBTree.cpp"
/*
    12.	Реализовать операции добавления и удаления в красно-черное
    дерево со ссылками на предков и фиктивным элементом, на который
    указывают листья и корень.
*/
int main() {
  RedBlackTree rbTree;
  std::cout << "Tree created!\n";

  for (int i = 1; i <= 6; i++) {
    rbTree.addNode(7*(i-1)+i);
  }

  std::cout << "Tree filled with values\n\n\n";
  std::cout << "Now we delete...\n";

  for (int i = 0; i <= 20; i++) {
    rbTree.deleteNode(2*i+1);
  }
}
