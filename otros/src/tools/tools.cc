#include "tools.h"

/**
 * @brief Construye una matriz de costes a partir de un fichero de entrada
 * @param file Fichero de entrada
 * @return Matriz de costes
*/

vector<vector<double>> ConstruirMatrizCoste(ifstream& file) {
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

/**
 * @brief Muestra una matriz por pantalla
 * @param matriz Matriz a mostrar
*/

void MostrarMatriz(const vector<vector<double>>& matriz) {
  for (int i = 0; i < matriz.size(); i++) {
    for (int j = 0; j < matriz.size(); j++) {
      cout << matriz[i][j] << " ";
    }
    cout << endl;
  }
}