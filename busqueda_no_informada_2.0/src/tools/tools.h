#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Tools {
  string fichero_entrada;
  string fichero_salida;
  int NodoInicial;
  int NodoFinal;
};

vector<vector<double>> MatrizCoste(ifstream& file) {
  double coste;
  int num_nodos;
  file >> num_nodos;
  vector<vector<double>> matriz(num_nodos, vector<double>(num_nodos, 0));
  for (int i = 0; i < num_nodos; i++) {
    for (int j = i + 1; j < num_nodos; j++) {
      file >> coste;
      if (coste != -1) {
        matriz[i][j] = coste;
        matriz[j][i] = coste;
      }
    }
  }
  return matriz;
}

Tools parse_args(int argc, char* argv[]) {
  if (argc != 5) {
    cout << "Uso: ./busqueda_no_informada <fichero_entrada> <fichero_salida> <nodo_inicial> <nodo_final>" << endl;
    exit(1);
  }

  Tools tools;
  tools.fichero_entrada = argv[1];
  tools.fichero_salida = argv[2];
  tools.NodoInicial = stoi(argv[3]);
  tools.NodoFinal = stoi(argv[4]);
}