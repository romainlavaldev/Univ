package com.example;

public class Case {
    private int x;
    private int y;
    private Color color;
    private Pion pion;
    
    public Case(int x, int y, Color c) {
        this.x = x;
        this.y = y;
        color = c;
    }

    public void setPion(Pion p){
        pion = p;
    }

    public Pion getPion(){
        return pion;
    }

    public boolean pionPresent(){
        return pion != null;
    }

    public Color getColor(){
        return color;
    }
}
