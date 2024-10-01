#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Nodo {
 public:
  Nodo() = default;
  Nodo(const int& id) : id_(id) {}

  // Getters
  int GetId() const { return id_; }
  vector<int> GetHijos() const { return hijos_; }

  // Setters
  void AddHijo(const int& hijo) { hijos_.push_back(hijo); }

  // Sobrecarga de operadores
  bool operator<(const Nodo& nodo) const { return id_ < nodo.id_; }

 private:
  int id_; // Identificador del nodo
  vector<int> hijos_; // Hijos del nodo
};