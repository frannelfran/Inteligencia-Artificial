#include "src/nodo/nodo.h"
#include "src/grafo/grafo.h"
#include "src/tools/tools.h"

int main(int argc, char* argv[]) {
  Tools options = parse_args(argc, argv);

  // Fichero de entrada, salida y nodos inicial y final
  ifstream file(options.fichero_entrada);
  ofstream output(options.fichero_salida);
  Nodo inicial(options.NodoInicial);
  Nodo final(options.NodoFinal);

  // Matriz de costes
  vector<vector<double>> matriz = MatrizCoste(file);
  // Creación del grafo
  Grafo grafo(matriz);

  int opcion;

  while (true) {
    cout << "1. Recorrido en profundidad" << endl;
    cout << "2. Salir" << endl;
    cout << "Introducir opción: ";
    cin >> opcion;

    switch (opcion) {
      case 1:
        grafo.RecorridoProfundidad(inicial, final);
        break;
      case 2:
        return 0;
      default:
        cout << "Opción no válida" << endl;

    }
  }
}