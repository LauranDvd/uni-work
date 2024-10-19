% (i, i) deterministic / (o, i) nondeterministic
% X: int, L: list
isInList(X, [X|_]).
isInList(X, [_|T]) :-
    isInList(X, T).

% (i, i, o) deterministic
% X: int, L: list, R: list
removeElem(X, [X|T], T) :- !.			
removeElem(X, [H|T], Res) :-
    removeElem(X, T, Res2),
    Res = [H|Res2].

% A: list, C: list, Res: list
% (i, i, o) nondeterministic
goodPermAux([], C, C).

goodPermAux(Available, [], Res) :-
    isInList(X, Available),
    removeElem(X, Available, AvWithoutX),
    goodPermAux(AvWithoutX, [X], Res).

goodPermAux(Available, [HC|TC], Res) :-
    isInList(X, Available),
    Predec is X - 1,
    isInList(Predec, [HC|TC]),
    
    removeElem(X, Available, AvWithoutX),
    goodPermAux(AvWithoutX, [X, HC|TC], Res).

goodPermAux(Available, [HC|TC], Res) :-
    isInList(X, Available),
    Succ is X + 1,
    isInList(Succ, [HC|TC]),
    
    removeElem(X, Available, AvWithoutX),
    goodPermAux(AvWithoutX, [X, HC|TC], Res).


% N: int, L: list
% (i, o) deterministic
getFirstNReverse(0, []) :- !.

getFirstNReverse(N, Res) :-
    MinusOne is N - 1,
    getFirstNReverse(MinusOne, Res2),
    Res = [N|Res2].

% same
getFirstN(N, Res) :-
    getFirstNReverse(N, Res2),
    reverse(Res2, Res).


% N: int, Res: list
% (i, o) nondeterministic
goodPerm(N, Res) :-
    getFirstN(N, FirstN),
    goodPermAux(FirstN, [], ResRev),
    reverse(ResRev, Res).
















