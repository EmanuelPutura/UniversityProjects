member([E|_], E) :- !.
member([_|T], E) :-
    member(T, E).
