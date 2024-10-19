% given a list which has both i) integers and ii) linear sublists of integers,
% add after each number encountered in a linear sublist its divisors, except 1 and itself
% e.g.:  [1, [2, 5, 7], 4, 5, [1, 4], 3, 2, [6, 2, 1], 4, [7, 2, 8, 1], 2]
% -> [1, [2, 5, 7], 4, 5, [1, 4, 2], 3, 2, [6, 2, 3, 2, 1], 4, [7, 2, 8, 2, 4, 1], 2] 

appendLists([], B, B) :-
    !.

appendLists([HA|TA], B, Result) :-
    appendLists(TA, B, TailResult),
    Result = [HA|TailResult].


% (X: integer, StartDiv: integer, Result: list)
% flow model: (i, i, o) / (i, i, i)
getAllDivisorsHigherThan(1, _, []) :-
    !.

getAllDivisorsHigherThan(X, X, []) :- 
    !.

getAllDivisorsHigherThan(X, StartDiv, Result) :-
    XmodStartDiv is X mod StartDiv,
    XmodStartDiv =:= 0,
    !,
    NextStartDiv is StartDiv + 1,
    getAllDivisorsHigherThan(X, NextStartDiv, SmallResult),
    Result = [StartDiv|SmallResult].

getAllDivisorsHigherThan(X, StartDiv, Result) :-
    NextStartDiv is StartDiv + 1,
    getAllDivisorsHigherThan(X, NextStartDiv, Result).


% (X: integer, Result: list)
% flow model: (i, o) / (i, i)
getAllDivisors(X, Result) :-
    getAllDivisorsHigherThan(X, 2, Result).


% (L: linear list, Result: linear list)
% flow model: (i, o) / (i, i)
insertTheirDivisorsAfterNumbersInLinearList([], []) :-
    !.

insertTheirDivisorsAfterNumbersInLinearList([H|T], Result) :-
    getAllDivisors(H, HsDivisors),
    insertTheirDivisorsAfterNumbersInLinearList(T, TailResult),
	appendLists(HsDivisors, TailResult, ResultWithoutH),
    Result = [H|ResultWithoutH].
    

% (L: list of integers and linear lists, Result: same)
% flow model: (i, o) / (i, i)
insertTheirDivisorsAfterNumbersFromSublists([], []) :-
    !.

insertTheirDivisorsAfterNumbersFromSublists([H|T], Result) :-
	number(H),
    !,
    insertTheirDivisorsAfterNumbersFromSublists(T, TailResult),
    Result = [H|TailResult].

insertTheirDivisorsAfterNumbersFromSublists([H|T], Result) :-
    insertTheirDivisorsAfterNumbersInLinearList(H, HAfterInsertions),
    insertTheirDivisorsAfterNumbersFromSublists(T, TailResult),
    Result = [HAfterInsertions|TailResult].


