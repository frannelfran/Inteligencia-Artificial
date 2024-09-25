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

  inline void InsertarNodo(const Nodo& nodo) { arbol_.insert({nodo.GetPadre(), nodo}); }
  bool ExisteNodo(const Nodo& nodo) const;

  friend ostream& operator<<(ostream& os, const Arbol& arbol);

 private:
  unordered_multimap<int, Nodo> arbol_;
};