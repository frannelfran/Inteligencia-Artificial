#pragma once
#include "../nodo/nodo.h"
#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <set>
#include <vector>

using namespace std;

class Arbol {
 public:
  // Constructores
  Arbol() {}
  Arbol(ifstream&);

  // Getters
  int GetAristas() const { return aristas_; }
  int GetNumNodos() const { return nodos_; }

  // Funciones
  inline void InsertarNodo(const Nodo& nodo) { arbol_.insert({nodo.GetPadre(), nodo}); }
  void DFS(int nodo_origen, int nodo_destino, ofstream& file); // Busqueda en profundidad

  friend ostream& operator<<(ostream& os, const Arbol& arbol);

 private:
  multimap<int, Nodo> arbol_;
  int aristas_;
  int nodos_;
};