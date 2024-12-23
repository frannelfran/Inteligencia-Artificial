#include "src/nodo/nodo.h"
#include "src/grafo/grafo.h"
#include "src/tools/tools.h"

int main(int argc, char* argv[]) {
  Tools options = parse_args(argc, argv);

  // Fichero de entrada, salida
  ifstream input(options.fichero_entrada);
  ofstream output(options.fichero_salida);
  Nodo inicial(options.NodoInicial);
  Nodo final(options.NodoFinal);

  // Matriz de costes
  vector<vector<double>> matriz = MatrizCoste(input);

  // Creación del grafo
  Grafo grafo(matriz);

  int opcion;

  while (true) {
    cout << "--- Menú ---" << endl;
    cout << "1. Recorrido en profundidad" << endl;
    cout << "2. Recorrido en amplitud" << endl;
    cout << "3. Cambiar nodos inicial y final" << endl;
    cout << "4. Mostrar grafo" << endl;
    cout << "5. Salir" << endl;
    cout << "Introducir opción: ";
    cin >> opcion;

    switch (opcion) {
      case 1:
        grafo.RecorridoProfundidad(inicial, final, output);
        break;
      case 2:
        grafo.RecorridoAmplitud(inicial, final, output);
        break;
      case 3:
        cout << "Introducir nodo inicial: ";
        cin >> options.NodoInicial;
        inicial = Nodo(options.NodoInicial); // Establezco el nuevo nodo inicial
        cout << "Introducir nodo final: ";
        cin >> options.NodoFinal;
        final = Nodo(options.NodoFinal); // Establezco el nuevo nodo final
        break;
      case 4:
        cout << grafo;
        break;
      case 5:
        return 0;
      default:
        cout << "Opción no válida" << endl;
    }
  }
  
  // Cerramos ficheros
  input.close();
  output.close();
}