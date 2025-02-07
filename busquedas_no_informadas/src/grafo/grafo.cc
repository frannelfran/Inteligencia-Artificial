#include "grafo.h"

/**
 * @brief Constructor de la clase Grafo
 * @param matriz Matriz de costes
 * @param raiz Nodo raíz
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
 * @brief Función que realiza un recorrido en profundidad
 * @param final Nodo final
 * @param file Fichero de salida
*/

void Grafo::RecorridoProfundidad(Nodo& final, ofstream& file) {
  stack<Nodo*> pila;
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

  // Añadimos el nodo inicial a la pila
  pila.push(raiz_);

  while (!pila.empty()) {
    Nodo* actual = pila.top();
    pila.pop();
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
    vector<pair<int, double>> hijos = grafo_[actual->GetId()];
    
    for (auto it = hijos.rbegin(); it != hijos.rend(); it++) {
      pair<int, double> hijos = *it; // Hijos del nodo actual

      Nodo* hijo = new Nodo(hijos.first);
      hijo->SetPadre(actual);
      if (!EstaEnRama(hijo, actual) || find(visitados.begin(), visitados.end(), hijo->GetId()) == visitados.end()) {
        pila.push(hijo);
        generados.push_back(hijo->GetId());
      }
    }
    MostrarIteracion(++iteracion, generados, visitados, file);
  }
  cout << "No se ha encontrado el nodo final" << endl;
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

  cout << "No se ha encontrado el nodo final" << endl;
}

/**
 * @brief Función que muestra el camino desde el nodo inicial hasta el nodo final
 * @param nodo Nodo final
 * @param file Fichero de salida
*/

void Grafo::MostrarCamino(Nodo* nodo, ofstream& file) {
  vector<Nodo*> camino;
  Nodo* aux = nodo;
  while (aux != nullptr) {
    camino.push_back(aux);
    aux = aux->GetPadre();
  }
  file << "Camino: ";
  for (int i = camino.size() - 1; i >= 0; i--) {
    file << camino[i]->GetId() << " ";
    if (i != 0) {
      file << "-> ";
    }
  }
  file << endl;
}

/**
 * @brief Función que calcula el coste total de un camino
 * @param nodo Nodo final
 * @return Coste total
*/

double Grafo::CalcularCosteTotal(Nodo* nodo) {
  vector<Nodo*> camino;
  Nodo* aux = nodo;
  double coste_total = 0.0;

  while (aux != nullptr) {
    camino.push_back(aux);
    aux = aux->GetPadre();
  }

  for (int i = camino.size() - 1; i > 0; i--) {
    for (auto& hijo : grafo_[camino[i]->GetId()]) {
      if (hijo.first == camino[i - 1]->GetId()) {
        coste_total += hijo.second;
      }
    }
  }
  return coste_total;
}

/**
 * @brief Función que comprueba si un nodo está en otra rama
 * @param hijo Nodo a comprobar
 * @param nodo Nodo actual
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