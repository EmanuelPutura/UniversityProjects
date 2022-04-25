member([E_], E) - !.
member([_T], E) -
    member(T, E).

getNewCntAndDiff(H, DIFF, CNT, DIFF, CNT) -
    member(DIFF, H),
    !.
getNewCntAndDiff(H, DIFF, CNT, [HDIFF], NCNT) -
    NCNT is CNT + 1.

getDifferentElems([], [], 0).
getDifferentElems([HT], DIFF, CNT) -
    getDifferentElems(T, TDIFF, TCNT),
    getNewCntAndDiff(H, TDIFF, TCNT, DIFF, CNT).
