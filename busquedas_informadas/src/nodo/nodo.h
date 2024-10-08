#pragma once
#include "../posicion/posicion.h"
#include "../laberinto/laberinto.h"
#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Nodo {
 public:
  // Constructores
  Nodo() = default;
  Nodo(Posicion posicion, int estado) : posicion_(posicion), estado_(estado) {}

  // Setters
  void SetEstado(const int& estado) { estado_ = estado; } // Establece el estado del nodo
  void SetHN(const int& h_n) { h_n_ = h_n; } // Establece la heurística del nodo
  void SetGN(const int& g_n) { g_n_ = g_n; } // Establece el costo del camino desde el nodo actual hasta el nodo objetivo
  void SetFN(const int& f_n) { f_n_ = f_n; } // Establece el costo total del nodo
  void SetPadre(const Posicion& padre) { padre_ = padre; } // Establece el nodo padre

  // Getters
  int GetEstado() const { return estado_; } // Retorna el estado del nodo
  int GetFN() const { return f_n_; } // Retorna el costo total del nodo
  int GetGN() const { return g_n_; } // Retorna el costo del camino desde el nodo actual hasta el nodo objetivo
  int GetHN() const { return h_n_; } // Retorna la heurística del nodo
  Posicion& GetPosicion() { return posicion_; } // Retorna la posición del nodo
  Posicion& GetPadre() { return padre_; } // Retorna el nodo padre

  // Sobrecarga de operadores
  friend ostream& operator<<(ostream& os, const Nodo& nodo) {
    os << nodo.estado_ << " ";
    return os;
  }
  bool operator==(const Nodo& nodo) {
    return (posicion_ == nodo.posicion_);
  }

 private:
  int estado_; // Estado del nodo
  Posicion posicion_;
  Posicion padre_;
  int costo_camino_; // Costo del camino desde el nodo raíz hasta el nodo actual
  int h_n_; // Heurística del nodo
  int g_n_ = 0; // Costo del camino desde el nodo actual hasta el nodo objetivo
  int f_n_; // Costo total del nodo
};