removeElemFromBeginningSorted([], _, []) :- !.
removeElemFromBeginningSorted([H|T], H, R) :-
    !,
	removeElemFromBeginningSorted(T, H, R).
removeElemFromBeginningSorted([H|T], _, [H|T]).
    
getReturnVal1(H, H, R, R) :- !.
getReturnVal1(H, _, R, [H|R]).

removeDuplicatesSorted([], _, []) :- !.
removeDuplicatesSorted([H|T], E, RR) :-
    removeDuplicatesSorted(T, H, R),
    getReturnVal1(H, E, R, RR).

removeDuplicatesSortedMain([H|T], [H|R]) :-
    removeDuplicatesSorted(T, H, R).

mergeSortedWithoutDuplicates([], [], []) :- !.
mergeSortedWithoutDuplicates([H1|T1], [], R) :-
    !,
    removeDuplicatesSortedMain([H1|T1], R).
mergeSortedWithoutDuplicates([], [H2|T2], R) :-
    !,
    removeDuplicatesSortedMain([H2|T2], R).
mergeSortedWithoutDuplicates([H1|T1], [H2|T2], [H1|RR]) :-
    H1 < H2,
    !,
    mergeSortedWithoutDuplicates(T1, [H2|T2], R),
    removeElemFromBeginningSorted(R, H1, RR).
mergeSortedWithoutDuplicates([H1|T1], [H2|T2], [H2|RR]) :-
    mergeSortedWithoutDuplicates([H1|T1], T2, R),
    removeElemFromBeginningSorted(R, H2, RR).

getReturnVal2(H, RR, R) :-
    is_list(H),
    !,
    mergeSortedWithoutDuplicates(H, RR, R).
getReturnVal2(_, RR, RR).

mergeAllSublists([], []) :- !.
mergeAllSublists([H|T], R) :-
    mergeAllSublists(T, RR),
    getReturnVal2(H, RR, R).
    