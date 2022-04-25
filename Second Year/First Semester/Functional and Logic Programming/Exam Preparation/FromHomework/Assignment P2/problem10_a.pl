checkIfPrime(N, D) :-
    D * D > N,
    !.
checkIfPrime(N, D) :-
    mod(N, D) =:= 0,
    !,
    fail.
checkIfPrime(N, D) :-
    D1 is D + 2,
    checkIfPrime(N, D1).

isPrime(N) :-
    N < 2,
    !,
    fail.
isPrime(N) :-
    N =:= 2,
    !.
isPrime(N) :-
    mod(N, 2) =:= 0,
    !,
    fail.
isPrime(N) :-
    checkIfPrime(N, 3).
  
getRetVal(H, RR, [H|[H|RR]]) :-
    isPrime(H),
    !.
getRetVal(H, RR, [H|RR]).

writeTwicePrimes([], []) :- !.
writeTwicePrimes([H|T], R) :-
    writeTwicePrimes(T, RR),
    getRetVal(H, RR, R).
    
