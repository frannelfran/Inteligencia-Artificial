#include "laberinto/laberinto.h"
#include "nodo/nodo.h"
#include "posicion/posicion.h"

int main(int argc, char* argv[]) {
  ifstream file(argv[1]);
  Laberinto lab(file);
  cout << lab << endl;
  lab.CambiarEntradaSalida(Posicion(10, 0), Posicion(0, 1));
  cout << lab;

  return 0;
}