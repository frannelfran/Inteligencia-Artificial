#include "laberinto.h"

/**
 * @brief Constructor de la clase Laberinto
 * @param file Archivo de entrada
*/

Laberinto::Laberinto(ifstream& file) {
  int filas, columnas, estado;
  file >> filas >> columnas;

  laberinto_.resize(filas, vector<Nodo>(columnas));
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      file >> estado;
      laberinto_[i][j] = Nodo(Posicion(i, j), estado);
      if (estado == 3) this->entrada_ = laberinto_[i][j].GetPosicion();
      else if (estado == 4) this->salida_ = laberinto_[i][j].GetPosicion();
    }
  }
  EstablecerHeuristica(); // Establecer la heurística de los nodos
}

/**
 * @brief Establece la heurística de los nodos del laberinto
*/

void Laberinto::EstablecerHeuristica() {
  for (int i = 0; i < laberinto_.size(); i++) {
    for (int j = 0; j < laberinto_[i].size(); j++) {
      if (laberinto_[i][j].GetEstado() == 0 || laberinto_[i][j].GetEstado() == 3 || laberinto_[i][j].GetEstado() == 4) {
        laberinto_[i][j].SetHX((abs(salida_.GetX() - i) + abs(salida_.GetY() - j)) * 3);
      }
    }
  }
}

/**
 * @brief Cambia la entrada y salida del laberinto
 * @param entrada Nueva posición de la entrada
 * @param salida Nueva posición de la salida
*/

void Laberinto::CambiarEntradaSalida(const Posicion& entrada, const Posicion& salida) {
  // Compruebo que las posiciones sean válidas
  if (entrada.GetX() < 0 || entrada.GetX() > laberinto_.size() || entrada.GetY() < 0 || entrada.GetY() > laberinto_[0].size()) {
    cout << "Posición de entrada inválida: Fuera de rango" << endl;
    return;
  }
  // Establezco como 1 la entrada y salida anteriores
  laberinto_[entrada_.GetX()][entrada_.GetY()].SetEstado(1);
  laberinto_[salida_.GetX()][salida_.GetY()].SetEstado(1);
  // Establezco la nueva entrada y salida
  laberinto_[entrada.GetX()][entrada.GetY()].SetEstado(3);
  laberinto_[salida.GetX()][salida.GetY()].SetEstado(4);
  // Actualizo la entrada y salida
  this->entrada_ = entrada;
  this->salida_ = salida;
  // Establezco la heurística de los nodos
  EstablecerHeuristica();
}

/**
 * @brief Realiza la búsqueda A* en el laberinto
*/

void Laberinto::BusquedaAEstrella() {

  Nodo inicial = laberinto_[entrada_.GetX()][entrada_.GetY()]; // Nodo inicial
  Nodo objetivo = laberinto_[salida_.GetX()][salida_.GetY()]; // Nodo objetivo
  list<Nodo> abierta; // Lista de nodos visitados
  list<Nodo> cerrada; // Lista de nodos no visitados
  Nodo actual;
  abierta.push_back(inicial);
  while (!abierta.empty()) {
    // Obtenemos el nodo actual a partir del nodo con costo de f(x) más bajo
    actual = abierta.front();
    for (auto nodo : abierta) {
      if (nodo.GetFX() < actual.GetFX()) {
        actual = nodo;
      }
    }
    // Eliminamos el nodo actual de la lista abierta y lo agregamos a la cerrada
    abierta.remove(actual), cerrada.push_back(actual);
    // Comprobamos si el nodo actual es el objetivo
    if (actual.GetPosicion() == objetivo.GetPosicion()) { // Si el nodo actual es el objetivo almacenamos el camino optimo
      for (auto nodo : cerrada) {
        cout << nodo.GetPosicion() << " ";
      }
      cout << endl;
      break;
    }
    // Obtenemos los nodos adyacentes al nodo actual y los almacenamos en una lista
    









  }








}

ostream& operator<<(ostream& os, const Laberinto& laberinto) {
  for (int i = 0; i < laberinto.laberinto_.size(); i++) {
    for (int j = 0; j < laberinto.laberinto_[i].size(); j++) {
      os << laberinto.laberinto_[i][j] << " ";
    }
    os << endl;
  }
  return os;
}