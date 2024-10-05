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

ostream& operator<<(ostream& os, const Laberinto& laberinto) {
  for (int i = 0; i < laberinto.laberinto_.size(); i++) {
    for (int j = 0; j < laberinto.laberinto_[i].size(); j++) {
      os << laberinto.laberinto_[i][j] << " ";
    }
    os << endl;
  }
  return os;
}