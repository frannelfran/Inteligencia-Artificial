#pragma once
#include <iostream>
#include <vector>

using namespace std;

class Nodo {
 public:
  // Constructor
  Nodo() = default;
  Nodo(const int& id) : id(id), padre_(nullptr) {}

  // Destructor
  ~Nodo() = default;

  // Getters
  int GetId() const { return id; }
  Nodo* GetPadre() const { return padre_; }

  // Setters
  void SetPadre(Nodo* padre) { padre_ = padre; }

  bool operator<(const Nodo& nodo) const { return id < nodo.id; }
  bool operator==(const Nodo& nodo) const { return id == nodo.id; }

 private:
  int id;
  Nodo* padre_;
};