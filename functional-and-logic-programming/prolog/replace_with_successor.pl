% given a list comprising numbers and lists of numbers,
% replace each list with the successor, written in the same manner,
% of the number that's obtained by interpreting the list as a list of digits
% e.g.: [1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] ->
% [1, [2, 4], 4, 5, [6, 8, 0], 10, 11, [1, 2, 1], 6]

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


% successorInReverseNotation(L: list, R: result)
% flow models: (input, output) / (input, input).
successorInReverseNotation([], [1]) :-
    !.

successorInReverseNotation([9|T], Result) :-
    !,
    successorInReverseNotation(T, TailResult),
    Result = [0|TailResult].

successorInReverseNotation([H|T], Result) :-
    HplusOne is H + 1,
    Result = [HplusOne|T].

% successor(L: list, Result: list)
% flow model: (i, o) / (i, i)
successor(L, Result) :-
    isReverse(L, LReversed),
    successorInReverseNotation(LReversed, SuccessorReversed),
    isReverse(SuccessorReversed, Result).
  

% listsBecomeTheirSuccessor(L: list, Result: List)
% flow model: (i, o) / (i, i) / 
listsBecomeTheirSuccessor([], []) :-
    !.

listsBecomeTheirSuccessor([H|T], Result) :-
    number(H),
    !,
    listsBecomeTheirSuccessor(T, TailResult),
    Result = [H|TailResult].

listsBecomeTheirSuccessor([H|T], Result) :-
    successor(H, HSuccessor),
    listsBecomeTheirSuccessor(T, TailResult),
    Result = [HSuccessor|TailResult].














