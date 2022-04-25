reverse([], C, C) :- !.
reverse([H|T], C, R) :-
    reverse(T, [H|C], R).

reverseMain(LST, R) :-
    reverse(LST, [], R).

generateOneParan(ONO, CNO, NONO, CNO, "(") :-
    ONO >= CNO,
    NONO is ONO + 1.
generateOneParan(ONO, CNO, ONO, NCNO, ")") :-
    ONO > CNO,
    NCNO is CNO + 1.

generateParanthesis(N, N, CNT, CNT, C, C) :- !.
generateParanthesis(N, N, _, _, C, C) :-
    !,
    fail.
generateParanthesis(N, NSF, ONO, CNO, C, R) :-
    generateOneParan(ONO, CNO, NONO, NCNO, GP),
    NSF1 is NSF + 1,
    generateParanthesis(N, NSF1, NONO, NCNO, [GP|C], R).

generateParanthesisMain(N, SOL) :-
    generateParanthesis(N, 0, 0, 0, [], SOL1),
    reverseMain(SOL1, SOL).
