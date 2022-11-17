package com.example;


import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.*;

/**
 * Unit test for simple App.
 */
public class PlateauTest 
{

    private static Plateau plateau;
    private static Case[][] cases;

    @BeforeAll
    public static void init(){
        plateau = new Plateau();
        cases = plateau.getCases();
    }

    /**
     * Rigorous Test :-)
     */
    @Test
    public void TestNbCasesPlateau()
    {
        assertEquals(100, plateau.getCases().length * plateau.getCases()[0].length);

        for (int i = 0; i < cases.length; i++) {
            for (int j = 0; j < cases[0].length; j++) {
                assertEquals(Case.class, cases[i][j].getClass());
            }
        }
    }

    @Test
    public void TestPositionsPionsDepart(){
        
        
        //4 premieres lignes
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < cases[i].length; j++) {
                if (cases[i][j].getColor() == Color.BLACK){
                    assertTrue(cases[i][j].pionPresent());
                }
            }
        }

        //4 dernieres lignes
        for (int i = cases.length - 4; i < cases.length; i++) {
            for (int j = 0; j < cases[i].length; j++) {
                if (cases[i][j].getColor() == Color.BLACK){
                    assertTrue(cases[i][j].pionPresent());
                }
            }
        }
    }

    @Test
    public void TestDeplacementPion(){
        System.out.println(plateau);
        plateau.deplacerPion(3, 0, 4, 1);
        assertTrue(cases[4][1].pionPresent());
        assertTrue(!cases[3][0].pionPresent());
        System.out.println(plateau);
    }
}
