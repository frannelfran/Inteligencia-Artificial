% Caso inicial: comienza la suma con un acumulador en 0.
suma_acc10(L, N) :-
  suma_acc10_aux(L, 0, N).

% Caso base: lista vacía, la suma acumulada es el resultado.
suma_acc10_aux([], Acc, Acc) :-
  Acc =< 10. % El acumulador debe ser menor o igual a 10.

% Caso recursivo: procesa la cabeza de la lista.
suma_acc10_aux([H|T], Acc, N) :-
  Acc1 is Acc + H, % Actualiza el acumulador.
  Acc1 =< 10,      % Asegura que la suma no supere 10.
  suma_acc10_aux(T, Acc1, N). % Continúa con la cola de la lista.
