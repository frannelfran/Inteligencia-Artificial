#pragma once
#include <iostream>

using namespace std;

class Arista {
 public:
  Arista() = default;
  Arista(const int& origen, const int& destino, const double& coste) : origen_(origen), destino_(destino), coste_(coste) {}

  // Getters
  int GetOrigen() const { return origen_; }
  int GetDestino() const { return destino_; }
  double GetCoste() const { return coste_;}

 private:
  int origen_;
  int destino_;
  double coste_;
};