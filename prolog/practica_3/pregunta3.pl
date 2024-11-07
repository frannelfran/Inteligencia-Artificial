% Caso base
entrelaza([], [], []). % Si ambas listas están vacías, la lista resultante también estará vacía.

entrelaza([H1|T1], [H2|T2], [H1, H2|T]) :-
  entrelaza(T1, T2, T). % Si ambas listas tienen al menos un elemento, se toma el primer elemento de cada una y se añaden a la lista resultante.

