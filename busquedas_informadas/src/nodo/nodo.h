#pragma once
#include "../posicion/posicion.h"
#include <iostream>
#include <vector>

using namespace std;

class Nodo {
 public:
  // Constructores
  Nodo() = default;
  Nodo(Posicion posicion, int estado) : posicion_(posicion), estado_(estado) {}

  // Setters
  void SetHX(const int& h_x) { h_x_ = h_x; } // Establece la heurística del nodo
  void SetGX(const int& g_x) { g_x_ = g_x; } // Establece el costo del camino desde el nodo actual hasta el nodo objetivo
  void SetFX(const int& f_x) { f_x_ = f_x; } // Establece el costo total del nodo

  // Getters
  int GetEstado() const { return estado_; } // Retorna el estado del nodo
  const Posicion& GetPosicion() { return posicion_; } // Retorna la posición del nodo

  // Sobrecarga de operadores
  friend ostream& operator<<(ostream& os, const Nodo& nodo) {
    os << nodo.estado_ << " ";
    return os;
  }

 private:
  int estado_; // Estado del nodo
  Posicion posicion_;
  vector<Nodo> hijos_; // Hijos del nodo
  int costo_camino_; // Costo del camino desde el nodo raíz hasta el nodo actual
  int h_x_; // Heurística del nodo
  int g_x_; // Costo del camino desde el nodo actual hasta el nodo objetivo
  int f_x_; // Costo total del nodo
};