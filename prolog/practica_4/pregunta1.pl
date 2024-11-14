% Predicado principal
invertir(L1, L2) :-
  invertir_acum(L1, [], L2).

% Caso base: cuando la lista de entrada está vacía, la lista invertida es el acumulador.
invertir_acum([], Acumulador, Acumulador).

% Caso recursivo: tomar la cabeza de L1 y añadirla al acumulador.
invertir_acum([Cabeza | Cola], Acumulador, L2) :-
  invertir_acum(Cola, [Cabeza | Acumulador], L2).