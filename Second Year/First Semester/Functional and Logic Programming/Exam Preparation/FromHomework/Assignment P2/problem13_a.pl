getRetVal(H1, H2, H3, R, R) :-
    H1 =:= H2 - 1,
    H2 =:= H3 - 1,
    !.
getRetVal(H1, _, _, R, [H1 | R]).

removeConsecutives([], []) :- !.
removeConsecutives([E], [E]) :- !.
removeConsecutives([E1, E2], []) :-
    E1 =:= E2 - 1,
    !.
removeConsecutives([E1, E2], [E1, E2]) :- !. 
removeConsecutives([H|T], R) :-
    H1 is H,
    [H2|TT] = T,
    [H3|_] = TT,
    H1 =:= H2 - 1,
    H2 =\= H3 - 1,
    !,
    removeConsecutives(TT, R).
removeConsecutives([H|T], RR) :-
    H1 is H,
    [H2|TT] = T,
    [H3|_] = TT,
    removeConsecutives(T, R),
    getRetVal(H1, H2, H3, R, RR).
