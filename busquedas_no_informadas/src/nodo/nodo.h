#pragma once
#include <iostream>

using namespace std;

class Nodo {
 public:
  Nodo() = default;
  Nodo(const int& padre, const int& hijo, const double& coste); // Constructor de la clase nodo

  // Getters
  int GetPadre() const { return padre_; }
  int GetHijo() const { return hijo_; }
  double GetCoste() const { return coste_; }

  friend ostream& operator<<(ostream& os, const Nodo& nodo);

 private:
  int padre_;
  int hijo_;
  double coste_;
};