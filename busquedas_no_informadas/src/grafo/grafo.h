#pragma once
#include "nodo/nodo.h"
#include <iostream>
#include <unordered_map>

using namespace std;

class Grafo {
 public:
  Grafo() = default;

  void InsertarNodo(const Nodo& nodo);

 private:
  unordered_map<int, Nodo> grafo_;
};









}