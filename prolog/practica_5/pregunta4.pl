% Caso base: 2 es primo.
primo(2) :- !.

% Caso general: un número es primo si es mayor que 2, no es divisible por ningún número
% entre 2 y la raíz cuadrada de N.
primo(N) :-
  N > 2,
  N mod 2 =\= 0,           % Descarta números pares mayores que 2.
  \+ tiene_divisor(N, 3).  % Comprueba si hay divisores comenzando desde 3.

% Predicado auxiliar para verificar si N tiene divisores.
tiene_divisor(N, Div) :-
  Div * Div =< N,          % Solo verifica hasta la raíz cuadrada de N.
  (N mod Div =:= 0;        % Falla si encuentra un divisor exacto.
    NextDiv is Div + 2,     % Incrementa el divisor en 2 (solo impares).
    tiene_divisor(N, NextDiv)).

