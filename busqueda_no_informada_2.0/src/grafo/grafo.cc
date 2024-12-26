#include "grafo.h"

/**
 * @brief Constructor de la clase Grafo
 * @param matriz Matriz de costes
*/

Grafo::Grafo(const vector<vector<double>>& matriz, const Nodo& raiz) {
  this->raiz_ = new Nodo(raiz.GetId());

  for (int i = 0; i < matriz.size(); i++) {
    vector<pair<int, double>> hijos;
    for (int j = 0; j < matriz[i].size(); j++) {
      if (matriz[i][j] != 0) {
        hijos.push_back({j + 1, matriz[i][j]});
      }
    }
    grafo_.insert({i + 1, hijos});
  }

  num_nodos_ = grafo_.size();
  // Calculamos las aristas
  for (auto& nodo : grafo_) {
    num_aristas_ += nodo.second.size();
  }
  num_aristas_ /= 2;
}

/**
 * @brief Función que muestra la iteración actual
 * @param iteracion Número de iteración
 * @param generados Nodos generados
 * @param inspeccionados Nodos inspeccionados
*/

void Grafo::MostrarIteracion(const int& iteracion, const vector<int>& generados, const vector<int>& inspeccionados, ofstream& file) const {
  file << "Iteración " << iteracion << endl;
  file << "Generados: ";
  for (auto id : generados) {
    file << id << " ";
  }
  file << "\nInspeccionados: ";
  for (auto id : inspeccionados) {
    file << id << " ";
  }
  file << "\n---------------------------------------------" << endl;
}

/**
 * @brief Función que realiza un recorrido en amplitud
 * @param inicial Nodo inicial
 * @param final Nodo final
 * @param file Fichero de salida
*/

void Grafo::RecorridoAmplitud(Nodo& final, ofstream& file) {
  queue<Nodo*> cola;
  vector<int> generados;
  vector<int> visitados;
  int iteracion = 1;

  // Muestro la información inicial
  file << "Número de nodos: " << num_nodos_ << endl;
  file << "Número de aristas: " << num_aristas_ << endl;
  file << "Vértice origen: " << raiz_->GetId() << endl;
  file << "Vértice destino: " << final.GetId() << endl;
  file << "---------------------------------------------" << endl;
  // Iteracción inicial
  file << "Iteración " << iteracion << endl;
  file << "Generados: " << raiz_->GetId() << endl;
  file << "Inspeccionados: -" << endl;
  file << "---------------------------------------------" << endl;

  // Añadimos el nodo inicial a la cola
  cola.push(raiz_);
  
  while (!cola.empty()) {
    Nodo* actual = cola.front();
    cola.pop();
    // Visito el nodo actual
    visitados.push_back(actual->GetId());

    // Compruebo si es el nodo final
    if (actual->GetId() == final.GetId()) {
      generados.push_back(actual->GetId());
      MostrarIteracion(++iteracion, generados, visitados, file);
      // Muestro el camino
      MostrarCamino(actual, file);
      
      // Calculo el coste total
      file << "Coste total: " << CalcularCosteTotal(actual) << endl;
      return;
    }

    // Para cada hijo del nodo actual
    for (auto& hijos : grafo_[actual->GetId()]) {
      Nodo* hijo = new Nodo(hijos.first);
      hijo->SetPadre(actual);
      if (!EstaEnRama(hijo, actual) || find(visitados.begin(), visitados.end(), hijo->GetId()) == visitados.end()) {
        cola.push(hijo);
        generados.push_back(hijo->GetId());
      }
    }
    MostrarIteracion(++iteracion, generados, visitados, file);
  }
}

/**
 * @brief Función que muestra el camino desde el nodo inicial hasta el nodo final
 * @param nodo Nodo final
 * @param file Fichero de salida
*/

void Grafo::MostrarCamino(Nodo* nodo, ofstream& file) {
  stack<Nodo*> camino;
  Nodo* aux = nodo;
  while (aux != nullptr) {
    camino.push(aux);
    aux = aux->GetPadre();
  }
  file << "Camino: ";
  while (!camino.empty()) {
    if (camino.size() == 1) {
      file << camino.top()->GetId();
    } else {
      file << camino.top()->GetId() << " -> ";
    }
    camino.pop();
  }
  file << endl;
}

/**
 * @brief Función que calcula el coste total de un camino
 * @param nodo Nodo final
 * @return Coste total
*/

double Grafo::CalcularCosteTotal(Nodo* nodo) {
  stack<Nodo*> camino;
  Nodo* aux = nodo;
  double coste_total = 0.0;

  while (aux != nullptr) {
    camino.push(aux);
    aux = aux->GetPadre();
  }

  while (!camino.empty()) {
    Nodo* actual = camino.top();
    camino.pop();
    // Si hay un nodo padre, buscar el coste de la conexión
    if (!camino.empty()) {
      Nodo* siguiente = camino.top(); // El siguiente nodo en el camino
      for (const auto& hijo : grafo_[actual->GetId()]) {
        if (hijo.first == siguiente->GetId()) {
          coste_total += hijo.second; // Sumar el coste de la conexión
          break;
        }
      }
    }
  }
  return coste_total;
}

/**
 * @brief Función que comprueba si un nodo está en otra rama
 * @param nodo Nodo a comprobar
 * @param padre Nodo padre
 * @param camino Camino recorrido
 * @return true si está en otra rama, false en caso contrario
*/

bool Grafo::EstaEnRama(Nodo* hijo, Nodo* nodo) {
  while (nodo != nullptr) {
    if (hijo->GetId() == nodo->GetId()) {
      return true;
    }
    nodo = nodo->GetPadre();
  }
  return false;
}