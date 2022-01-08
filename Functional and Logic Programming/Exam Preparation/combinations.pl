comb(_, 0, []) :- !.
comb([H|_], 1, [H]).
comb([_|T], K, R) :-
    comb(T, K, R).
comb([H|T], K, [H|R]) :-
    K > 1,
    K1 is K - 1,
    comb(T, K1, R).