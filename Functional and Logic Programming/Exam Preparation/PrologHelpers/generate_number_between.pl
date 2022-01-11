generateNoBetween(M, M, M) :- !.
generateNoBetween(MIN, _, MIN).
generateNoBetween(MIN, MAX, GEN) :-
    MIN1 is MIN + 1,
    generateNoBetween(MIN1, MAX, GEN).