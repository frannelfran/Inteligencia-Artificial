#include "Nodo/nodo.h"
#include <fstream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Pruebe --help para mas información" << endl;
    return 1;
  }
  else if (string(argv[1]) == "--help") {
    cout << "Modo de uso: " << argv[0] << " " << "<fichero>" << endl;
    return EXIT_SUCCESS;
  }









}