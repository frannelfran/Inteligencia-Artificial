#include "arbol.h"

/**
 * @brief Constructor de la clase arbol
 * @param file Fichero con los datos del arbol
*/

Arbol::Arbol(ifstream& file) {
  int num_nodos, save_num_nodos, nodo_padre = 1, nodo_hijo = 2;
  double coste;
  file >> num_nodos;
  save_num_nodos = num_nodos; // Guardo el numero de nodos para poder reiniciar el contador

  while (!file.eof()) {
    while (num_nodos--) {
      if (nodo_hijo > save_num_nodos) break;
      if (nodo_padre == nodo_hijo) nodo_hijo++;
      file >> coste;
      if (coste >= 0) {
        Nodo nodo(nodo_padre, nodo_hijo, coste); // Creo un nodo con el padre y el hijo
        InsertarNodo(nodo);
      }
      nodo_hijo++;
    }
    nodo_padre++;
    nodo_hijo = nodo_padre + 1;
    num_nodos = save_num_nodos;
  }
  this->nodos_ = save_num_nodos; // Guardo el numero de nodos
  this->aristas_ = arbol_.size(); // Guardo el numero de aristas
}

/**
 * @brief Busqueda en profundidad
 * @param nodo_origen Nodo de origen
 * @param nodo_destino Nodo de destino
 * @param file Fichero de salida
*/

void Arbol::DFS(int nodo_origen, int nodo_destino, ofstream& file) {
  stack<int> pila; // Pila para almacenar los nodos
  set<int> visitados; // Conjunto para almacenar los nodos visitados
  map<int, Nodo> camino; // Mapa para almacenar el camino
  double costo_total = 0.0;
  int iteracion = 1;

  // Información inicial
  file << "Número de nodos del grafo: " << GetNumNodos() << endl;
  file << "Número de aristas del grafo: " << GetAristas() << endl;
  file << "Vértice origen: " << nodo_origen << endl;
  file << "Vértice destino: " << nodo_destino << endl;

  pila.push(nodo_origen);
  visitados.insert(nodo_origen);
  vector<int> generados = {nodo_origen}, inspeccionados;

  while (!pila.empty()) {
    int nodo_actual = pila.top();
    pila.pop();
    inspeccionados.push_back(nodo_actual);
    if (nodo_actual == nodo_destino) {
      stack<int> camino_reverso;
      for (int temp = nodo_destino; temp != nodo_origen; temp = camino[temp].GetPadre()) {
        camino_reverso.push(temp);
        costo_total += camino[temp].GetCoste();
      }
      camino_reverso.push(nodo_origen);

      // Última iteración
      file << "Iteración " << iteracion << endl;
      file << "Nodos generados: ";
      for (int n : generados) file << n << " ";
        file << endl << "Nodos inspeccionados: ";
        for (int n : inspeccionados) file << n << " ";
        file << endl << "Camino: ";
        while (!camino_reverso.empty()) {
          file << camino_reverso.top();
          camino_reverso.pop();
          if (!camino_reverso.empty()) file << " - ";
        }
        file << endl << "Costo: " << costo_total << endl;
        cout << "Se ha encontrado un camino, para visualizarlo consulte el fichero de salida" << endl;
      return;
    }
    auto rango_hijos = arbol_.equal_range(nodo_actual);
    generados.clear();
    for (auto it = rango_hijos.first; it != rango_hijos.second; ++it) {
      Nodo hijo_nodo = it->second;
      int hijo = hijo_nodo.GetHijo();
      if (!visitados.count(hijo)) {
        pila.push(hijo);
        visitados.insert(hijo);
        camino[hijo] = hijo_nodo;
        generados.push_back(hijo);
      }
    }
    // Imprimir iteración
    file << "Iteración " << iteracion++ << endl;
    file << "Nodos generados: ";
    for (int n : generados) file << n << " ";
    file << endl << "Nodos inspeccionados: ";
    for (int n : inspeccionados) file << n << " ";
    file << endl;
  }
  cout << "No se encontró un camino entre " << nodo_origen << " y " << nodo_destino << endl;
}

/**
 * @overload Sobrecarga del operador <<
*/

ostream& operator<<(ostream& os, const Arbol& arbol) {
  for (auto it = arbol.arbol_.begin(); it != arbol.arbol_.end(); ++it) {
    os << it->first << " -> ";
    os << it->second;
  }
  return os;
}