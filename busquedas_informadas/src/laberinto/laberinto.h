#pragma once
#include "../nodo/nodo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

class Laberinto {
 public:
  // Constructores
  Laberinto() = default;
  Laberinto(ifstream&);

  // Métodos
  void EstablecerHeuristica(); // Establece la heurística de los nodos del laberinto



  // Sobrecarga de operadores
  friend ostream& operator<<(ostream&, const Laberinto&);

 private:
  vector<vector<Nodo>> laberinto_;
  Posicion entrada_;
  Posicion salida_;
};