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
      if (nodo_hijo > save_num_nodos) break;
      if (nodo_padre == nodo_hijo) nodo_hijo++;

      file >> coste;
      if (coste >= 0) {
        Nodo nodo(nodo_padre, nodo_hijo, coste); // Creo un nodo con el padre y el hijo
        InsertarNodo(nodo);
      }
      nodo_hijo++;
    }
    nodo_padre++;
    nodo_hijo = nodo_padre + 1;
    num_nodos = save_num_nodos;
  }
  cout << arbol_.size() << endl;
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