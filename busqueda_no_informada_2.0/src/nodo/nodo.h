#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Nodo {
 public:
  // Constructor
  Nodo() = default;
  Nodo(const int& id) : id(id) {}

  // Destructor
  ~Nodo() = default;

  // Getters
  int GetId() const { return id; }
  vector<pair<Nodo*, double>> GetHijos() const { return hijos_; }

  // Setters
  void SetHijo(Nodo* hijo, const double& coste) { hijos_.push_back(make_pair(hijo, coste)); }

  // Sobrecarga de operadores
  friend ostream& operator<<(ostream& os, const Nodo& nodo) {
    os << nodo.id << " -> ";
    for (auto& hijo : nodo.hijos_) {
      os << hijo.first->GetId() << "(" << hijo.second << ") ";
    }
    return os;
  }

  bool operator<(const Nodo& nodo) const { return id < nodo.id; }
  bool operator==(const Nodo& nodo) const { return id == nodo.id; }

 private:
  int id;
  vector<pair<Nodo*, double>> hijos_;
};