#include "grafo.h"

/**
 * @brief Constructor de la clase Grafo
 * @param matriz Matriz de costes
*/

Grafo::Grafo(const vector<vector<double>>& matriz) {
  vector<Nodo*> nodos;
  nodos.reserve(matriz.size());
  for (int i = 1; i < matriz.size() + 1; i++) {
    nodos.push_back(new Nodo(i));
  }
  for (int i = 0; i < matriz.size(); i++) {
    for (int j = i + 1; j < matriz[i].size(); j++) {
      if (matriz[i][j] != 0) {
        nodos[i]->SetHijo(nodos[j], matriz[i][j]);
        nodos[j]->SetHijo(nodos[i], matriz[i][j]); // Para no dirigido
      }
    }
    InsertarNodo(*nodos[i]);
  }
  num_nodos_ = nodos.size();
  num_aristas_ = grafo_.size() - 1;
}

/**
 * @brief Destructor de la clase Grafo
*/

Grafo::~Grafo() {
  set<Nodo*> nodos_a_eliminar;
  for (auto& par : grafo_) {
    for (auto& hijo : par.second) {
      if (!nodos_a_eliminar.count((hijo.first))) nodos_a_eliminar.insert(hijo.first);
    }
  }
  for (Nodo* nodo : nodos_a_eliminar) delete nodo; // Eliminamos los nodos
  grafo_.clear();
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
 * @param inicial Nodo inicial
 * @param final Nodo final
 * @param file Fichero de salida
*/

void Grafo::RecorridoProfundidad(Nodo& inicial, Nodo& final, ofstream& file) {
  stack<Nodo*> pila; // Pila para realizar el recorrido en profundidad
  set<Nodo> visitados; // Conjunto de nodos visitados
  map<int, pair<Nodo*, double>> camino; // Camino recorrido (padre y coste)
  vector<int> inspeccionados, generados = {inicial.GetId()};
  double coste_total = 0.0;
  int iteracion = 1;

  // Información inicial
  file << "Número de nodos: " << num_nodos_ << endl;
  file << "Número de aristas: " << num_aristas_ << endl;
  file << "Vertice origen: " << inicial.GetId() << endl;
  file << "Vertice destino: " << final.GetId() << endl;
  file << "---------------------------------------------" << endl;
  file << "Iteración " << iteracion << endl;
  file << "Generados: " << inicial.GetId() << endl;
  file << "Inspeccionados: -" << endl;
  file << "---------------------------------------------" << endl;

  // Para los nodos random
  // random_device rd;
  // mt19937 gen(rd());

  Nodo* nodo_inicial = nullptr;
  Nodo* nodo_final = nullptr;

  // Buscamos el nodo en el grafo
  for (auto& par : grafo_) {
    if (par.first.GetId() == inicial.GetId()) nodo_inicial = const_cast<Nodo*>(&par.first);
    if (par.first.GetId() == final.GetId()) nodo_final = const_cast<Nodo*>(&par.first);
  }

  pila.push(nodo_inicial);
  visitados.insert(inicial);

  while (!pila.empty()) {
    Nodo* actual = pila.top();
    pila.pop();
    inspeccionados.push_back(actual->GetId());

    // Si se alcanza el nodo final, reconstruimos el camino
    if (actual->GetId() == nodo_final->GetId()) {
      stack<Nodo*> camino_inverso;
      for (Nodo* nodo = nodo_final; nodo != nodo_inicial; nodo = camino[nodo->GetId()].first) {
        camino_inverso.push(nodo);
        coste_total += camino[nodo->GetId()].second;
      }
      camino_inverso.push(nodo_inicial);

      // Muestro el camino y coste total
      MostrarIteracion(++iteracion, generados, inspeccionados, file);
      file << "Camino: ";
      while (!camino_inverso.empty()) {
        file << camino_inverso.top()->GetId();
        if (camino_inverso.size() > 1) {
          file << " -> ";
        }
        camino_inverso.pop();
      }
      file << "\nCoste: " << coste_total << endl;
      cout << "Comprobar fichero de salida" << endl;
      return;
    }

    // Obtener hijos del nodo actual y procesarlos
    vector<pair<Nodo*, double>> hijos = actual->GetHijos();
    
    // shuffle(hijos.begin(), hijos.end(), gen); // escoger hijos random
    for (auto it = hijos.rbegin(); it != hijos.rend(); it++) {
      Nodo* hijo = it->first;
      double coste = it->second;

      // Verificar si el nodo está en otra rama
      if (EstaEnOtraRama(hijo, actual, camino)) {
        pila.push(hijo);
        camino[hijo->GetId()] = {actual, coste};
        generados.push_back(hijo->GetId());
        visitados.insert(*hijo);
      } else if (visitados.find(*hijo) == visitados.end()) {
        // Procesar nodos no visitados
        pila.push(hijo);
        camino[hijo->GetId()] = {actual, coste};
        generados.push_back(hijo->GetId());
        visitados.insert(*hijo);
      }
    }

    // Mostrar estado de la iteración
    MostrarIteracion(++iteracion, generados, inspeccionados, file);
  }

  // Si no se encontró un camino
  cout << "No se encontró un camino al nodo final." << endl;
}

/**
 * @brief Función que realiza un recorrido en amplitud
 * @param inicial Nodo inicial
 * @param final Nodo final
 * @param file Fichero de salida
*/

void Grafo::RecorridoAmplitud(Nodo& inicial, Nodo& final, ofstream& file) {
  queue<Nodo*> cola; // Cola para realizar el recorrido en amplitud
  set<Nodo> visitados; // Conjunto de nodos visitados
  map<int, pair<Nodo*, double>> camino; // Camino recorrido (padre y coste)
  vector<int> inspeccionados, generados = {inicial.GetId()};
  double coste_total = 0.0;
  int iteracion = 1;

  // Información inicial
  file << "Número de nodos: " << num_nodos_ << endl;
  file << "Número de aristas: " << num_aristas_ << endl;
  file << "Vertice origen: " << inicial.GetId() << endl;
  file << "Vertice destino: " << final.GetId() << endl;
  file << "---------------------------------------------" << endl;
  file << "Iteración " << iteracion << endl;
  file << "Generados: " << inicial.GetId() << endl;
  file << "Inspeccionados: -" << endl;
  file << "---------------------------------------------" << endl;

  Nodo* nodo_inicial = nullptr;
  Nodo* nodo_final = nullptr;

  // Buscamos el nodo en el grafo
  for (auto& par : grafo_) {
    if (par.first.GetId() == inicial.GetId()) nodo_inicial = const_cast<Nodo*>(&par.first);
    if (par.first.GetId() == final.GetId()) nodo_final = const_cast<Nodo*>(&par.first);
  }

  cola.push(nodo_inicial);
  visitados.insert(inicial);

  while (!cola.empty()) {
    Nodo* actual = cola.front();
    cola.pop();
    inspeccionados.push_back(actual->GetId());

    // Si se alcanza el nodo final, reconstruimos el camino
    if (actual->GetId() == nodo_final->GetId()) {
      stack<Nodo*> camino_inverso;
      for (Nodo* nodo = nodo_final; nodo != nodo_inicial; nodo = camino[nodo->GetId()].first) {
        camino_inverso.push(nodo);
        coste_total += camino[nodo->GetId()].second;
      }
      camino_inverso.push(nodo_inicial);

      // Muestro el camino y coste total
      MostrarIteracion(iteracion++, generados, inspeccionados, file);
      file << "Camino: ";
      while (!camino_inverso.empty()) {
        file << camino_inverso.top()->GetId() << " ";
        camino_inverso.pop();
      }
      file << "\nCoste: " << coste_total << endl;
      return;
    }

    // Obtener hijos del nodo actual y procesarlos
    vector<pair<Nodo*, double>> hijos = actual->GetHijos();
    for (auto it = hijos.begin(); it != hijos.end(); it++) {
      if (!visitados.count(it->first->GetId())) {
        cola.push(it->first);
        visitados.insert(it->first->GetId());
        camino[it->first->GetId()] = {actual, it->second};
        generados.push_back(it->first->GetId());
      }
    }

    // Mostrar estado de la iteración
    MostrarIteracion(iteracion++, generados, inspeccionados, file);
  }
  cout << "No se encontró un camino al nodo final." << endl;
}

/**
 * @brief Función que comprueba si un nodo está en otra rama
 * @param nodo Nodo a comprobar
 * @param padre Nodo padre
 * @param camino Camino recorrido
 * @return true si está en otra rama, false en caso contrario
*/

bool Grafo::EstaEnOtraRama(Nodo* nodo, Nodo* padre, map<int, pair<Nodo*, double>>& camino) {
  Nodo* actual = padre;
  while (actual != nullptr) {
    if (actual->GetId() == nodo->GetId()) {
      return false; // El nodo está en la misma rama
    }
    if (camino.find(actual->GetId()) == camino.end()) {
      break; // No hay más padres en el camino actual
    }
    actual = camino[actual->GetId()].first;
  }
  return true; // El nodo no está en la misma rama
}