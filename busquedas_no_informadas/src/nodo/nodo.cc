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
 * @brief Saber si un nodo ya existe
 * @param nodo Nodo a comprobar
 * @return true si el nodo ya existe, false en caso contrario
*/


/**
 * @overload Sobrecarga del operador <<
*/

ostream& operator<<(ostream& os, const Nodo& nodo) {
  os << "(" << nodo.padre_ << ", " << nodo.hijo_ << ") " << nodo.coste_ << endl;
  return os;
}