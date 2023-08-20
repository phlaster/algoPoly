/*
Задание 4.3
Кратчайший путь
На шахматной доске размером N*N найти кратчайший путь
ходами коня из поля А в поле В.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

struct Point {
    int x;
    int y;

    bool operator==(const Point& other) const {
        return x==other.x && y==other.y;
    }

    Point operator+(const Point& other) const {
        return Point({x+other.x, y+other.y});
    }

    void print() const {
        cout << "   x=" << x << ", y=" << y << "\n";
    }

    // Сработает для начальной точки маршрута, чей родитель по умолчанию (-1,-1)
    bool isorphan() const{
        return x==-1 && y==-1;
    }

    // Проверяем, что точка на доске
    bool onTable(int N) const{
        return x >= 0 && y >= 0 && x < N && y < N;
    }

    // Необходимо для цветного отображения
    bool inVector(const vector<Point>& V) const{
        for (const auto& p : V)
            if (p.x == x && p.y == y)
                return true;
        return false;
    }
};

using DistanceGrid = vector<vector<int>>;
using ParentGrid = vector<vector<Point>>;

// Печать матрицы в терминал
void print(const DistanceGrid& dGrid, const vector<Point>& pts) {
    for (size_t i = 0; i < size(dGrid); i++) {
        for (size_t j = 0; j < size(dGrid[0]); j++)
            // Не более чем двузначные расстояния
            if (dGrid[j][i]>99){
                cout << " .";
            }else{
                if (Point({int(j),int(i)}).inVector(pts)){
                    // Красим цифру, если точка присутствует в пути
                    cout << "\e[1m\x1B[91m" << setw(2) << dGrid[j][i] << "\033[0m\e[0m";
                } else{
                    cout << setw(2) << dGrid[j][i];
                }
            }
        cout << "\n";
    }
    cout << "\n";
}

// Печать в терминал пройденного пути в обратном порядке
// За исключением крайних точек и технического родителя (-1,-1)
void print(const vector<Point>& path){
    for (int i=size(path)-3; i>0; i--)
        path[i].print();
}

// Вернёт путь до текущеё клетки (если алгоритм её посещал)
vector<Point> findAncestors(const ParentGrid& pGrid, Point p){
    vector<Point> ancestors(1, p);
    while (!p.isorphan()){
        p = pGrid[p.x][p.y];
        ancestors.push_back(p);
    }
    return ancestors;
}


pair<DistanceGrid,ParentGrid> pathfinder(int N, const Point& start, const Point& stop) {
    vector<Point> allowedMoves = {
        {-2,-1}, {-1,-2}, { 1,-2}, { 2,-1}, {-2, 1}, {-1, 2}, { 1, 2}, { 2, 1}
    };
    // Матрица расстояний, заполняемая алгоритмом
    // Изначально заполнена произвольными большими числами,
    // Символизирующими "бесконечное" расстояние
    DistanceGrid distances(N,vector<int>(N,99999));

    // Матрица координат точек, из которых мы пришли в текущую
    ParentGrid parents(N,vector<Point>(N, Point{-1,-1}));

    // Очередь реализует алгоритм поиска в ширину
    queue<Point> q;
  
  	q.push(start);
  	distances[start.x][start.y] = 0;
  	while (!q.empty()) {
      	Point currPos = q.front();
        int i = distances[currPos.x][currPos.y]+1;
      	q.pop();

        if (currPos == stop)
            // Если мы дошли до B на i-м шаге, алгоритм сделает
            // углубится не более, чем на расстояние i+1
            return make_pair(distances, parents);

        for(Point move : allowedMoves) {
            Point nextPos = currPos+move;

            // Второе условие исключает точки, вычисленное расстояние до которых меньше
            // номера текущего шага (остаются только с "бесконечными" расстояниями) 
            if(nextPos.onTable(N) && distances[nextPos.x][nextPos.y] > i) {
                distances[nextPos.x][nextPos.y] = i;
                parents[nextPos.x][nextPos.y] = currPos;
                q.push(nextPos);
            }
            if (nextPos == stop)
                return make_pair(distances, parents);
        }
    }
    return make_pair(distances, parents);
}

int main() {
    int N, ax, ay, bx, by;
    while (true){
        cout << "Введите N: "; cin >> N; 
        if (N<1 || N>50){
            cout << "Завершение программы!\n"; break;
        }

        cout << "Введите Ax, Ay, Bx, By: "; cin >> ax >> ay >> bx >> by;
        
        Point A = {ax, ay};
        Point B = {bx, by};
        if (!A.onTable(N) || !B.onTable(N)){
            cout << "Повторите ввод координат!\n"; continue;
        };


        auto [dGrid, pGrid] = pathfinder(N, A, B);
        vector<Point>ancestors = findAncestors(pGrid, B);
        
        cout << "Весь путь:\n";
        cout << "A: x="<<A.x<<", y="<<A.y<<"\n";
        print(ancestors);
        cout << "B: x="<<B.x<<", y="<<B.y<<"\n";

        if (size(ancestors)==2){
            // Такое может случиться, если доска слишком мала
            cout << "Путь не найден или равен нулю!\n";
            continue;
        } else
            // Исключаем предка начальной точки с координатами (-1,-1)
            // И конечную точку
            cout << "Длина пути: " << size(ancestors)-2 << "\n";
        cout << "Расстояния до клеток, посещённых алгоритмом:\n";
        print(dGrid, ancestors);
    }
  	return 0;
}
