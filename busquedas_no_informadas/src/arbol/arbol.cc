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
      if (coste >= 0) {
        if (nodo_padre == nodo_hijo) {
          nodo_hijo++;
        }
        Nodo nodo(nodo_padre, nodo_hijo, coste);
        if (!ExisteNodo(nodo)) {
          InsertarNodo(nodo);
        }
      }
      nodo_hijo++;
      cout << num_nodos << endl;
    }
    nodo_padre++;
    nodo_hijo = 1;
    num_nodos = save_num_nodos;
  }
}

/**
 * @brief Comprueba si un nodo existe en el arbol
 * @param nodo Nodo a comprobar
 * @return true si el nodo existe, false en caso contrario
*/

bool Arbol::ExisteNodo(const Nodo& nodo) const {
  // Comprobar si hay una arista en la dirección (padre, hijo)
  auto rangePadreHijo = arbol_.equal_range(nodo.GetPadre());
  for (auto it = rangePadreHijo.first; it != rangePadreHijo.second; ++it) {
    if (it->second.GetHijo() == nodo.GetHijo()) {
      return true; // Arista (padre, hijo) ya existe
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