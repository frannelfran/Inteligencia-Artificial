% Asociación de números a nombres de días de la semana
nombre_dia(0, domingo).
nombre_dia(1, lunes).
nombre_dia(2, martes).
nombre_dia(3, miercoles).
nombre_dia(4, jueves).
nombre_dia(5, viernes).
nombre_dia(6, sabado).

dia_semana(D, M, Y, DiaSemana) :-
    K is Y mod 100,
    J is Y // 100,
    calcular_m(M, MM),
    F is D + floor(2.6 * MM - 0.2) - 2 * J + K + floor(K / 4) + floor(J / 4),
    N is ((F mod 7) + 7) mod 7, % Normalizar a un valor positivo
    nombre_dia(N, DiaSemana).

% Ajuste de meses para el cálculo del día de la semana
calcular_m(M, MM) :-
    (M =< 2 -> MM is M + 10 ; MM is M - 2).
