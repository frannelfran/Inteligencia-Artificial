#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iterator>
#include <optional>
#include <string_view>
#include <cassert>

using namespace std;

struct Options {
  string file_in;
  string file_out;
  int nodo_origen;
  int nodo_destino;
  int opcion;
};

optional<Options> parse_args(int argc, char* argv[]); // Parsea los argumentos de la línea de comandos

vector<vector<double>> ConstruirMatrizCoste(ifstream&); // Construye la matriz de coste a partir del fichero de entrada
void MostrarMatriz(const vector<vector<double>>&); // Muestra la matriz de coste