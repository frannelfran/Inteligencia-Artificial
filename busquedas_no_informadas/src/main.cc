#include "nodo/nodo.h"
#include "arbol/arbol.h"
#include "options/options.h"

int main(int argc, char* argv[]) {
  auto options = parse_args(argc, argv);
  
  ifstream file(options->file_in);
  ofstream file_out(options->file_out);
  int nodo_origen = options->nodo_origen;
  int nodo_destino = options->nodo_destino;
  if (!file.is_open()) { // Comprobamos que el fichero se pudo abrir correctamente
    cout << "No se pudo abrir el fichero" << endl;
    return EXIT_FAILURE;
  }
  
  // Leemos los datos del fichero;
  Arbol arbol(file);
  cout << "Opción 1: Algortimo de busqueda en profundidad (DFS)" << endl;
  cout << "Opción 2: Algortimo de busqueda en anchura (BFS)" << endl;
  int opcion;
  cout << "Introducir opción: ";
  cin >> opcion;
  if (opcion == 1) arbol.DFS(nodo_origen, nodo_destino, file_out);
  else if (opcion == 2) cout << "Opción no implementada" << endl;
  else {
    cout << "Opción no válida" << endl;
    return EXIT_FAILURE;
  }
  // Cerramos ficheros
  file.close();
  file_out.close();
  return 0;
}