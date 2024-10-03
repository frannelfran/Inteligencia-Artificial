#include <iostream>

using namespace std;

class Posicion {
 public:
  // Constructores 
  Posicion() = default;
  Posicion(int x, int y) : x_(x), y_(y) {}

  // Getters
  int GetX() const { return x_; }
  int GetY() const { return y_; }

  // Sobrecarga de operadores
  friend ostream& operator<(ostream& os, const Posicion& posicion) {
    os << "(" << posicion.x_ << ", " << posicion.y_ << ")";
    return os;
  }

 private:
  int x_;
  int y_;
};