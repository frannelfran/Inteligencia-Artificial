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
  void CambiarEntrada(const Posicion&); // Cambia la entrada del laberinto
  void CambiarSalida(const Posicion&); // Cambia la salida del laberinto
  void BusquedaAEstrella(ofstream&); // Realiza la búsqueda A* en el laberinto
  void MostrarCamino(ofstream&); // Muestra el camino encontrado
  void ResetearValores(); // Resetea los valores de los nodos del laberinto

  // Getters
  list<Nodo> GetVecinos(const Nodo&) const; // Retorna los nodos vecinos de un nodo
  int CostoTotalCamino() const; // Retorna el costo total del camino
  Posicion GetEntrada() const { return entrada_; } // Retorna la entrada del laberinto
  Posicion GetSalida() const { return salida_; } // Retorna la salida del laberinto
  int GetFilas() const { return filas_; } // Retorna el número de filas del laberinto
  int GetColumnas() const { return columnas_; } // Retorna el número de columnas del laberinto

  // Setters
  void SetValores(const list<Nodo>&); // Establece el costo total y el costo del camino de los nodos

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
  int filas_;
  int columnas_;
};