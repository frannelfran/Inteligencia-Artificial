% Archivo: suma.pl

% Relación suma/2: calcula la suma de los elementos de la lista L sin acumulador
suma([], 0).  % Caso base: la suma de una lista vacía es 0.
suma([Cabeza | Cola], X) :-
  suma(Cola, SumaCola),   % Llamada recursiva para la cola
  X is Cabeza + SumaCola.  % La suma total es la cabeza más la suma de la cola.

% Archivo: suma_acc.pl

% Relación suma_acc/2: calcula la suma de los elementos de la lista L usando un acumulador
suma_acc(L, X) :-
  suma_acc(L, 0, X).  % Inicializa el acumulador en 0.

% Caso base: cuando la lista está vacía, la suma es el valor del acumulador.
suma_acc([], Acumulador, Acumulador).

% Caso recursivo: suma la cabeza al acumulador y continúa con la cola.
suma_acc([Cabeza | Cola], Acumulador, X) :-
  NuevoAcumulador is Acumulador + Cabeza,
  suma_acc(Cola, NuevoAcumulador, X).