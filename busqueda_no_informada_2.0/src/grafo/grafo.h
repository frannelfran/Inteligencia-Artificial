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
  Grafo(const vector<vector<double>>& matriz, const Nodo& raiz);

  // Destructor
  ~Grafo() {
    delete raiz_;
  }

  // Funciones
  void MostrarIteracion(const int& iteracion, const vector<int>& generados, const vector<int>& inspeccionados, ofstream& file) const; // Mostrar la iteración actual
  //void RecorridoProfundidad(Nodo& inicial, Nodo& final, ofstream& file); // Realiza un recorrido en profundidad
  void RecorridoAmplitud(Nodo& final, ofstream& file); // Realiza un recorrido en amplitud
  bool EstaEnRama(Nodo* padre, Nodo* nodo); // Comprueba si un nodo esta en la misma rama que su padre
  void MostrarCamino(Nodo* nodo, ofstream& file); // Muestra el camino desde el nodo inicial hasta el nodo final
  double CalcularCosteTotal(Nodo* nodo); // Calcula el coste total de un camino

  // Setters
  inline void CambiarRaiz(const Nodo& raiz) { delete raiz_, raiz_ = new Nodo(raiz.GetId()); }
  
  // Sobrecarga de operadores
  friend ostream& operator<<(ostream& os, const Grafo& grafo) {
    for (auto& nodo : grafo.grafo_) {
      os << nodo.first << " -> ";
      for (auto& hijo : nodo.second) {
        os << hijo.first << "(" << hijo.second << ") ";
      }
      os << endl;
    }
    return os;
  }

 private:
  map<int, vector<pair<int, double>>> grafo_;
  Nodo* raiz_;
  int num_nodos_;
  int num_aristas_ = 0;
};