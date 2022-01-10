getSolutions(_, R, S, R, S).
getSolutions(H, R, S, [H|R], SOLS) :-
    SOLS is S + H.
    
subsets([], [], 0).
subsets([H|T], SOL, SOLS) :-
    subsets(T, R, S),
    getSolutions(H, R, S, SOL, SOLS).

findSubsetsWithProperty(LST, N, SOL) :-
    subsets(LST, SOL, S),
    mod(S, N) =:= 0.
