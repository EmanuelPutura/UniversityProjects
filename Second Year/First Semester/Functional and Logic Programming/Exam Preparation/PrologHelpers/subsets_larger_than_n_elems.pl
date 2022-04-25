comb(_, 0, []) :- !.
comb([H|_], 1, [H]).
comb([_|T], K, R) :-
    comb(T, K, R).
comb([H|T], K, [H|R]) :-
    K > 1,
    K1 is K - 1,
    comb(T, K1, R).

largerThanSubsets(LST, N, N, LST) :- !.
largerThanSubsets([_|T], LEN, N, R) :-
    LEN1 is LEN - 1,
    largerThanSubsets(T, LEN1, N, R).
largerThanSubsets([H|T], _, N, [H|R]) :-
    N > 0,
    N1 is N - 1,
    comb(T, N1, R).
largerThanSubsets([H|T], LEN, N, [H|R]) :-
    LEN1 is LEN - 1,
    largerThanSubsets(T, LEN1, N, R).