% isReverseWithCollector(L: list, Collector: list, Result: list)
% flow model: (input, input, output) / (input, input, input) /
% (input, output, input) -- not recommended
isReverseWithCollector([], Collector, Collector) :-
    !.

isReverseWithCollector([H|T], Collector, Result) :-
    NewCollector = [H|Collector],
    isReverseWithCollector(T, NewCollector, Result).

% isReverse(L: list, Result: list)
% flow model: (i, o) / (i, i) / (o, i)
isReverse(L, Result) :-
    isReverseWithCollector(L, [], Result).


% sumOfReversedNumbers(A: list, B: list, Carry: integer, Result: list)
% flow model: (i, i, i, o) / (i, i, i, i), 
sumOfReversedNumbers([], [], 0, []) :-
    !.

sumOfReversedNumbers([], [], Carry, [Carry]) :-
    !.

sumOfReversedNumbers([], B, 0, B) :-
    !.

sumOfReversedNumbers([], [HB|TB], Carry, Result) :-
    !,
    DigitHere is (HB + Carry) mod 10,
    NewCarry is (HB + Carry) div 10,
    sumOfReversedNumbers([], TB, NewCarry, Preresult),
    Result = [DigitHere|Preresult].

sumOfReversedNumbers(A, [], 0, A) :-
    !.

sumOfReversedNumbers([HA|TA], [], Carry, Result) :-
    !,
    DigitHere is (HA + Carry) mod 10,
    NewCarry is (HA + Carry) div 10,
    sumOfReversedNumbers(TA, [], NewCarry, Preresult),
    Result = [DigitHere|Preresult].

sumOfReversedNumbers([HA|TA], [HB|TB], Carry, Result) :-
    DigitHere is (HA + HB + Carry) mod 10,
    NewCarry is (HA + HB + Carry) div 10,
    sumOfReversedNumbers(TA, TB, NewCarry, Preresult),
    Result = [DigitHere|Preresult].

% sumOfNumbers(A: list, B: list, Result: list)
% flow: (i, i, o) / (i, i, i)
sumOfNumbers(A, B, Result) :-
    isReverse(A, AReversed),
    isReverse(B, BReversed),
    sumOfReversedNumbers(AReversed, BReversed, 0, ResultReversed),
    isReverse(ResultReversed, Result).


sumOfAllSublists([], []) :-
    !.

sumOfAllSublists([H|T], Result) :-
    number(H),
    !,
    sumOfAllSublists(T, Result).

sumOfAllSublists([H|T], Result) :-
    sumOfAllSublists(T, TailResult),
    sumOfNumbers(H, TailResult, Result).

