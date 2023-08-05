#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;
using Str = string;
using Pair = pair<Str, int>;

void quickSort(vector<Pair>& data);
void printSorted(vector<Pair>& data);
vector<Pair> readdata(const Str& filename);
bool hasCollisions(vector<Pair>& data);
Str wordOccurs(const vector<Pair>& data, int value);