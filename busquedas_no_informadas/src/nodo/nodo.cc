#include "nodo.h"

/**
 * @brief Constructor de la clase nodo
 * @param padre Nodo padre
 * @param hijo Nodo hijo
 * @param coste Coste del nodo
*/

Nodo::Nodo(const int& padre, const int& hijo, const double& coste) {
  nodo_.insert({padre, hijo});
  coste_ = coste;
}

/**
 * @overload Sobrecarga del operador <<
*/

ostream& operator<<(ostream& os, const Nodo& nodo) {
  for (auto it = nodo.nodo_.begin(); it != nodo.nodo_.end(); it++) {
    os << "(" << it->first << ", " << it->second << ") " << nodo.coste_ << endl;
  }
  return os;
}