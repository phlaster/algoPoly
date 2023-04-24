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

    // Заполняем дерево значениями
    for (int i = 1; i <= 6; i++) {
        rbTree.addNode(7*(i-1)+i);
    }

    std::cout << "Tree now filled with values\n\n\n";
    std::cout << "Now we delete...\n";

    // Пытаемся удалить некоторые значения
    for (int i = 0; i <= 21; i++) {
        rbTree.deleteNode(2*i+1);
    }
    std::cout << "\nExecution complete.\n";
    return 0;
}
