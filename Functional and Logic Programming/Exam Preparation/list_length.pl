listLength([], 0) :- !.
listLength([_|T], L) :-
    listLength(T, LL),
    L is LL + 1.