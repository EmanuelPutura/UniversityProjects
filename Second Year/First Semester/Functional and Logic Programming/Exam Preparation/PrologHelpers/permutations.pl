insertOnEveryPos([], E, [E]) :- !.
insertOnEveryPos(LST, E, [E|LST]).
insertOnEveryPos([H|T], E, [H|R]) :-
    insertOnEveryPos(T, E, R).

permutations([], []).
permutations([H|T], R) :-
    permutations(T, RR),
    insertOnEveryPos(RR, H, R).
    