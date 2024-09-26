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
  stack<int> pila; // Pila para gestionar los nodos a explorar
  set<int> visitados; // Conjunto de nodos visitados
  map<int, Nodo> camino; // Mapa para guardar el camino
  double costo_total = 0.0;
  int iteracion = 1;

  // Información inicial del grafo
  file << "Número de nodos del grafo: " << GetNumNodos() << endl;
  file << "Número de aristas del grafo: " << GetAristas() << endl;
  file << "Vértice origen: " << nodo_origen << endl;
  file << "Vértice destino: " << nodo_destino << endl;

  // Insertamos el nodo inicial en la pila
  pila.push(nodo_origen);
  visitados.insert(nodo_origen);

  vector<int> nodos_generados;
  vector<int> nodos_inspeccionados;

  // Realizar la búsqueda en profundidad
  while (!pila.empty()) {
    int nodo_actual = pila.top();
    pila.pop();
    nodos_inspeccionados.push_back(nodo_actual);

    // Si encontramos el nodo destino, reconstruimos el camino y calculamos el costo
    if (nodo_actual == nodo_destino) {
      stack<int> camino_inverso;
      int temp = nodo_destino;
      while (temp != nodo_origen) {
        camino_inverso.push(temp);
        costo_total += camino[temp].GetCoste();
        temp = camino[temp].GetPadre();
      }
      camino_inverso.push(nodo_origen);
      // Imprimir iteración final
      file << "Iteración " << iteracion << endl;
      file << "Nodos generados: ";
      for (int nodo : nodos_generados) file << nodo << " ";
      file << endl;
      file << "Nodos inspeccionados: ";
      for (int nodo : nodos_inspeccionados) file << nodo << " ";
      file << endl;

      // Escribir el camino en el archivo
      file << "Camino: ";
      while (!camino_inverso.empty()) {
        file << camino_inverso.top();
        camino_inverso.pop();
        if (!camino_inverso.empty()) file << " - ";
      }
      file << endl;
      file << "Costo: " << costo_total << endl;
      return;
    }
    // Obtener todos los hijos del nodo inicial
    auto rango_hijos = arbol_.equal_range(nodo_actual);
    nodos_generados.clear(); // Limpiar los nodos generados
    for (auto it = rango_hijos.first; it != rango_hijos.second; it++) {
      Nodo hijo_nodo = it->second;
      int hijo = hijo_nodo.GetHijo();
      if (visitados.find(hijo) == visitados.end()) {
        // No ha sido visitado, lo agregamos a la pila
        pila.push(hijo);
        visitados.insert(hijo);
        // Guardamos el nodo y su relación con el padre
        camino[hijo] = hijo_nodo;
        // Agregamos el nodo a la lista de nodos generados
        nodos_generados.push_back(hijo);
      }
    }
    // Imprimir la iteración actual
    file << "Iteración " << iteracion++ << endl;
    file << "Nodos generados: ";
    for (int nodo : nodos_generados) file << nodo << " ";
    file << endl;
    file << "Nodos inspeccionados: ";
    for (int nodo : nodos_inspeccionados) file << nodo << " ";
    file << endl;
  }

  cout << "No se encontró un camino entre los nodos " << nodo_origen << " y " << nodo_destino << endl;
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