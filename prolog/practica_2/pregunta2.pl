% Valores de X dentro de un rango de números

generado_int(X, MIN, MAX) :- 
  MIN =< MAX, 
  X = MIN.

generado_int(X, MIN, MAX) :-
  MIN < MAX,
  MIN1 is MIN + 1,
  generado_int(X, MIN1, MAX).