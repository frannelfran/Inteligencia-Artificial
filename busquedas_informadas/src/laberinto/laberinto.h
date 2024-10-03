#include "../nodo/nodo.h"
#include <iostream>
#include <vector>
#include <fstream>

class Laberinto {
 public:
  // Constructores
  Laberinto() = default;
  Laberinto(ifstream&);

 private:
  vector<vector<Nodo>> laberinto_;
};