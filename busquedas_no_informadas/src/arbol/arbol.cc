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
    cout << "Nodo padre: " << nodo_padre << endl;
    while (num_nodos--) {
      file >> coste;
      if (coste > -1) {
        Nodo nodo(nodo_padre, nodo_hijo, coste);
        if (!ExisteNodo(nodo)) {
          InsertarNodo(nodo);
        }
      }
      nodo_hijo++;
    }
    nodo_padre++;
    save_num_nodos = num_nodos;
  }
}