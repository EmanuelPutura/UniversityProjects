generateSymbols(1).
generateSymbols(x).
generateSymbols(2).

reverse([], C, C) :- !.
reverse([H|T], C, R) :-
    reverse(T, [H|C], R).

reverseMain(LST, R) :-
    reverse(LST, [], R).

getNox(S, NOXSF, NOX) :-
    S = x,
    !,
    NOX is NOXSF + 1.
getNox(_, NOXSF, NOXSF).

predict(_, 3, _, []) :-
    !,
    fail.
predict(4, _, [HS|_], []) :-
    number(HS),
    HS =:= 2,
    !,
    fail.
predict(4, _, LST, LST) :- !.
predict(LEN, NOX, COL, SOL) :-
    generateSymbols(S),
    LEN1 is LEN + 1,
    getNox(S, NOX, NOX1),
    predict(LEN1, NOX1, [S|COL], SOL).

predictMain(SOL) :-
    predict(0, 0, [], SOL1),
    reverseMain(SOL1, SOL).
