#include <cstdlib>
#include <ctime>

#include "Classes.hpp"
#include "functions.hpp"


void Animation(int delay)
{
    while (true)
    {
        BTree t(3);
        for(int i=0; i<30; i++)
        {
            Clear();
            t.insert(randInt(1, 99));
            t.printLevelOrder();
            Delay(delay);
        }
        Delay(delay * 10);
    }
}


int main() {
    srand(time(NULL));
    Animation(300);
    return 0;
}