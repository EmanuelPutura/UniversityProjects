listLength([], 0) :- !.
listLength([_|T], L) :-
    listLength(T, LL),
    L is LL + 1.

nSizeSubsets(LST, N, N, LST) :- !.
nSizeSubsets(_, LEN, N, _) :-
    LEN < N,
    !,
    fail.
nSizeSubsets([_|T], LEN, N, S) :-
    LEN1 is LEN - 1,
    nSizeSubsets(T, LEN1, N, S).
nSizeSubsets([H|T], LEN, N, [H|S]) :-
    N1 is N - 1,
    LEN1 is LEN - 1,
    nSizeSubsets(T, LEN1, N1, S).

nSizeSubsetsMain(LST, N, R) :-
    listLength(LST, LEN),
    findall(S, nSizeSubsets(LST, LEN, N, S), R).
