reverse([], C, C) :- !.
reverse([H|T], C, R) :-
    reverse(T, [H|C], R).

generateNoBetween(M, M, M) :- !.
generateNoBetween(MIN, _, MIN).
generateNoBetween(MIN, MAX, GEN) :-
    MIN1 is MIN + 1,
    generateNoBetween(MIN1, MAX, GEN).

solve(N, SF, N, SF).
solve(N, [H|T], SUM, SOL) :-
    H1 is H + 1,
    SUM1 is SUM + H1,
    SUM1 =< N,
    solve(N, [H1|[H|T]], SUM1, SOL).

findDecomposition(N, SOL) :-
    generateNoBetween(1, N, NO),
    solve(N, [NO], NO, SOL1),
    reverse(SOL1, SOL).
