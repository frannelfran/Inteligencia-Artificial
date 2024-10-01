#pragma once
#include "../nodo/nodo.h"
#include "../arista/arista.h"
#include <fstream>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <vector>



using namespace std;

class Arbol {
 public:
  Arbol() = default;
  Arbol(const vector<vector<double>>&);

  void InsertarNodo(const Nodo& nodo, const Arista& arista) { arbol_.insert({nodo, arista}); } // Método para insertar un nodo en el árbol

  void DFS(const int nodo_origen, const int nodo_destino, ofstream& file); // Búsqueda en profundidad
  void BFS(const int nodo_origen, const int nodo_destino, ofstream& file); // Búsqueda en amplitud
  
  // Sobrecarga del operador de salida
  friend ostream& operator<<(ostream& os, const Arbol& arbol);

 private:
  multimap<Nodo, Arista> arbol_;
  int num_nodos_;
  int num_aristas_;
};