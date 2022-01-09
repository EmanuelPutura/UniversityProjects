getAscendingSublist(_, _, R, R).
getAscendingSublist(H, _, [], [H]) :- !.
getAscendingSublist(H, [H1|_], [HH|TT], [H|[HH|TT]]) :-
    H < HH,
    H1 is HH.
    
ascendingSublists([_], []).
ascendingSublists([H], [H]).
ascendingSublists([H|T], SOL) :-
    ascendingSublists(T, R),
    getAscendingSublist(H, T, R, SOL).
