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

    bool operator==(const Point& other){
        return x==other.x && y==other.y;
    }

    Point operator+(const Point& other){
        return Point({x+other.x, y+other.y});
    }
    void print(){
        cout << "x=" << x << ", y=" << y << "\n";
    }

    // Сработает для начальной точки маршрута, чей родитель по умолчанию (-1,-1)
    bool isorphan() const{
        return x==-1 && y==-1;
    }

    // Проверяем, что точка на доске
    bool ontable(int N){
        return x >= 0 && y >= 0 && x < N && y < N;
    }
};

using DistanceGrid = vector<vector<int>>;
using ParentGrid = vector<vector<Point>>;



// Печать матрицы в терминал
void print(const DistanceGrid& dGrid) {
    for (size_t i = 0; i < size(dGrid); i++) {
        for (size_t j = 0; j < size(dGrid[0]); j++)
            // Не более чем двузначные расстояния
            if (dGrid[i][j]>99){
                cout << " .";
            }else{
                cout << setw(2) << dGrid[i][j];
            }
        cout << "\n";
    }
    cout << "\n";
}

// Печать в терминал пройденного пути в обратном порядке
// За исключением (-1,-1) -- технического родителя начальной точки
void print(const vector<Point>& ancestors){
    for (auto p : ancestors)
        if (!p.isorphan())
            p.print();
}

// Вернёт путь до текущеё клетки (если алгоритм её посещал)
vector<Point> findAncestors(const ParentGrid& pGrid, Point p){
    vector<Point> ancestors(0);
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
    // Символизирующими бесконечное расстояние
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
            // номера текущего шага, оставляя только неисследованные клетки (с "бесконечными" расстояниями) 
            if(nextPos.ontable(N) && distances[nextPos.x][nextPos.y] > i) {
                distances[nextPos.x][nextPos.y] = i;
                parents[nextPos.x][nextPos.y] = currPos;
                q.push(nextPos);
            }
        }
    }
    return make_pair(distances, parents);
}

int main() {
    int N, ax, ay, bx, by; // Chessboard size (N x N)
    while (true){
        cout << "Введите N: "; cin >> N; 
        if (N <= 0){
            cout << "Завершение программы!\n"; break;
        }

        cout << "Введите Ax, Ay, Bx, By: "; cin >> ax >> ay >> bx >> by;
        
        Point A = {ax, ay};
        Point B = {bx, by};
        if (!A.ontable(N) || !B.ontable(N)){
            cout << "Повторите ввод координат!\n"; continue;
        };

        cout << "Начальная точка:"; A.print();
        cout << "Конечная точка:"; B.print();

        auto [dGrid, pGrid] = pathfinder(N, A, B);
        vector<Point>ancestors = findAncestors(pGrid, B);
        if (size(ancestors)==0){
            // Такое может случиться, если доска слишком мала
            cout << "Пути не найдено!\n";
            continue;
        } else
            // Исключаем предка начальной точки с координатами (-1,-1)
            cout << "Длина пути: " << size(ancestors)-1 << "\n";
        
        cout << "Путь назад:\n";
        print(ancestors);

        cout << "\nРасстояния до клеток, песещённых алгоритмом:\n";
        print(dGrid);
    }
  	return 0;
}