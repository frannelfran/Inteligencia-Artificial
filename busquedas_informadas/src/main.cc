#include "laberinto/laberinto.h"
#include "nodo/nodo.h"
#include "posicion/posicion.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    cout << "Uso: " << argv[0] << " <archivo_entrada>" << endl;
    return EXIT_FAILURE;
  }
  ifstream file(argv[1]);
  // Compruebo que se pueda abrir el fichero
  if (!file.is_open()) {
    cout << "Error al abrir el archivo" << endl;
    return EXIT_FAILURE;
  }
  // Creo el laberinto
  Laberinto laberinto(file);
  int opcion;
  do {
    cout << "[1]. Cambiar entrada" << endl;
    cout << "[2]. Cambiar salida" << endl;
    cout << "[3]. Buscar camino" << endl;
    cout << "[4]. Salir" << endl;
    cout << "Opción: ";
    cin >> opcion;
    switch (opcion) { // Manejo de las opciones
      case 1: { // Cambiar la entrada
        int x, y;
        cout << "Introduce la nueva posición de la entrada: ";
        cin >> x >> y;
        laberinto.CambiarEntrada(Posicion(x, y));
        break;
      }
      case 2: { // Cambiar la salida
        int x, y;
        cout << "Introduce la nueva posición de la salida: ";
        cin >> x >> y;
        laberinto.CambiarSalida(Posicion(x, y));
        break;
      }
      case 3: // Buscar camino
        laberinto.BusquedaAEstrella();
        break;
      case 4: // Salir
        cout << "Saliendo..." << endl;
        break;
      default:
        cout << "Opción no válida" << endl;
        break;
    }
  } while (opcion != 5);
  
  file.close();
  return 0;
}