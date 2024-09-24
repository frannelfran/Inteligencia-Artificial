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
  int num_nodos, nodo_inicial = 1;
  double coste;
  while (file.eof()) {
    file >> num_nodos;
    while (num_nodos--) {
      file >> coste;
      if (coste == -1) continue; // Ingnorar los nodos que tengan coste -1
      Nodo nodo(nodo_inicial, nodo_inicial + 1, coste);
      
    }
  }










}