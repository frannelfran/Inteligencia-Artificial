% Caso base: la lista vacía se aplana como una lista vacía.
aplana([], []).

% Caso recursivo 1: Si el primer elemento es una lista, se aplana recursivamente.
aplana([H|T], L2) :-
  is_list(H),               % Verifica si H es una lista.
  aplana(H, H_aplanado),    % Aplana la sublista H.
  aplana(T, T_aplanado),    % Aplana el resto de la lista T.
  append(H_aplanado, T_aplanado, L2). % Une el resultado de H y T.

% Caso recursivo 2: Si el primer elemento no es una lista, se agrega directamente a L2.
aplana([H|T], [H|T_aplanado]) :-
  \+ is_list(H),            % Verifica que H no sea una lista.
  aplana(T, T_aplanado).    % Aplana el resto de la lista T.
