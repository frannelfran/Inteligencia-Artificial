#pragma once
#include <iostream>

using namespace std;

class Posicion {
 public:
  // Constructores 
  Posicion() = default;
  Posicion(const int& x, const int& y) : x_(x), y_(y) {}

  // Getters
  int GetX() const { return x_; }
  int GetY() const { return y_; }

  // Sobrecarga de operadores
  friend ostream& operator<<(ostream& os, const Posicion& posicion) {
    os << "(" << posicion.x_ << ", " << posicion.y_ << ")";
    return os;
  }
  bool operator==(const Posicion& posicion) {
    return (x_ == posicion.x_ && y_ == posicion.y_);
  }

 private:
  int x_;
  int y_;
};