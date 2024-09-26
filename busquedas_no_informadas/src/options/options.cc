#include "options.h"

/**
 * @brief Manejar las opciones del programa
 * @param argc Número de argumentos
 * @param argv Array donse se almacenan las opciones
 * @return Objeto Options
*/

optional<Options> parse_args(int argc, char* argv[]) {
  if (string(argv[1]) == "-h" || string(argv[1]) == "--help") { // Mostrar la ayuda
    cout << "Modo de uso: " << argv[0] << " " << "<fichero_entrada> <fichero_salida> <nodo origen> <nodo destino>" << endl;
    exit(EXIT_SUCCESS);
  }

  if (argc < 5 || argc > 5) {
    cerr << "Pruebe " << argv[0] << " -h o --help para más información" << endl;
    exit(EXIT_FAILURE);
  }

  vector<string_view> args(argv + 1, argv + argc);
  Options options;
  for (auto it = args.begin(); it != args.end(); it++) {
    options.file_in = string(*it);
    options.file_out = string(*++it);
    options.nodo_origen = stoi(string(*++it));
    options.nodo_destino = stoi(string(*++it));
  }
  return options;
}