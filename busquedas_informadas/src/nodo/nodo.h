#include "../posicion/posicion.h"
#include <iostream>
#include <vector>

using namespace std;

class Nodo {
 public:
  Nodo() = default;
  Nodo(Posicion posicion, int estado) : posicion_(posicion), estado_(estado) {}

  // Getters
  Posicion GetPosicion() const { return posicion_; }
  int GetEuristica() const { return euristica_; }
  int GetCostoAcumulado() const { return costo_acumulado_; } // g(n)
  int GetCostoTotal() const { return costo_total_; } // f(n)

  // Setters
  void SetCostoAcumulado(int costo_acumulado) { costo_acumulado_ = costo_acumulado; } // g(n)
  void SetCostoTotal(int costo_total) { costo_total_ = costo_total; } // f(n)

 private:
  Posicion posicion_;
  int estado_;
  int euristica_; // h(n)
  int costo_acumulado_; // g(n)
  int costo_total_; // f(n)
  vector<int> hijos_;
};