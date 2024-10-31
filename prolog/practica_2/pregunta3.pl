mcd(A, 0, A) :- A > 0, !.
mcd(A, B, D) :-
    B > 0,
    R is A mod B,
    mcd(B, R, D).

mcm(M, A, B) :-
    mcd(A, B, D),
    M is (A * B) // D.