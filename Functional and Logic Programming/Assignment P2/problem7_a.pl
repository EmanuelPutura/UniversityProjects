/*
 * a. Determine the position of the maximal element of a linear list.  
*/

% maxBetweenTwoNos(NR1 - number, NR2 - number, R - number)
% flow: (i, i, i), (i, i, o)
maxBetweenTwoNos(NR1, NR2, R) :-
    NR1 > NR2,
    !,
    R is NR1.
maxBetweenTwoNos(_, NR2, NR2).

% findMax(L - list, R - number)
% flow: (i, i), (i, o)
findMax([],_) :-
    fail.
findMax([H], H) :- !.
findMax([H | T], R) :-
    findMax(T, RR),
    maxBetweenTwoNos(H, RR, R).

% setIfEqualsMax(T - list, H - number, MAX - number, POS - number, R - list)
% flow: (i, i, i, i, i), (i, i, i, i, o)
setIfEqualsMax(T, H, MAX, POS, [POS | T]) :-
    H is MAX,
    !.
setIfEqualsMax(T, _, _, _, T).

% maxElemPositions(L - list, MAX - number, R - list, POS - number)
% flow: (i, i, i, i), (i, i, o, i)
maxElemPositions([], _, [], _).
maxElemPositions([H | T], MAX, R, POS) :-
    NPOS is POS + 1,
    maxElemPositions(T, MAX, RR, NPOS),
    setIfEqualsMax(RR, H, MAX, POS, R).

% maxElemPositionsMain(L - list, R - list)
% flow: (i, i), (i, o)
maxElemPositionsMain(L, R) :-
    findMax(L, MAX),
    !,
    maxElemPositions(L, MAX, R, 1).
maxElemPositionsMain([], []).
