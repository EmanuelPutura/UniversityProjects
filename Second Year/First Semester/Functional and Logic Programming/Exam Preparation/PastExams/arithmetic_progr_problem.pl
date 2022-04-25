subsetsHelper(RR, _, CNT1, RR, CNT1).
subsetsHelper(RR, H, CNT1, [H|RR], CNT) :-
    CNT is CNT1 + 1.

subsets([], [], 0).
subsets([H|T], R, CNT) :-
    subsets(T, RR, CNT1),
    subsetsHelper(RR, H, CNT1, R, CNT).
    
getOdd([], [], 0).
getOdd([H|T], [H|R], LEN1) :-
    mod(H, 2) =:= 1,
    !,
    getOdd(T, R, LEN),
    LEN1 is LEN + 1.
getOdd([_|T], R, LEN) :-
    getOdd(T, R, LEN).

insertOnCorrectPos([], EL, [EL]).
insertOnCorrectPos([H|T], EL, [EL|[H|T]]) :-
	EL < H,
    !.
insertOnCorrectPos([H|T], EL, [H|RR]) :-
    insertOnCorrectPos(T, EL, RR).

sortList([], []).
sortList([H|T], R) :-
    sortList(T, RR),
    insertOnCorrectPos(RR, H, R).    

check([], _, _) :- !.
check([H|T], LST, DIFF) :-
    DIFF is H - LST,
    check(T, H, DIFF).

checkMain([]) :- !.
checkMain([_]) :- !.
checkMain([H1, H2 | T]) :-
    DIFF is H2 - H1,
    check(T, H2, DIFF).

solve1(LST, K, R) :-
    subsets(LST, RS, _),
    getOdd(RS, RO, OLEN),
    OLEN is K,
    sortList(RO, R),
    checkMain(R).

solve2(LST, K, R) :-
    getOdd(LST, ODD, _),
    sortList(ODD, RR),
    subsets(RR, R, LEN),
    LEN =:= K,
    checkMain(R).
