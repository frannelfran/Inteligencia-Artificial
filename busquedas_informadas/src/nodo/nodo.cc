#include "nodo.h"
#include "../laberinto/laberinto.h"

list<Nodo> Nodo::GetVecinos(const Laberinto& lab) const {
  list<Nodo> vecinos; // Lista de nodos vecinos
  Posicion pos = this->posicion_; // Posición del nodo actual
  int x = pos.GetX(); // Coordenada x del nodo actual
  int y = pos.GetY(); // Coordenada y del nodo actual

  // Comprobar las posiciones adyacentes al nodo actual
  vector<Posicion> posiciones { // Todas las posibilidades
    Posicion(x - 1, y), // Arriba
    Posicion(x + 1, y), // Abajo
    Posicion(x, y - 1), // Izquierda
    Posicion(x, y + 1), // Derecha
    Posicion(x - 1, y - 1), // Arriba izquierda
    Posicion(x - 1, y + 1), // Arriba derecha
    Posicion(x + 1, y - 1), // Abajo izquierda
    Posicion(x + 1, y + 1) // Abajo derecha
  };
  
  for (auto& p : posiciones) {
    if (lab.EsPosicionValida(p) && !lab.EsPared(p)) {
      vecinos.push_back(Nodo(p, 0));
    }
  }
  return vecinos;
}