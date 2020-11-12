vend(paul,basse,60).
vend(loic,livre,10).
vend(zoe,dvd,10).
vend(tom, livre, 15).
vend(tim,tshirt,20).
vend(tim,jeu,40).

achete(john,basse, 50).
achete(zoe, livre, 15).
achete(tom,dvd,15).
achete(tim,basse,80).
achete(loic,jeu,10).
achete(tom,jeu,30).

achat(A,V,O,P) :- vend(V,O,P), achete(A,O,Pmax), P =< Pmax.

troc(X,Y,O1,O2) :- vend(X,O1,P1), achete(Y,O1,P2), vend(Y,O2,P3), achete(X,O2,P4), compatible(P1,P2,P3,P4).

compatible(X,_,X,_).
compatible(_,Y,_,Y).

marche_conclu(X,Y,vente) :- achat(X,Y,_,_).
marche_conclu(X,Y,troc) :- troc(X,Y,_,_).
