member([E|_], E) :- !.
member([_|T], E) :-
    member(T, E).

getNewCntAndDiff(H, DIFF, CNT, DIFF, CNT) :-
    member(DIFF, H),
    !.
getNewCntAndDiff(H, DIFF, CNT, [H|DIFF], NCNT) :-
    NCNT is CNT + 1.

getDifferentElems([], [], 0).
getDifferentElems([H|T], DIFF, CNT) :-
    getDifferentElems(T, TDIFF, TCNT),
    getNewCntAndDiff(H, TDIFF, TCNT, DIFF, CNT).


generateNoBetween(M, M, M) :- !.
generateNoBetween(MIN, _, MIN).
generateNoBetween(MIN, MAX, GEN) :-
    MIN1 is MIN + 1,
    generateNoBetween(MIN1, MAX, GEN).

getColor(M, C) :-
    generateNoBetween(1, M, C).

checkColor(LSTC, C) :-
    LSTC =\= C.

colourMap(N, _, CSF, N, CSF) :- !.
colourMap(N, M, [H|T], LEN, SOL) :-
    getColor(M, C),
    checkColor(H, C),
    LEN1 is LEN + 1,
    colourMap(N, M, [C|[H|T]], LEN1, SOL).

colourMapMain(N, M, SOL) :-
    getColor(M, C),
    colourMap(N, M, [C], 1, SOL),
    getDifferentElems(SOL, _, CNT),
    CNT =:= M.