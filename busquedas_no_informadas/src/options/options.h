#pragma once
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <iterator>
#include <optional>
#include <string_view>
#include <cassert>

using namespace std;

struct Options {
  string file_in;
  string file_out;
  int nodo_origen;
  int nodo_destino;
  int opcion;
};

optional<Options> parse_args(int argc, char* argv[]);