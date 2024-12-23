#include "src/nodo/nodo.h"
#include "src/grafo/grafo.h"
#include "src/tools/tools.h"

int main(int argc, char* argv[]) {
  Tools options = parse_args(argc, argv);

  // Fichero de entrada, salida
  ifstream input(options.fichero_entrada);
  ofstream output(options.fichero_salida);

  // Matriz de costes
  vector<vector<double>> matriz = MatrizCoste(input);

  // Creación del grafo
  Grafo grafo(matriz);

  int opcion;

  while (true) {
    cout << "1. Recorrido en profundidad" << endl;
    cout << "2. Recorrido en amplitud" << endl;
    cout << "3. Cambiar nodos inicial y final" << endl;
    cout << "4. Salir" << endl;
    cout << "Introducir opción: ";
    cin >> opcion;

    switch (opcion) {
      case 1: {
        Nodo inicial(options.NodoInicial);
        Nodo final(options.NodoFinal);
        grafo.RecorridoProfundidad(inicial, final, output);
        cout << "Comprobar fichero de salida" << endl;
        break;
      }
      case 2:
        return 0;
      case 3:
        cout << "Introducir nodo inicial: ";
        cin >> options.NodoInicial;
        cout << "Introducir nodo final: ";
        cin >> options.NodoFinal;
        break;
      case 4:
        return 0;
      default:
        cout << "Opción no válida" << endl;

    }
  }
  
  // Cerramos ficheros
  input.close();
  output.close();
}