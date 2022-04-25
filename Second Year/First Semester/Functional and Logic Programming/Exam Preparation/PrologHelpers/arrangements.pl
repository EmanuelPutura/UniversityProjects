insertOnEveryPos([], E, [E]) :- !.
insertOnEveryPos(LST, E, [E|LST]).
insertOnEveryPos([H|T], E, [H|R]) :-
    insertOnEveryPos(T, E, R).

arrangements([H|_], 1, [H]).
arrangements([_|T], K, R) :-
    arrangements(T, K, R).
arrangements([H|T], K, RR) :-
    K > 1,
    K1 is K - 1,
    arrangements(T, K1, R),
    insertOnEveryPos(R, H, RR).