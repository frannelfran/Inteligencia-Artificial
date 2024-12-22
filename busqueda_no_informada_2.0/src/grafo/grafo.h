#pragma once
#include "../nodo/nodo.h"
#include <fstream>
#include <stack> // Para el recorrido en profundidad
#include <set>
#include <map>
#include <random>
#include <algorithm> // Para shuffle

class Grafo {
 public:
  // Constructor
  Grafo(const vector<vector<double>>&);

  // Destructor
  ~Grafo();

  // Funciones
  void MostrarIteracion(const int& iteracion, const vector<int>& generados, const vector<int>& inspeccionados) const; // Mostrar la iteración actual
  void InsertarNodo(const Nodo& nodo) { grafo_.insert({nodo, nodo.GetHijos()}); } // Inserta un nodo en el grafo
  void RecorridoProfundidad(Nodo& inicial, Nodo& final); // Realiza un recorrido en profundidad
  
  // Sobrecarga de operadores
  friend ostream& operator<<(ostream& os, const Grafo& grafo) {
    for (auto& nodo : grafo.grafo_) {
      os << nodo.first << endl;
    }
    return os;
  }

 private:
  map<Nodo, vector<pair<Nodo*, double>>> grafo_;
};