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
        laberinto_[i][j].SetHN((abs(salida_.GetX() - i) + abs(salida_.GetY() - j)) * 3);
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
  if (!EsPosicionValida(entrada) || !EsPosicionValida(salida)) {
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
  list<Nodo> vecinos; // Vecinos de cada nodo

  Nodo actual;
  abierta.push_back(inicial);
  while (!abierta.empty()) {
    // Obtenemos el nodo actual a partir del nodo con costo de f(x) más bajo
    actual = *min_element(abierta.begin(), abierta.end(), [](const Nodo& a, const Nodo& b) { return a.GetFN() < b.GetFN();});
    
    // Eliminamos el nodo actual de la lista abierta y lo agregamos a la cerrada
    abierta.remove(actual), cerrada.push_back(actual);

    // Comprobamos si el nodo actual es el objetivo
    if (actual.GetPosicion() == objetivo.GetPosicion()) { // Si el nodo actual es el objetivo almacenamos el camino optimo
      // Muestro el camino a partir de los padres de cada nodo
      MostrarCamino(cerrada);
      return;
    }

    // Obtenemos los nodos adyacentes al nodo actual y los almacenamos en una lista
    vecinos = GetVecinos(actual);
    // Recorremos la lista de nodos adyacentes
    for (auto& vecino : vecinos) {
      if (find(cerrada.begin(), cerrada.end(), vecino) != cerrada.end() || vecino.GetEstado() == 1) {
        continue;
      }

      // Calculamos el costo del camino desde el nodo inicial hasta el nodo actual
      EstablecerCostoCamino(actual, vecino); // Para la g(n)
      
      // Calculamos el costo total del nodo
      vecino.SetFN(vecino.GetGN() + vecino.GetHN());
      
      // Si encontramos la posicion en la lista abierta
      auto vecino_abierto = find(abierta.begin(), abierta.end(), vecino);
      if (vecino_abierto != abierta.end()) {
        // Si el costo del camino del nodo actual es mayor al del vecino
        if (vecino.GetGN() < vecino_abierto->GetGN()) {
          // Establecemos el nodo actual como el padre del vecino
          vecino_abierto->SetPadre(actual.GetPosicion());
          // Establecemos el costo del camino del nodo actual como el del vecino
          vecino_abierto->SetGN(vecino.GetGN());
        }
      }
      else {
        vecino.SetPadre(actual.GetPosicion());
        abierta.push_back(vecino);
      }
    }
  }
}

/**
 * @brief Muestra el camino encontrado
 * @param nodo Nodo objetivo
*/

void Laberinto::MostrarCamino(const list<Nodo>& camino) {
  for (auto& nodo : camino) {
    laberinto_[nodo.GetPosicion().GetX()][nodo.GetPosicion().GetY()] = nodo;
  }
  Nodo actual = laberinto_[salida_.GetX()][salida_.GetY()];
  while (actual.GetPosicion() != entrada_) {
    Posicion padre = actual.GetPadre();
    laberinto_[padre.GetX()][padre.GetY()].SetEstado(2);
    actual = laberinto_[padre.GetX()][padre.GetY()];
  }
  laberinto_[salida_.GetX()][salida_.GetY()].SetEstado(2);
}

/**
 * @brief Establece el costo del camino de los nodos del laberinto
 * @param nodo Nodo a establecer el costo del camino
*/

void Laberinto::EstablecerCostoCamino(Nodo& nodo_actual, Nodo& nodo_vecino) {
  Posicion pos_actual = nodo_actual.GetPosicion();
  Posicion pos_vecino = nodo_vecino.GetPosicion();
  // Comprobamos si las posiciones son diagonales
  if (EsDiagonal(pos_actual, pos_vecino)) {
    nodo_vecino.SetGN(nodo_actual.GetGN() + diagonal_);
  } else {
    nodo_vecino.SetGN(nodo_actual.GetGN() + frontal_);
  }
}

/**
 * @brief Retorna los nodos vecinos de un nodo
 * @param nodo Nodo del que se quieren obtener los vecinosç
 * @return Lista de nodos vecinos
*/

list<Nodo> Laberinto::GetVecinos(const Nodo& nodo) const {
  list<Nodo> vecinos; // Lista de nodos vecinos
  Posicion pos = nodo.GetPosicion(); // Posición del nodo actual
  int x = pos.GetX(); // Coordenada x del nodo actual
  int y = pos.GetY(); // Coordenada y del nodo actual

  // Comprobar las posiciones adyacentes al nodo actual
  vector<Posicion> posiciones { // Todas las posibilidades
    Posicion(x - 1, y), // Arriba
    Posicion(x + 1, y), // Abajo
    Posicion(x, y - 1), // Izquierda
    Posicion(x, y + 1), // Derecha
    Posicion(x - 1, y - 1), // Arriba izquierda
    Posicion(x - 1, y + 1), // Arriba derecha
    Posicion(x + 1, y - 1), // Abajo izquierda
    Posicion(x + 1, y + 1) // Abajo derecha
  };

  for (auto& p : posiciones) {
    if (EsPosicionValida(p) && !EsPared(p)) {
      vecinos.push_back(laberinto_[p.GetX()][p.GetY()]);
    }
  }
  return vecinos;
}

/**
 * @brief Comprueba si una posición es diagonal
 * @param pos_actual Posición a comprobar
 * @param pos_vecino Posición a comprobar
 * @return true si la posición es diagonal, false en caso contrario
*/

bool Laberinto::EsDiagonal(const Posicion& pos_actual, const Posicion& pos_vecino) const {
  return (abs(pos_actual.GetX() - pos_vecino.GetX()) == abs(pos_actual.GetY() - pos_vecino.GetY()));
}

/**
 * @brief Comprueba si una posición es válida
 * @param pos Posición a comprobar
 * @return true si la posición es válida, false en caso contrario
*/

bool Laberinto::EsPosicionValida(const Posicion& pos) const {
  return (pos.GetX() >= 0 && pos.GetX() < laberinto_.size() && pos.GetY() >= 0 && pos.GetY() < laberinto_[0].size());
}

/**
 * @brief Comprueba si una posición es una pared
 * @param pos Posición a comprobar
 * @return true si la posición es una pared, false en caso contrario
*/

bool Laberinto::EsPared(const Posicion& pos) const {
  return (laberinto_[pos.GetX()][pos.GetY()].GetEstado() == 1);
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