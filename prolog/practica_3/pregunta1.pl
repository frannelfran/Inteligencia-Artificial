% Caso base: el mínimo de una lista con un solo elemento es ese elemento.
min_lista([X], X).

% Caso recursivo: divide la lista en cabeza y cola, y compara la cabeza con el mínimo de la cola.
min_lista([H|T], Min) :-
  min_lista(T, MinT),      % Calcula el mínimo de la cola
  Min is min(H, MinT).  % Compara el primer elemento (H) con el mínimo de la cola
