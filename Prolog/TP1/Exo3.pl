couleur(rouge).
couleur(jaune).
couleur(vert).
couleur(bleu).

voisin(A,B):- couleur(A), couleur(B), A\=B.

carte(A,B,C,D,E,F):-
    voisin(A,C), voisin(A,B), voisin(A,E), voisin(A,F),
    voisin(B,C), voisin(B,D), voisin(B,F), voisin(B,E),
    voisin(C,D), voisin(C,F),
    voisin(E,F).


