%
% IA-ESIT-ULL: Ejemplo de hechos y reglas
%

% Hechos
%

% Sexo
femenino(petra).
femenino(carmen).
femenino(maria).
femenino(rosa).
femenino(ana).
femenino(cande).
masculino(angel).
masculino(pepe).
masculino(juan).
masculino(pedro).
masculino(enrique).
masculino(raul).
masculino(alfonso).

% Progenitor
progenitor(petra, juan).
progenitor(petra, rosa).
progenitor(carmen, pedro).
progenitor(maria, ana).
progenitor(maria, enrique).
progenitor(rosa, raul).
progenitor(rosa, alfonso).
progenitor(rosa, cande).
progenitor(angel, juan).
progenitor(angel, rosa).
progenitor(pepe, pedro).
progenitor(juan, ana).
progenitor(juan, enrique).
progenitor(pedro, raul).
progenitor(pedro, alfonso).
progenitor(pedro, cande).


% Reglas
%

nieto_a(X, Y) :- progenitor(V, X), progenitor(Y, V).

antepasado(X, Z) :- progenitor(X, Z).
antepasado(X, Z) :- progenitor(X, Y), antepasado(Y, Z).

% Realizar las reglas necesarias para definir los siguientes predicados distinguiendo el sexo:
% hijo/2, hija/2
% nieto/2, nieta/2

hijo(X, Y) :- progenitor(Y, X), masculino(X).
hija(X, Y) :- progenitor(Y, X), femenino(X).

nieto(X, Y) :- progenitor(Y, Z), progenitor(Z, X), masculino(X).
nieta(X, Y) :- progenitor(Y, Z), progenitor(Z, X), femenino(X).

% ¿Qué dificultades encuentras al tratar de definir reglas para los siguientes predicados con lo dado hasta ahora?
% hermano/2, hermana/2
% sobrino/2, sobrina/2
% primo/2, prima/2

% Dificultades:
% - No se puede definir hermano/2, hermana/2 porque no se ha definido el concepto de hermano.
% - No se puede definir sobrino/2, sobrina/2 porque no se ha definido el concepto de sobrino.
% - No se puede definir primo/2, prima/2 porque no se ha definido el concepto de primo.



