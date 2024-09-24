#pragma once
#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

class Nodo {
 public:
  Nodo() = default;
  Nodo(const int& padre, const int& hijo, const double& coste); // Constructor de la clase nodo

  friend ostream& operator<<(ostream& os, const Nodo& nodo);

 private:
  unordered_map<int, int> nodo_;
  double coste_;
};