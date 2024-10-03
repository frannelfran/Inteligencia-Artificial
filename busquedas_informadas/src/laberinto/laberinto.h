#include "../nodo/nodo.h"
#include <iostream>
#include <vector>
#include <fstream>

class Laberinto {
 public:
  // Constructores
  Laberinto() = default;
  Laberinto(ifstream&);

  pair<int, int> BuscarEntradaSalida(ifstream&);

  // Sobrecarga de operadores
  friend ostream& operator<<(ostream&, const Laberinto&);

 private:
  vector<vector<Nodo>> laberinto_;
};