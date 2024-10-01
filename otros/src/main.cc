#include "nodo/nodo.h"
#include "arista/arista.h"
#include "arbol/arbol.h"
#include "tools/tools.h"

int main(int argc, char* argv[]) {
  ifstream file_in(argv[1]);
  ofstream file_out("salida.txt");
  vector<vector<double>> matriz_coste = ConstruirMatrizCoste(file_in);
  Arbol arbol(matriz_coste);
  cout << arbol;
  arbol.DFS(1, 5, file_out);
  









  cout << "Hello, World!" << endl;
  return 0;







}