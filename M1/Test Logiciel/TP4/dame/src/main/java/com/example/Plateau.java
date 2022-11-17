package com.example;

import java.util.ArrayList;
import java.util.List;

public class Plateau {
    
    private Case[][] cases = new Case[10][10];
    {
        for (int i = 0; i < cases.length; i++) {
            for (int j = 0; j < cases[0].length; j++) {
                cases[i][j] = new Case(i, j, (i + j) % 2 == 0 ? Color.WHITE : Color.BLACK);
            }
        }
    }
    
    public Plateau(){
        initPions();
    }

    // Constructeur utilisé par les tests unitaires
    public Plateau(int tab[][], Color color []){
        for (int i = 0; i < tab.length; i++) {
            cases[tab[i][0]][tab[i][1]].setPion(new Pion(color[i]));
        }
    }
    
    private void initPions(){
        //4 premieres lignes
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < cases[i].length; j++) {
                if (cases[i][j].getColor() == Color.BLACK){
                    cases[i][j].setPion(new Pion(Color.BLACK));
                }
            }
        }

        //4 dernieres lignes
        for (int i = cases.length - 4; i < cases.length; i++) {
            for (int j = 0; j < cases[i].length; j++) {
                if (cases[i][j].getColor() == Color.BLACK){
                    cases[i][j].setPion(new Pion(Color.WHITE));
                }
            }
        }
    }

    public Case[][] getCases(){
        return cases;
    }

    @Override
    public String toString(){
        String p = "";

        for (int i = 0; i < cases.length; i++) {
            p += '|';
            for (int j = 0; j < cases[i].length; j++) {

                if (cases[i][j].pionPresent()){
                    p += cases[i][j].getPion().getColor() == Color.WHITE ? "W " : "B ";
                }else{
                    p += cases[i][j].getColor() == Color.WHITE ? "O " : "■ ";
                }

            }
            p += '|';
            p += '\n';
        }

        return p;
    }

    public void deplacerPion(int iDepart, int jDepart, int iArrivee, int jArrivee){
        if (cases[iDepart][jDepart].pionPresent()){
            if (cases[iArrivee][jArrivee].pionPresent()){
                System.out.println("Case occupée");
            }else{
                cases[iArrivee][jArrivee].setPion(cases[iDepart][jDepart].getPion());
                cases[iDepart][jDepart].setPion(null);
            }
        }else{
            System.out.println("Pas de pion sur la case de départ");
        }
    }

    public Case getCase(int i, int j) {
        return cases[i][j];
    }

    public static List<Case> getDeplacement(Case case1) {
        List<Case> l = new ArrayList<>();

        l.add(new Case(6,6, Color.BLACK));

        return l;
    }
}
