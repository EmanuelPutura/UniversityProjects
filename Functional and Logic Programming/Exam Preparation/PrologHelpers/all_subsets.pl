getSubsetsSol(_, R, R).
getSubsetsSol(H, R, [H|R]).
    
generateAllSubsets([], []).
generateAllSubsets([H|T], SOL) :-
    generateAllSubsets(T, R),
    getSubsetsSol(H, R, SOL).
    
generateAllSubsetsMain(LST, R) :-
    findall(SOL, generateAllSubsets(LST, SOL), R).