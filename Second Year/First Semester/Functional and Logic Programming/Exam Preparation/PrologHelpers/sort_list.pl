insertOnCorrectPos([], EL, [EL]) :- !.
insertOnCorrectPos([H|T], EL, [EL|[H|T]]) :-
	EL < H,
    !.
insertOnCorrectPos([H|T], EL, [H|RR]) :-
    insertOnCorrectPos(T, EL, RR).

sortList([], []) :- !.
sortList([H|T], R) :-
    sortList(T, RR),
    insertOnCorrectPos(RR, H, R).
   