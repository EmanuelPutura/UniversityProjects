getRet(H, M, H) :-
    H < M,
    !.
getRet(_, M, M).

listMin([], none) :- !.
listMin([H], H) :- !.
listMin([H|T], R) :-
    listMin(T, M),
    getRet(H, M, R).

swapMin([], _, _, []) :- !.
swapMin([M|T], E, M, [E|T]) :- !.
swapMin([H|T], E, M, [H|R]) :-
    swapMin(T, E, M, R).

swapMinMain([H|T], E, R, M) :-
    listMin([H|T], M),
    swapMin([H|T], E, M, R).

/* H >= E always*/
deleteElemSorted([], _, []) :- !.
deleteElemSorted([H|T], E, [H|T]) :-
    H > E,
    !.
deleteElemSorted([_|T], E, R) :-
    deleteElemSorted(T, E, R).

sortList([], []).
sortList([H|T], [M|RS]) :-
    swapMinMain([H|T], H, [_|RT], M),
    sortList(RT, RR),
    deleteElemSorted(RR, M, RS).
