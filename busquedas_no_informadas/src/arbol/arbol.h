#pragma once
#include "../nodo/nodo.h"
#include <iostream>
#include <map>
#include <fstream>

using namespace std;

class Arbol {
 public:
  // Constructores
  Arbol() {}
  Arbol(ifstream&);

  inline void InsertarNodo(const Nodo& nodo) { arbol_.insert({nodo.GetPadre(), nodo}); }

  friend ostream& operator<<(ostream& os, const Arbol& arbol);

 private:
  multimap<int, Nodo> arbol_;
};