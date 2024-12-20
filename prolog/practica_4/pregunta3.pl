hanoi(N, L) :-
  hanoi(N, 1, 3, 2, L). % Llama a la relación hanoi/5 con los valores iniciales.

% Caso base: si N es 0, no hay movimientos que hacer.
hanoi(0, _, _, _, []).

% Caso recursivo: mueve N discos de la torre A a la torre C usando la torre B.
hanoi(N, Origen, Destino, Auxiliar, L) :-
  N > 0, % Si N es 0, no hay movimientos que hacer.
  N1 is N - 1, % Número de discos a mover en la llamada recursiva.
  hanoi(N1, Origen, Auxiliar, Destino, L1),
  append(L1, [mover(Origen, Destino)], L2),
  hanoi(N1, Auxiliar, Destino, Origen, L3),
  append(L2, L3, L).

% hanoi_ACC
hanoi_acc(N, L) :-
  hanoi_acc(N, 1, 3, 2, [], L). % Llama a la relación hanoi_ACC/6 con los valores iniciales.

% Caso base: si N es 0, no hay movimientos que hacer.
hanoi_acc(0, _, _, _, Acc, Acc).

% Caso recursivo: mueve N discos de la torre A a la torre C usando la torre B.
hanoi_acc(N, Origen, Destino, Auxiliar, Acc, L) :-
  N > 0, % Si N es 0, no hay movimientos que hacer.
  N1 is N - 1, % Número de discos a mover en la llamada recursiva.
  hanoi_acc(N1, Origen, Auxiliar, Destino, Acc, L1),
  append(L1, [mover(Origen, Destino)], L2),
  hanoi_acc(N1, Auxiliar, Destino, Origen, L2, L).

% hanoi_dif

hanoi_dif(N, L) :-
  hanoi_dif(N, 1, 3, 2, L-Tail), % Llama a la relación hanoi_diff/6 con los valores iniciales.
  Tail = [].

% Caso base: si N es 0, no hay movimientos que hacer.
hanoi_dif(0, _, _, _, L-L).

% Caso recursivo: mueve N discos de la torre A a la torre C usando la torre B.
hanoi_dif(N, Origen, Destino, Auxiliar, L-Tail) :-
  N > 0, % Si N es 0, no hay movimientos que hacer.
  N1 is N - 1, % Número de discos a mover en la llamada recursiva.
  hanoi_dif(N1, Origen, Auxiliar, Destino, L-L1),
  L1 = [mover(Origen, Destino) | L2],
  hanoi_dif(N1, Auxiliar, Destino, Origen, L2-Tail).