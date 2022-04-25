generateGreaterThan(N, N).
generateGreaterThan(N, R) :-
    N1 is N + 1,
    generateGreaterThan(N1, R).

generateBetween(M, M, M) :- !.
generateBetween(MIN, _, MIN).
generateBetween(MIN, MAX, R) :-
	MIN1 is MIN + 1,
    generateBetween(MIN1, MAX, R).

solve(N, _, [H|_], _) :-
    H > N,
    !,
    fail.
solve(_, _, LST, LST).
solve(N, M, [GH|GT], R) :-
    MIN is GH + M,
    MIN =< N,
    generateGreaterThan(MIN, RR),
    RR =< N,
    !,
    solve(N, M, [RR|[GH|GT]], R).

stopSols(RR, N) :-
    RR =< N,
    !.


solveMain(N, M, R) :-
    generateBetween(1, N, RR),
    RR =< N,
    solve(N, M, [RR], R),
    [_|[_|_]] = R.
    