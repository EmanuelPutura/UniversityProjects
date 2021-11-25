% insertOnEveryPos(𝑙1𝑙2…𝑙𝑛, 𝑒) =
% 	𝑒 ⊕ 𝑙1,𝑙2 … 𝑙𝑛,
%	𝑙1 ⊕ insertOnEveryPos(𝑙2…𝑙𝑛, e).
%	
% insertOnEveryPos(L - list, E - number, R - list)
% flow model: (i, i, o), (i, o, i), (o, i, i), (o, o, i)
insertOnEveryPos(L, E, [E | L]).
insertOnEveryPos([H | T], E, [H | R]) :-
    insertOnEveryPos(T, E, R).

% abs(a, b) =
%	a - b, if a >= b,
%	b - a, otherwise.
%
% abs(A - number, B - number, R - number)
% flow model: (i, i, o), (i, i, i)
abs(A, B, R) :-
    A >= B,
    !,
    R is A - B.
abs(A, B, R) :-
    R is B - A.

% Checks if for element EL (which has index POS), there exists at least an 
% index < POS that respects the given constraint
%
% checkConstraint(l1l2...ln, EL, POS) =
% 	false, if POS <= 0,
%   true,  if abs(l1, EL) = 1,
%   checkConstraint(l2...ln, EL, POS - 1), otherwise.
%
% checkConstraint(L - list, EL - number, POS - number)
% flow model: (i, i, i)
checkConstraint(_, _, POS) :-
    POS =< 0,
    !,
    fail.
checkConstraint([H | _], EL, _) :-
    abs(H, EL, 1),
    !.
checkConstraint([_ | T], EL, POS) :-
    NPOS is POS - 1,
	checkConstraint(T, EL, NPOS).

% check(l1l2...ln, c1c2...cm, CRT) = 
% 	true, if m = 0,
% 	check(L, c2...cm, CRT + 1), if checkConstraint(L, c1, CRT),
% 	check(L, c2...cm, CRT + 1), if CRT = 1,
% 	false, otherwise.
%
% check(L - list, CRTL - list, CRT - number)
% flow model: (i, i, i)
check(_, [], _) :- !.
check(L, [H | T], CRT) :-
    checkConstraint(L, H, CRT),
    !,
    NCRT is CRT + 1,
    check(L, T, NCRT).
check(L, [_ | T], CRT) :-
    CRT is 1,
    NCRT is CRT + 1,
    check(L, T, NCRT).

% mainCheck(l1l2...ln) = check(l1l2...ln, l1l2...ln, 1).
% mainCheck(L - list)
% flow model: (i)
mainCheck(L) :-
    check(L, L, 1).

% checkPermutation(l1l2...ln, CNT, RCNT) =
% 	mainCheck(l1l2...ln), if CNT = RCNT,
%	true, otherwise.
%
% checkPermutation(L - list, CNT - number, RCNT - number)
% flow model: (i, i, i)
% RCNT is equal to N, CNT is the RCNT - current length of the permutation
checkPermutation(L, RCNT, RCNT) :-
    !,
    mainCheck(L).
checkPermutation(_, _, _).

% perm(l1l2...ln, CNT, RCNT) =
% 	∅, 𝑖𝑓 𝑙 𝑖𝑠 𝑒𝑚𝑝𝑡𝑦 and CNT = 0,
%   p = insertOnEveryPos(perm(l2l3...ln, CNT - 1, RCNT), l1), 
%   		if checkPermutation(p, CNT, RCNT).
%
% perm(L - list, CNT - number, RCNT - number, R - list)
% flow model: (i, i, i, o), ), (i, i, i, i)
perm([], 0, _, []).
perm([H | T], CNT, RCNT, R) :-
    NCNT is CNT - 1,
    perm(T, NCNT, RCNT, RR),
    insertOnEveryPos(RR, H, R),
    checkPermutation(R, CNT, RCNT).

% permMain(l1l2...ln, CNT) = perm(l2l2...ln, CNT, CNT).
% permMain(L - list, CNT - number, R - List)
% flow model: (i, i, o), (i, i, i)
permMain(L, CNT, R) :-
    perm(L, CNT, CNT, R).

permFindAll(L, CNT, RR) :-
    findall(R, permMain(L, CNT, R), RR).