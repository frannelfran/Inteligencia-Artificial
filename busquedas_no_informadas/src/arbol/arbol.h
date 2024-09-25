#pragma once
#include "../nodo/nodo.h"
#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

class Arbol {
 public:
  // Constructores
  Arbol() {}
  Arbol(ifstream&);

  void InsertarNodo(const Nodo& nodo);
  bool ExisteNodo(const Nodo& nodo) const;

 private:
  unordered_multimap<int, Nodo> arbol_;
};