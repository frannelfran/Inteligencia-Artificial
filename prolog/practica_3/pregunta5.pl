% Caso base: cuando encontramos X en L, verificamos que Y esté en el resto de la lista.
previo(X, Y, [X|T]) :-
  member(Y, T).

% Caso recursivo: si X no es el primer elemento de L, seguimos recorriendo la lista.
previo(X, Y, [_|T]) :-
  previo(X, Y, T).
