#include "nodo/nodo.h"
#include "arista/arista.h"
#include "arbol/arbol.h"
#include "tools/tools.h"

int main(int argc, char* argv[]) {
  auto options = parse_args(argc, argv);
  
  ifstream file(options->file_in);
  ofstream file_out(options->file_out);
  int nodo_origen = options->nodo_origen;
  int nodo_destino = options->nodo_destino;

  vector<vector<double>> matriz_coste = ConstruirMatrizCoste(file); // Construimos la matriz de coste a partir del fichero
  Arbol arbol(matriz_coste); // Creamos el árbol

  if (!file.is_open()) { // Comprobamos que el fichero se pudo abrir correctamente
    cout << "No se pudo abrir el fichero" << endl;
    return EXIT_FAILURE;
  }
  cout << "Opción 1: Algortimo de búsqueda en profundidad (DFS)" << endl;
  cout << "Opción 2: Algortimo de búsqueda en amplitud (BFS)" << endl;
  cout << "Opción 3: Mostrar árbol" << endl;
  int opcion;
  do {
    cout << "Introducir opción: ";
    cin >> opcion;
    if (opcion == 1) arbol.DFS(nodo_origen, nodo_destino, file_out); // Busqueda en profundidad
    else if (opcion == 2) arbol.BFS(nodo_origen, nodo_destino, file_out); // Busqueda en amplitud
    else if (opcion == 3) cout << arbol; // Mostrar árbol
    else if (opcion == 4) break; // Salir
    else {
      cout << "Opción no válida" << endl;
      break; // Volver a pedir la opción si no es válida
    }
  } while (opcion == 1 || opcion == 2 || opcion == 3);
  // Cerramos ficheros y eliminamos el árbol
  file.close();
  file_out.close();
  return 0;
}