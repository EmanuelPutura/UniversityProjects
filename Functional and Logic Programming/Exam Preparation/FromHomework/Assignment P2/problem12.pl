getDivisors(N, D, D) :-
    D < N,
    mod(N, D) =:= 0.
getDivisors(N, D, R) :-
    D1 is D + 1,
    D1 < N,
    getDivisors(N, D1, R).

getDivisorsMain(N, R) :-
    findall(RR, getDivisors(N, 2, RR), R).

reverse([], C, C) :- !.
reverse([H|T], C, R) :-
    reverse(T, [H|C], R).

appendList([], L, L) :- !.
appendList(L, [], L) :- !.
appendList([H1|T1], L, [H1|R]) :-
    appendList(T1, L, R).

addDivisorsAfterEveryElem([], []) :- !.
addDivisorsAfterEveryElem([H|T], R) :-
    addDivisorsAfterEveryElem(T, RR),
    getDivisorsMain(H, RHD),
    appendList([H|RHD], RR, R).

getRetVal(H, RR, [RH|RR]) :-
    is_list(H),
    !,
    addDivisorsAfterEveryElem(H, RH).
getRetVal(H, RR, [H|RR]).

addDivisorsInEverySublist([], []) :- !.
addDivisorsInEverySublist([H|T], R) :-
    addDivisorsInEverySublist(T, RR),
    getRetVal(H, RR, R).