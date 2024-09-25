#include "arbol.h"

/**
 * @brief Constructor de la clase arbol
 * @param file Fichero con los datos del arbol
*/

Arbol::Arbol(ifstream& file) {
  int num_nodos, save_num_nodos, nodo_padre = 1, nodo_hijo = 2;
  double coste;
  file >> num_nodos;
  save_num_nodos = num_nodos; // Guardo el numero de nodos para poder reiniciar el contador

  while (!file.eof()) {
    while (num_nodos--) {
      file >> coste;
      if (coste > -1) {
        Nodo nodo(nodo_padre, nodo_hijo, coste);
        if (!ExisteNodo(nodo)) {
          InsertarNodo(nodo);
        }
        else {
          cout << "El nodo ya existe" << endl;
        }
      }
      nodo_hijo++;
    }
    nodo_padre++;
    save_num_nodos = num_nodos;
  }
}

/**
 * @brief Comprueba si un nodo existe en el arbol
 * @param nodo Nodo a comprobar
 * @return true si el nodo existe, false en caso contrario
*/

bool Arbol::ExisteNodo(const Nodo& nodo) const {
  auto it = arbol_.find(nodo.GetPadre());
  while (it != arbol_.end()) {
    if (it->second.GetHijo() == nodo.GetPadre()) {
      return true;
    }
  }
  return false;
}

/**
 * @overload Sobrecarga del operador <<
*/

ostream& operator<<(ostream& os, const Arbol& arbol) {
  for (auto it = arbol.arbol_.begin(); it != arbol.arbol_.end(); ++it) {
    os << it->first << " -> ";
    os << it->second;
  }
  return os;
}