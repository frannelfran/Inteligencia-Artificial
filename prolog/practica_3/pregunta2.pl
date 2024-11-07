% Caso base = listas vacias
cuadrado([], []).

% Caso recursivo
cuadrado([H|T], [H2|T2]) :-
  H2 is H*H, % Calcula el cuadrado de la cabeza
  cuadrado(T, T2). % Calcula el cuadrado de la cola