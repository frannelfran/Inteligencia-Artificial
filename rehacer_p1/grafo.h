#pragma once
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Grafo {
 public:
  // Constructor
  Grafo(ifstream& file);

  // Métodos
  void DFS(const int nodo_origen, const int nodo_destino, ofstream& file); // Búsqueda en profundidad
  void BFS(const int nodo_origen, const int nodo_destino, ofstream& file); // Búsqueda en amplitud
  void AgregarArista(const int& nodo_origen, const int& nodo_destino, const double& coste) { grafo_[nodo_origen][nodo_destino] = coste; } // Añadir arista al grafo

  // Sobrecarga de operadores
  friend ostream& operator<<(ostream& os, const Grafo& grafo);

 private:
  vector<vector<double>> grafo_;
  int num_nodos_;
  int num_aristas_;
};