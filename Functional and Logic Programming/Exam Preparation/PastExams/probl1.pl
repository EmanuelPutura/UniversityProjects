genList(M, M, [M]) :- !.
genList(MIN, MAX, [MIN|R]) :-
    MIN1 is MIN + 1,
    genList(MIN1, MAX, R).
    
insertOnEveryPos([], EL, [EL]) :- !.
insertOnEveryPos(LST, EL, [EL|LST]).
insertOnEveryPos([H|T], EL, [H|R]) :-
    insertOnEveryPos(T, EL, R).

permutations([], []).
permutations([H|T], R) :-
    permutations(T, RR),
    insertOnEveryPos(RR, H, R).

checkPermutation([], _) :- !.
checkPermutation([H|T], LST) :-
    abs(H - LST) =< 2,
    checkPermutation(T, H).
    
main(N, [H|T]) :-
    NMAX is 2 * N - 1,
    genList(N, NMAX, GEN),
    permutations(GEN, [H|T]),
    checkPermutation(T, H).
