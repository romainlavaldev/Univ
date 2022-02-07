public class Test {
    public static void main(String[] args) {
        System.out.println("START");

        Rationnel a = new Rationnel(2, 3);
        System.out.println("a : " + a.toString());
        Rationnel b = new Rationnel(1, 2);
        System.out.println("b : " + b.toString());

        System.out.println("a+b : " + a.somme(b).toString());

        System.out.println("a*b : " + a.produit(b).toString());

        System.out.println("a/b : " + a.quotient(b).toString());

        System.out.println("Comparaison a b : " + a.compareTo(b));

        
        System.out.println("abs -7/2 : " + new Rationnel(-7, 2).abs());

        Rationnel[] t = new Rationnel[2];
        t[0] = new Rationnel(4, 2);
        t[1] = new Rationnel(24, 4);

        System.out.println("moyenne du tableau : 4/2 - 24/4 : " + Rationnel.moyenne(t));

        System.out.println("- EQUATION -");
        System.out.println("système: ");
        System.out.println("3x + 5y - 4 = 0");
        System.out.println("2x - 3y + 1 = 0");

        System.out.println("Solutions : ");
        Rationnel[] solution = Rationnel.system(3, 5, -4, 2, -3, 1);
        System.out.println("x = " + solution[0].toString());
        System.out.println("y = " + solution[1].toString());

        Rationnel racine2 = Rationnel.sqrt(new Rationnel(2, 1), new Rationnel(1, 100));

        System.out.println("Racine de 2 à 1/100 de précision : " + racine2 + " (" + racine2.toDouble() + ")");

        System.out.println("24/6 simplifié : " + new Rationnel(24, 6).simplify());

        System.out.println("Ecart-type du tableau : 4/2 - 24/4 : " + Rationnel.std(t, new Rationnel(1, 10)));

        System.out.println("END");
    }
}
