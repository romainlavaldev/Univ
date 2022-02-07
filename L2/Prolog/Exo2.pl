max(A,B,G) :- A > B ,G is A.
max(A,B,G) :- A =< B ,G is B.

min(A,B,M) :- A < B, M is A.
min(A,B,M) :- A >= B, M is A.

max(A,B,C,G) :- max(A,B,G1), max(G1,C,G2), G is G2.
min(A,B,C,M) :- min(A,B,M1), min(M1,C,M2), M is M2.

mediane(A,B,C,A) :- max(A,B,C,B), min(A,B,C,C).
mediane(A,B,C,A) :- min(A,B,C,B), max(A,B,C,C).
mediane(A,B,C,B) :- max(A,B,C,A), min(A,B,C,C).
mediane(A,B,C,B) :- min(A,B,C,A), max(A,B,C,C).
mediane(A,B,C,C) :- max(A,B,C,A), min(A,B,C,B).
mediane(A,B,C,C) :- min(A,B,C,A), max(A,B,C,B).
