#pragma once
#include "../nodo/nodo.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <list>

class Laberinto {
 public:
  // Constructores
  Laberinto() = default;
  Laberinto(ifstream&);

  // Métodos
  void EstablecerHeuristica(); // Establece la heurística de los nodos del laberinto
  void EstablecerCostoCamino(Nodo&, Nodo&); // Establece el costo del camino de los nodos del laberinto
  void CambiarEntradaSalida(const Posicion&, const Posicion&); // Cambia la entrada y salida del laberinto
  void BusquedaAEstrella(); // Realiza la búsqueda A* en el laberinto

  // Getters
  list<Nodo> GetVecinos(Nodo) const; // Retorna los nodos vecinos de un nodo

  // Comprobar cosas
  bool EsPosicionValida(const Posicion&) const; // Comprueba si una posición es válida
  bool EsPared(const Posicion&) const; // Comprueba si una posición es una pared
  bool EsDiagonal(const Posicion&, const Posicion&) const; // Comprueba si una posición es diagonal

  // Sobrecarga de operadores
  friend ostream& operator<<(ostream&, const Laberinto&);

 private:
  vector<vector<Nodo>> laberinto_;
  Posicion entrada_; // Entrada del laberinto
  Posicion salida_; // Salida del laberinto
  int diagonal_ = 7;
  int frontal_ = 5;
};