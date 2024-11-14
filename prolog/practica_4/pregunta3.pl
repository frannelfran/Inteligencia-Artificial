hanoi(N, L) :-
  hanoi(N, 1, 2, 3, L). % Llama a la relación hanoi/5 con los valores iniciales.

% Caso base: si N es 0, no hay movimientos que hacer.
hanoi(0, _, _, _, []).

% Caso recursivo: mueve N discos de la torre A a la torre C usando la torre B.
hanoi(N, Origen, Destino, Auxiliar, L) :-
  N > 0, % Si N es 0, no hay movimientos que hacer.
  N1 is N - 1, % Número de discos a mover en la llamada recursiva.
  hanoi(N1, Origen, Auxiliar, Destino, L1), % Mueve N1 discos de A a B.
  append(L1, [mover(N, Origen, Destino)], L2), % Agrega el movimiento actual.
  hanoi(N1, Auxiliar, Destino, Origen, L3), % Mueve N1 discos de B a C.
  append(L2, L3, L). % Concatena las listas de movimientos.

