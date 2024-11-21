% Caso base: 2 es primo.
primo(2) :- !.
primo(3) :- !.

% Caso general: un número es primo si es mayor que 2, no es divisible por ningún número
% entre 2 y la raíz cuadrada de N.
primo(N) :-
  N > 1,
  not(tiene_divisor(N, 2)).

% Predicado auxiliar para verificar si N tiene divisores.
tiene_divisor(N, Div) :-
  Div * Div =< N,          % Solo verifica hasta la raíz cuadrada de N.
  (N mod Div =:= 0;        % Falla si encuentra un divisor exacto.
    NextDiv is Div + 1,     % Incrementa el divisor en 2 (solo impares).
    tiene_divisor(N, NextDiv)).

