% given a list of points, find all subsets
% of 3 collinear points

% M, N, P: lists of 2 integers
% flow model: (input, input, input)
% deterministic
coll([XM, YM], [XN, YN], [XP, YP]) :-
	Left is (YN - YM) * (XP - XN),
  	Right is (XN - XM) * (YP - YN),
   	Left =:= Right.
    

% M, N: lists of 2 integers, L: list of lists of 2 integers,
% P: list of 2 integers
% flow model: (i, i, i, o) / (i, i, i, i)
%             nondeterministic / deterministic
onePointCollWith(M, N, [[XL1, YL1]|_], [XL1, YL1]) :-
    coll(M, N, [XL1, YL1]).

onePointCollWith(M, N, [_|T], Result) :-
    onePointCollWith(M, N, T, Result).
    

% M: list of 2 integers, L: list of lists of 2 integers,
% NP: list of 2 lists of 2 integers
% flow model: (i, i, o) / (i, i, i)
%             nondeterministic / deterministic
twoPointsCollWith(M, [[XL1, YL1]|T], [[XL1, YL1], [XP, YP]]) :-
    onePointCollWith(M, [XL1, YL1], T, [XP, YP]).

twoPointsCollWith(M, [_|T], [[XL1, YL1], [XP, YP]]) :-
    twoPointsCollWith(M, T, [[XL1, YL1], [XP, YP]]).


% L: list of lists of 2 integers, R: list of 3 lists of 2 integers
% flow model: (i, o) / (i, i)
% 				nondeterministic / deterministic
allColl([H|T], [H, [XN, YN], [XP, YP]]) :-
    twoPointsCollWith(H, T, [[XN, YN], [XP, YP]]).

allColl([_|T], [[XM, YM], [XN, YN], [XP, YP]]) :-
    allColl(T, [[XM, YM], [XN, YN], [XP, YP]]).
    
% L: list of lists of 2 integers, R: list of lists of 3 lists of 2 integers
% flow model: (i, o) / (i, i)
% deterministic / deterministic
allCollCollected(L, Result) :-
    findall(Points, allColl(L, Points), Result).
