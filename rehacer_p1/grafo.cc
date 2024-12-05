#include "grafo.h"

/**
 * @brief Constructor de la clase grafo
 * @param matriz_coste Matriz de costes
*/

Grafo::Grafo(ifstream& file) {
  double coste;
  int num_nodos;
  file >> num_nodos;
  grafo_.resize(num_nodos, vector<double>(num_nodos, -1));
  for (int i = 0; i < num_nodos; i++) {
    for (int j = i + 1; j < num_nodos; j++) {
      file >> coste;
      if (coste != -1) {
        AgregarArista(i, j, coste);
        // No dirigido
        AgregarArista(j, i, coste);
      }
    }
  }
  this->num_nodos_ = num_nodos;
  this->num_aristas_ = num_nodos * (num_nodos - 1) / 2;
}

/**
 * @overload Sobrecarga del operador de salida
*/

ostream& operator<<(ostream& os, const Grafo& grafo) {
  for (int i = 0; i < grafo.grafo_.size(); i++) {
    os << "Nodo " << i + 1 << ": ";
    for (int j = 0; j < grafo.grafo_[i].size(); j++) {
      if (grafo.grafo_[i][j] != -1) {
        os << j + 1 << " ";
      }
    }
    os << endl;
  }
  return os;
}