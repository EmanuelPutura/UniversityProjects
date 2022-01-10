addToEnd([], EL, [EL]).
addToEnd([H|T], EL, [H|R]) :-
    addToEnd(T, EL, R).

checkForSingleElem(_, _, ELPOS, CPOS) :-
    CPOS > ELPOS,
    !,
    fail.
checkForSingleElem([H|_], EL, _, _) :-
    abs(EL - H, R),
    R is 1,
    !.
checkForSingleElem([_|T], EL, ELPOS, CPOS) :-
    CPOS1 is CPOS + 1,
    checkForSingleElem(T, EL, ELPOS, CPOS1).

checkPermutation([_], _, _) :- !.
checkPermutation([H|T], PSF, PSFLEN) :-
    PSFLEN1 is PSFLEN + 1,
    addToEnd(PSF, H, R),
    checkForSingleElem(R, H, PSFLEN, 0),
	checkPermutation(T, R, PSFLEN1).

checkPermutationMain([H|T]) :-
    checkPermutation(T, [H], 1).

insertOnEveryPos([], EL, [EL]) :- !.
insertOnEveryPos(LST, EL, [EL|LST]).
insertOnEveryPos([H|T], EL, [H|R]) :-
    insertOnEveryPos(T, EL, R).

permutations([], []).
permutations([H|T], R) :-
    permutations(T, RR),
    insertOnEveryPos(RR, H, R).

permutationsMain(LST, R) :-
    permutations(LST, R),
    checkPermutationMain(R).
