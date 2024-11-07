% Caso base: una lista vacía L1 es siempre un subtramo de cualquier lista L2.
subtramo([], _).

% Caso recursivo 1: si L1 es un prefijo de L2, entonces es un subtramo.
subtramo([H1|T1], [H1|T2]) :-
  subtramo(T1, T2).

subtramo(L1, [_|T2]) :-
  subtramo(L1, T2).
