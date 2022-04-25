areCollinear([X1, _], [X2, _], [X3, _]) :-
    X2 - X1 =:= 0,
    !,
    X3 - X1 =:= 0.
areCollinear([X1, _], [X2, _], [X3, _]) :-
    X3 - X2 =:= 0,
    !,
    X3 - X1 =:= 0.
areCollinear([X1, Y1], [X2, Y2], [X3, Y3]) :-
    SL1 is (Y2 - Y1) / (X2 - X1),
    SL2 is (Y3 - Y2) / (X3 - X2),
    SL1 =:= SL2.

getSlope(X1, X2, _, _, inf) :-
    X1 =:= X2,
    !.
getSlope(X1, X2, Y1, Y2, SL) :-
    SL is (Y2 - Y1) / (X2 - X1).

checkSlopes(inf, inf) :- !.
checkSlopes(SL, SL) :- !.

checkSubset([]) :- !.
checkSubset([_]) :- !.
checkSubset([[X1, Y1], [X2, Y2] | T]) :-
    getSlope(X1, X2, Y1, Y2, SLP),
    checkSubsetSlope([[X2, Y2] | T], SLP).
    
checkSubsetSlope([], _) :- !.
checkSubsetSlope([_], _) :- !.
checkSubsetSlope([[X1, Y1], [X2, Y2] | T], SL) :-
    getSlope(X1, X2, Y1, Y2, SLP),
    checkSlopes(SL, SLP),
    checkSubsetSlope([[X2, Y2] | T], SL).

getSubsetsSol(_, R, RLEN, R, RLEN).
getSubsetsSol(H, R, RLEN, [H|R], RLEN1) :-
    RLEN1 is RLEN + 1.
    
generateAndTestSubsets([], [], 0).
generateAndTestSubsets([H|T], SOL, RLEN1) :-
    generateAndTestSubsets(T, R, RLEN),
    getSubsetsSol(H, R, RLEN, SOL, RLEN1),
    checkSubset(SOL).

generateAndTestSubsetsMain(LST, SOL) :-
    generateAndTestSubsets(LST, SOL, RLEN),
    RLEN >= 2.