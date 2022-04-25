reverse([], C, C) :- !.
reverse([H|T], C, R) :-
    reverse(T, [H | C], R).

findLSCN([], MSF, _, _, _, MSF) :- !.
findLSCN([H|T], MSF, MSFL, _, _, R) :-
    mod(H, 2) =:= 1,
    !,
    findLSCN(T, MSF, MSFL, [], 0, R).
findLSCN([H|T], _, MSFL, _, SFL, R) :-
    SFL =:= 0,
    MSFL =:= 0,
    !,
    findLSCN(T, [H], 1, [H], 1, R).
findLSCN([H|T], MSF, MSFL, _, SFL, R) :-
    SFL =:= 0,
    !,
    findLSCN(T, MSF, MSFL, [H], 1, R).
findLSCN([H|T], _, MSFL, [SFH|SFT], SFL, R) :-
    SFH =:= H - 2,
    MSFL < SFL + 1,
    !,
    findLSCN(T, [H|[SFH|SFT]], SFL + 1, [H|[SFH|SFT]], SFL + 1, R).
findLSCN([H|T], MSF, MSFL, [SFH|SFT], SFL, R) :-
    SFH =:= H - 2,
    !,
    findLSCN(T, MSF, MSFL, [H|[SFH|SFT]], SFL + 1, R).
findLSCN([H|T], MSF, MSFL, _, _, R) :-
    findLSCN(T, MSF, MSFL, [H], 1, R).

findLSCNMain(L, R) :-
    findLSCN(L, [], 0, [], 0, RR),
    reverse(RR, R).
