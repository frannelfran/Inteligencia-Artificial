#include "laberinto.h"

/**
 * @brief Constructor de la clase Laberinto
 * @param file Archivo de entrada
*/

Laberinto::Laberinto(ifstream& file) {
  int filas, columnas, estado;
  file >> filas >> columnas;

  // Establecer las filas y columnas del laberinto
  this->filas_ = filas;
  this->columnas_ = columnas;

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
      if (laberinto_[i][j].GetEstado() == '0' || laberinto_[i][j].GetEstado() == '3' || laberinto_[i][j].GetEstado() == '4') {
        laberinto_[i][j].SetHN((abs(salida_.GetX() - i) + abs(salida_.GetY() - j)) * 3);
      }
    }
  }
}

/**
 * @brief Cambia la entrada y salida del laberinto
 * @param entrada Nueva posición de la entrada
*/

void Laberinto::CambiarEntrada(const Posicion& entrada) {
  // Compruebo que las posiciones sean válidas
  if (!EsPosicionValida(entrada)) {
    cout << "Posición de entrada inválida: Fuera de rango" << endl;
    return;
  }
  // Establezco como 1 la entrada anterior
  laberinto_[entrada_.GetX()][entrada_.GetY()].SetEstado('1');
  // Establezco la nueva entrada
  laberinto_[entrada.GetX()][entrada.GetY()].SetEstado('3');
  // Actualizo la entrada
  this->entrada_ = entrada;
  // Establezco la heurística de los nodos
  EstablecerHeuristica();
}

/**
 * @brief Cambia la salida del laberinto
 * @param salida Nueva posición de la salida
*/

void Laberinto::CambiarSalida(const Posicion& salida) {
  // Compruebo que las posiciones sean válidas
  if (!EsPosicionValida(salida)) {
    cout << "Posición de salida inválida: Fuera de rango" << endl;
    return;
  }
  // Establezco como 1 la salida anterior
  laberinto_[salida_.GetX()][salida_.GetY()].SetEstado('1');
  // Establezco la nueva salida
  laberinto_[salida.GetX()][salida.GetY()].SetEstado('4');
  // Actualizo la salida
  this->salida_ = salida;
  // Establezco la heurística de los nodos
  EstablecerHeuristica();
}

/**
 * @brief Resetea los valores de los nodos del laberinto
*/

void Laberinto::ResetearValores() {
  for (int i = 0; i < laberinto_.size(); i++) {
    for (int j = 0; j < laberinto_[i].size(); j++) {
      laberinto_[i][j].SetFN(0);
      laberinto_[i][j].SetGN(0);
      if (laberinto_[i][j].GetEstado() == 'x') laberinto_[i][j].SetEstado('0');
    }
  }
}

/**
 * @brief Realiza la búsqueda A* en el laberinto
 * @param file_out Archivo de salida
*/

