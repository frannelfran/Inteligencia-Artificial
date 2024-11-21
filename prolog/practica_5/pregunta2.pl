% Datos de reinado
reigns(rhodri, 844-878).
reigns(cadwallon, 985-986).
reigns(owain, 950-979).

% Generador de años dentro de un rango
between_inclusive(Start, End, Start) :- Start =< End.
between_inclusive(Start, End, Year) :-
  Start < End,
  Next is Start + 1,
  between_inclusive(Next, End, Year).

% Predicado reigns/2 modificado
prince(Prince, Year) :-
  nonvar(Prince), var(Year),  % Caso: Primer argumento instanciado, segundo sin instanciar
  reigns(Prince, Start-End),
  between_inclusive(Start, End, Year).
prince(Prince, Year) :-
  nonvar(Year),  % Caso: Segundo argumento instanciado
  reigns(Prince, Start-End),
  Year >= Start,
  Year =< End.
prince(Prince, Start-End) :-
  var(Prince), var(Start), var(End),
  reigns(Prince, Start-End).
