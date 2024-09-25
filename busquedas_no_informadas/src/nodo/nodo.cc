#include "nodo.h"

/**
 * @brief Constructor de la clase nodo
 * @param padre Nodo padre
 * @param hijo Nodo hijo
 * @param coste Coste del nodo
*/

Nodo::Nodo(const int& padre, const int& hijo, const double& coste) {
  padre_ = padre;
  hijo_ = hijo;
  coste_ = coste;
}

/**
 * @overload Sobrecarga del operador <<
*/

ostream& operator<<(ostream& os, const Nodo& nodo) {
  os << "(" << nodo.padre_ << ", " << nodo.hijo_ << ") " << nodo.coste_ << endl;
  return os;
}