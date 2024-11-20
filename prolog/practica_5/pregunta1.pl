% Definición del predicado alterar/2
alterar([], []) :- !. % Caso base: cuando la lista está vacía, la solución es una lista vacía.

alterar([tu|T], [yo|R]) :- !, alterar(T, R). % Si el elemento es 'tu', se sustituye por 'yo'.
alterar([eres|T], [[no, soy]|R]) :- !, alterar(T, R). % Si el elemento es 'eres', se sustituye por '[no, soy]'.
alterar([ordenador|T], [humano|R]) :- !, alterar(T, R). % Si el elemento es 'ordenador', se sustituye por 'humano'.
alterar([H|T], [H|R]) :- alterar(T, R). % Para cualquier otro caso, se conserva el elemento original.
