entree(crdit�s, 6).
entree(taboul�, 8).
entree(avocat, 5).

plat(couscous, 12).
plat(risotto, 10).
plat(lasagnes, 12).

dessert(glace, 6).
dessert(fruits, 5).
dessert(gateau, 8).

menu(C1,C2,P) :- entree(C1,PE), plat(C2,PPl), P is PE + PPl.
menu(C1,C2,P) :- plat(C1,PPl), dessert(C2,PD), P is PPl + PD.
