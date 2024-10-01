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

/**
 * @brief Manejar las opciones del programa
 * @param argc Número de argumentos
 * @param argv Array donse se almacenan las opciones
 * @return Objeto Options
*/

optional<Options> parse_args(int argc, char* argv[]) {
  if (string(argv[1]) == "-h" || string(argv[1]) == "--help") { // Mostrar la ayuda
    cout << "Modo de uso: " << argv[0] << " " << "<fichero_entrada> <fichero_salida> <nodo origen> <nodo destino>" << endl;
    exit(EXIT_SUCCESS);
  }

  if (argc < 5 || argc > 5) {
    cerr << "Pruebe " << argv[0] << " -h o --help para más información" << endl;
    exit(EXIT_FAILURE);
  }

  vector<string_view> args(argv + 1, argv + argc);
  Options options;
  for (auto it = args.begin(); it != args.end(); it++) {
    options.file_in = string(*it);
    options.file_out = string(*++it);
    options.nodo_origen = stoi(string(*++it));
    options.nodo_destino = stoi(string(*++it));
  }
  return options;
}