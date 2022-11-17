package com.example;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.List;

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

public class PionTest{
    @BeforeAll
    public static void init(){

    }

    @Test
    public void CreateColoredPion(){
        Pion pWhite = new Pion(Color.WHITE);
        Pion pBlack = new Pion(Color.BLACK);

        assertEquals(Color.WHITE, pWhite.getColor());
        assertEquals(Color.BLACK, pBlack.getColor());
    }

    @Test
    public void MangerPion(){
        int [][] tabCoords = new int[2][2];
        tabCoords[0][0] = 5;
        tabCoords[0][1] = 5;
        tabCoords[1][0] = 4;
        tabCoords[1][1] = 4;

        Color [] tabColor = new Color[2];
        tabColor[0] = Color.WHITE;
        tabColor[1] = Color.BLACK;
        
        Plateau p = new Plateau(tabCoords, tabColor);

        Pion pion = p.getCase(4, 4).getPion();
        List<Case> listCase = Plateau.getDeplacement(p.getCase(4, 4));
        if(listCase.size() == 1){
            assertEquals(p.getCase(6,6), listCase.get(0));
        }
        
    }
}