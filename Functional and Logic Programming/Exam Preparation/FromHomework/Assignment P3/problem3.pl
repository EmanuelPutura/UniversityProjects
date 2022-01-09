genNatNosLessThan(0, 0) :- !.
genNatNosLessThan(N, GEN) :-
    N1 is N - 1,
    genNatNosLessThan(N1, GEN).
genNatNosLessThan(N, N).

findSumDecomp(N, N, SOL, SOL) :- !.
findSumDecomp(N, CSUM, _, []) :-
    CSUM > N,
    !,
    fail.
findSumDecomp(N, CSUM, [H|T], SOL) :-
    H1 is H + 1,
    CSUM1 is CSUM + H1,
    findSumDecomp(N, CSUM1, [H1|[H|T]], SOL).
    

findSumDecompMain(N, SOL) :-
    genNatNosLessThan(N, R),
    findSumDecomp(N, R, [R], SOL).
   