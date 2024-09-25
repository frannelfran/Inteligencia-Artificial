#include "nodo/nodo.h"
#include "arbol/arbol.h"

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
  Arbol arbol(file);
  return EXIT_SUCCESS;










}