void Laberinto::BusquedaAEstrella(ofstream& file_out) {
  int iteracion = 1;
  Nodo inicial = laberinto_[entrada_.GetX()][entrada_.GetY()]; // Nodo inicial
  Nodo objetivo = laberinto_[salida_.GetX()][salida_.GetY()]; // Nodo objetivo
  list<Nodo> abierta; // Lista de nodos por inspeccionar
  list<Nodo> cerrada; // Lista de nodos inspeccionados
  list<Nodo> vecinos; // Vecinos de cada nodo
  list<Nodo> generados; // Nodos generados

  Nodo actual;
  abierta.push_back(inicial);
  while (!abierta.empty()) {
    // Obtenemos el nodo actual a partir del nodo con costo de f(x) más bajo
    actual = *min_element(abierta.begin(), abierta.end(), [](const Nodo& a, const Nodo& b) { return a.GetFN() < b.GetFN();});
    
    // Eliminamos el nodo actual de la lista abierta y lo agregamos a la cerrada
    abierta.remove(actual), cerrada.push_back(actual);

    // Comprobamos si el nodo actual es el objetivo
    if (actual.GetPosicion() == objetivo.GetPosicion()) { // Si el nodo actual es el objetivo almacenamos el camino optimo
      file_out << "Nodos generados: " << generados.size() << endl; // Muestro el número de nodos generados
      file_out << "Nodos inspeccionados: " << cerrada.size() << endl; // Muestro el número de nodos inspeccionados
      // Muestro el camino a partir de los padres de cada nodo
      MostrarCamino(file_out);
      return;
    }

    // Obtenemos los nodos adyacentes al nodo actual y los almacenamos en una lista
    vecinos = GetVecinos(actual);
    // Guardamos los nodos generados si no están ya en la lista
    for (auto& vecino : vecinos) {
      if (find(generados.begin(), generados.end(), vecino) == generados.end()) {
        generados.push_back(vecino);
      }
    }
    
    // Recorremos la lista de nodos adyacentes
    for (auto& vecino : vecinos) {
      if (find(cerrada.begin(), cerrada.end(), vecino) != cerrada.end() || vecino.GetEstado() == '1') {
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
    SetValores(abierta); // Establezco los valores calculados a los nodos del laberinto

    // Muestro la información de la iteración
    file_out << "-----------------------------------" << endl;
    file_out << "Iteración: " << iteracion++ << endl;
    file_out << "Nodo actual: " << actual.GetPosicion() << endl;
    // Muestro los nodos generados
    file_out << "Nodos generados: ";
    for (auto& nodo : generados) {
      file_out << nodo.GetPosicion() << " ";
    }
    file_out << endl;
    // Muestro los nodos inspeccionados
    file_out << "Nodos inspeccionados: ";
    for (auto& nodo : cerrada) {
      file_out << nodo.GetPosicion() << " ";
    }
    file_out << endl << "-----------------------------------" << endl;
  }
}

/**
 * @brief Muestra el camino encontrado
 * @param file_out Archivo de salida
*/

void Laberinto::MostrarCamino(ofstream& file_out) {
  vector<Nodo> camino; // Camino encontrado
  Nodo actual = laberinto_[salida_.GetX()][salida_.GetY()];
  while (actual.GetPosicion() != entrada_) {
    Posicion padre = actual.GetPadre();
    laberinto_[padre.GetX()][padre.GetY()].SetEstado('x');
    camino.push_back(actual);
    actual = laberinto_[padre.GetX()][padre.GetY()];
  }
  laberinto_[salida_.GetX()][salida_.GetY()].SetEstado('x');
  camino.push_back(actual); // Añadir el nodo inicial al camino

  // Imprimir el laberinto con el camino
  for (int i = 0; i < laberinto_.size(); i++) {
    for (int j = 0; j < laberinto_[i].size(); j++) {
      char estado = laberinto_[i][j].GetEstado();
      
      // Imprimir la 'X' en verde
      if (estado == 'x') {
        cout << "\033[31mX\033[0m "; // 'X' en rojo
      } else {
        cout << estado << " "; // Imprimir el estado original
      }
    }
    cout << endl;
  }
  // Mostrar el camino en el archivo de salida
  file_out << "Camino: ";
  for (int i = camino.size() - 1; i >= 0; i--) {
    file_out << camino[i].GetPosicion() << " ";
  }
  // Mostrar el costo total del camino
  file_out << endl << "Coste total: " << CostoTotalCamino() << endl;
  file_out << *this; // Mostrar el laberinto con el camino en el archivo de salida
}

/**
 * @brief Establece el costo total, el costo del camino y el padre de los nodos
 * @param nodos Lista de nodos
*/

void Laberinto::SetValores(const list<Nodo>& nodos) {
  for (auto& nodo : nodos) {
    Posicion pos = nodo.GetPosicion();
    laberinto_[pos.GetX()][pos.GetY()].SetPadre(nodo.GetPadre()); // Establecer el padre
    laberinto_[pos.GetX()][pos.GetY()].SetGN(nodo.GetGN()); // Establecer el costo del camino
    laberinto_[pos.GetX()][pos.GetY()].SetFN(nodo.GetFN()); // Establecer el costo total
  }
}

/**
 * @brief Retorna el costo total del camino
 * @param inicial Nodo inicial
 * @param objetivo Nodo objetivo
 * @return Costo total del camino
*/

int Laberinto::CostoTotalCamino() const {
  return laberinto_[salida_.GetX()][salida_.GetY()].GetGN();
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
  return (laberinto_[pos.GetX()][pos.GetY()].GetEstado() == '1');
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