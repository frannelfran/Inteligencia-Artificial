#include "src/nodo/nodo.h"
#include "src/grafo/grafo.h"

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

int main(int argc, char* argv[]) {
  ifstream file(argv[1]);
  vector<vector<double>> matriz = MatrizCoste(file);

  // Crear grafo
  Grafo grafo(matriz);
  cout << grafo;
  Nodo inicial(15);
  Nodo final(1);
  grafo.RecorridoProfundidad(inicial, final);
  
  return 0;
}