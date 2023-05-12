#include <iostream>

#include "Classes.hpp"
#include "functions.hpp"


void runAnimation
(
    const int n_values=20,
    const int minDegree=3,
    const int delay_ms=200,
    const int minval = 0,
    const int maxval=100
)
{
    int n_nodes = 0;
    BTree t(minDegree);
    for(int i=0; i<n_values; i++)
    {
        Clear();
        std::cout << "Минимальная степень не листового узла: " << minDegree << "\n";
        std::cout << "Значений: " << i+1 << "/" << n_values << "\n";
        t.insert(randInt(minval, maxval));
        n_nodes = t.printLevelOrder();
        std::cout << "Узлов: " << n_nodes << "\n";
        Delay(delay_ms);
    }
    std::cout << "\nДерево нарисовано!\n";
}


int main(int argc, char* argv[]) {
    srand(time(NULL));
    switch (argc)
    {
        case 1:
            runAnimation();
            break;
        case 2:
            runAnimation(
                atoi(argv[1])
                );
            break;
        case 3:
            runAnimation(
                atoi(argv[1]),
                atoi(argv[2])
                );
            break;
        case 4:
            runAnimation(
                atoi(argv[1]),
                atoi(argv[2]),
                atoi(argv[3])
                );
            break;
        case 5:
            runAnimation(
                atoi(argv[1]),
                atoi(argv[2]),
                atoi(argv[3]),
                atoi(argv[4]));
            break;
        case 6:
            runAnimation(
                atoi(argv[1]),
                atoi(argv[2]),
                atoi(argv[3]),
                atoi(argv[4]),
                atoi(argv[5])
                );
            break;
        default:
            std::cout << "Wrong number of arguments\n";
            break;

    }
    return 0;
}