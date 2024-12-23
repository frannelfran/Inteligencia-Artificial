#pragma once
#include "../nodo/nodo.h"
#include <fstream>
#include <stack> // Para el recorrido en profundidad
#include <queue> // Para el recorrido en amplitud
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
  void MostrarIteracion(const int& iteracion, const vector<int>& generados, const vector<int>& inspeccionados, ofstream& file) const; // Mostrar la iteración actual
  inline void InsertarNodo(const Nodo& nodo) { grafo_.insert({nodo, nodo.GetHijos()}); } // Inserta un nodo en el grafo
  void RecorridoProfundidad(Nodo& inicial, Nodo& final, ofstream& file); // Realiza un recorrido en profundidad
  void RecorridoAmplitud(Nodo& inicial, Nodo& final, ofstream& file); // Realiza un recorrido en amplitud
  
  // Sobrecarga de operadores
  friend ostream& operator<<(ostream& os, const Grafo& grafo) {
    for (auto& nodo : grafo.grafo_) {
      os << nodo.first << endl;
    }
    return os;
  }

 private:
  map<Nodo, vector<pair<Nodo*, double>>> grafo_;
  int num_nodos_;
  int num_aristas_;
};