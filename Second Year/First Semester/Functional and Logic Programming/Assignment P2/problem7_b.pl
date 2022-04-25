maxBetweenTwoNos(NR1, NR2, R) :-
    NR1 > NR2,
    !,
    R is NR1.
maxBetweenTwoNos(_, NR2, NR2).

findMax([],_) :-
    fail.
findMax([H], H) :- !.
findMax([H | T], R) :-
    findMax(T, RR),
    maxBetweenTwoNos(H, RR, R).

setIfEqualsMax(T, H, MAX, POS, [POS | T]) :-
    H is MAX,
    !.
setIfEqualsMax(T, _, _, _, T).

maxElemPositions([], _, [], _).
maxElemPositions([H | T], MAX, R, POS) :-
    NPOS is POS + 1,
    maxElemPositions(T, MAX, RR, NPOS),
    setIfEqualsMax(RR, H, MAX, POS, R).

maxElemPositionsMain(L, R) :-
    findMax(L, MAX),
    !,
    maxElemPositions(L, MAX, R, 1).
maxElemPositionsMain([], []).

% replaceSublistWithMaxPositions(L - list, R - list)
% flow: (i, i), (i, o)
replaceSublistWithMaxPositions([], []).
replaceSublistWithMaxPositions([H | T], [P | TR]) :-
    is_list(H),
    !,
    maxElemPositionsMain(H, P),
    replaceSublistWithMaxPositions(T, TR).
replaceSublistWithMaxPositions([H | T], [H | TR]) :-
    replaceSublistWithMaxPositions(T, TR).
