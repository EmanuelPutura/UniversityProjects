reverse([], C, C) :- !.
reverse([H|T], C, R) :-
    reverse(T, [H|C], R).

reverseMain(LST, R) :-
    reverse(LST, [], R).