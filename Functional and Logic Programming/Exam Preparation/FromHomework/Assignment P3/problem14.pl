getSol(_, SOL1, SUM1, SOL1, SUM1).
getSol(H, SOL1, SUM1, [H|SOL1], SUM) :-
    SUM is SUM1 + H.

subsets([], [], 0) :- !.
subsets([H|T], SOL, SUM) :-
    subsets(T, SOL1, SUM1),
    getSol(H, SOL1, SUM1, SOL, SUM).
    
solve(LST, S, SOL) :-
    subsets(LST, SOL, SUM),
    SUM =:= S.
