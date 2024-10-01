#include "arbol.h"

/**
 * @brief Constructor de la clase árbol
 * @param file Fichero de entrada
*/

Arbol::Arbol(const vector<vector<double>>& matriz_coste) {
  for (int i = 0; i < matriz_coste.size(); i++) {
    for (int j = i + 1; j < matriz_coste.size(); j++) {
      if (matriz_coste[i][j] != 0) { // si el coste != -1 cambiado por 0
        Nodo nodo_ida(i + 1), nodo_vuelta(j + 1);
        Arista arista_ida(i + 1, j + 1, matriz_coste[i][j]), arista_vuelta(j + 1, i + 1, matriz_coste[i][j]);
        // Insertamos los nodos en el árbol
        InsertarNodo(nodo_ida, arista_ida);
        InsertarNodo(nodo_vuelta, arista_vuelta);
        // Insertamnos los hijos a cada nodo
        nodo_ida.AddHijo(j + 1);
      }
    }
  }
  this->num_aristas_ = arbol_.size() / 2; // Número de aristas del grafo
  this->num_nodos_ = matriz_coste.size(); // Número de nodos del grafo
}

/**
 * @brief Búsqueda en profundidad
 * @param nodo_origen Nodo de origen
 * @param nodo_destino Nodo de destino
 * @param file Fichero de salida
*/
 
void Arbol::DFS(const int nodo_origen, const int nodo_destino, ofstream& file) {
  stack<int> pila; // Pila para almacenar los nodos
  set<int> visitados, generados = {nodo_origen}; // Conjunto para almacenar los nodos visitados
  map<int, Arista> camino; // Mapa para almacenar el camino
  vector<int> inspeccionados; // Vector para almacenar los nodos inspeccionados
  double costo_total = 0.0;
  int iteracion = 1;

  // Muestro la información inicial en el fichero
  file << "Número de nodos del grafo: " << this->num_nodos_ << endl;
  file << "Número de aristas del grafo: " << this->num_aristas_ << endl;
  file << "Vértice origen: " << nodo_origen << endl;
  file << "Vértice destino: " << nodo_destino << endl;

  // Inserto la raíz en la pila y en el conjunto de visitados
  pila.push(nodo_origen);
  visitados.insert(nodo_origen);

  while (!pila.empty()) {
    int nodo_actual = pila.top(); // Obtenemos el nodo actual
    pila.pop(); // Lo extraemos
    inspeccionados.push_back(nodo_actual);
    // Si encontramos el nodo destino
    if (nodo_actual == nodo_destino) {
      stack<int> camino_inverso; // Pila para almacenar el camino
      // Reconstruyo el camino desde el nodo destino hasta el origen
      for (int it = nodo_destino; it != nodo_origen; it = camino[it].GetOrigen()) {
        camino_inverso.push(it);
        costo_total += camino[it].GetCoste();
      }
      camino_inverso.push(nodo_origen); // Inserto el nodo origen
      // Muestro el camino en el fichero
      file << "Iteración " << iteracion << ": " << endl;
      file << "Nodos generados: ";
      for (int nodo : generados) file << nodo << " ";
      file << endl << "Nodos inspeccionados: ";
      for (auto it = inspeccionados.begin(); it != inspeccionados.end(); it++) {
        file << *it << " ";
      }
      file << endl << "------------------------------------" << endl;
      // Mostramos el camino en el fichero
      file << "Camino: ";
      while (!camino_inverso.empty()) {
        file << camino_inverso.top();
        camino_inverso.pop();
        if (!camino_inverso.empty()) file << " - ";
      }
      // Mostramos el coste total
      file << endl << "Coste total: " << costo_total << endl;
      cout << "Camino encontrado" << endl;
      return;
    }

    // Obtengo los hijos del nodo actual
    auto range_hijos = arbol_.equal_range(Nodo(nodo_actual));
    generados.clear();
    for (auto it = range_hijos.second; it != range_hijos.first;) {
      --it;
      int hijo = it->second.GetDestino();
      if (!visitados.count(hijo)) { // Si no ha sido visitado
        pila.push(hijo);
        generados.insert(hijo); // Lo genero
        visitados.insert(hijo); // Lo visito
        camino[hijo] = it->second; // Almaceno el camino
      }
    }
    // Muestro la información en el fichero
    file << "Iteración " << iteracion++ << ": ";
    file << endl << "Nodos generados: ";
    for (int nodo : generados) file << nodo << " ";
    file << endl << "Nodos inspeccionados: ";
    for (auto it = inspeccionados.begin(); it != inspeccionados.end(); it++) {
      file << *it << " ";
    }
    file << endl << "------------------------------------" << endl;
  }
  cout << "Camino no encontrado" << endl;
}

/**
 * @overload Sobrecarga del operador de salida
*/

ostream& operator<<(ostream& os, const Arbol& arbol) {
  for (auto it = arbol.arbol_.begin(); it != arbol.arbol_.end(); it++) {
    os << it->first.GetId() << " -> " << it->second.GetDestino() << " " << it->second.GetCoste() << endl;
  }
  return os;
}