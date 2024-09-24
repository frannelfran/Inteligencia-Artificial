#include "nodo/nodo.h"
#include <fstream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Pruebe --help para mas información" << endl;
    return EXIT_FAILURE;
  }
  else if (string(argv[1]) == "--help") {
    cout << "Modo de uso: " << argv[0] << " " << "<fichero>" << endl;
    return EXIT_SUCCESS;
  }
  ifstream file(argv[1]);
  if (!file.is_open()) { // Comprobamos que el fichero se pudo abrir correctamente
    cout << "No se pudo abrir el fichero" << endl;
    return EXIT_FAILURE;
  }
  // Leemos los datos del fichero;
  int num_nodos, save_num_nodos, nodo_padre = 1, nodo_hijo = 2;
  double coste;
  file >> num_nodos;
  save_num_nodos = num_nodos; // Guardo el numero de nodos para poder reiniciar el contador

  while (!file.eof()) {
    cout << "Nodo padre: " << nodo_padre << endl;
    while (num_nodos--) {
      file >> coste;
      if (coste != -1.00) { // Ingnorar los nodos que tengan coste -1
        if (nodo_padre == nodo_hijo) {
          nodo_hijo++; 
        }
        Nodo nodo(nodo_padre, nodo_hijo, coste);
        cout << nodo;
        nodo_hijo++;
      }
    }
    nodo_padre++;
    nodo_hijo = 1;
    num_nodos = save_num_nodos;
  }










}