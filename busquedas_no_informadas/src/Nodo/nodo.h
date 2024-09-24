#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

class Nodo {
 public:
  Nodo() = default;
  Nodo(const int, const int);

 private:
  unordered_map<int, int> nodo_;
};