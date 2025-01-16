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
  Grafo grafo(matriz, inicial);

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
        grafo.RecorridoProfundidad(final, output);
        cout << "Consultar fichero de salida" << endl;
        break;
      case 2:
        grafo.RecorridoAmplitud(final, output);
        cout << "Consultar fichero de salida" << endl;
        break;
      case 3:
        cout << "Introducir nodo inicial: ";
        cin >> options.NodoInicial;
        inicial = Nodo(options.NodoInicial); // Establezco el nuevo nodo inicial
        grafo.CambiarRaiz(inicial); // Cambio la raíz del grafo
        cout << "Introducir nodo final: ";
        cin >> options.NodoFinal;
        final = Nodo(options.NodoFinal); // Establezco el nuevo nodo final
        break;
      case 4:
        cout << grafo;
        break;
      case 5:
        // Cerramos ficheros
        input.close();
        output.close();
        return 0;
      default:
        cout << "Opción no válida" << endl;
    }
  }
}