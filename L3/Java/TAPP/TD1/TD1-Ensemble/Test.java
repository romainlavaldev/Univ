public class Test {
    public static void main(String[] args) {
        System.out.println("START");
        
        System.out.println("e1 random :");
        EnsembleDeChiffre e1 = new EnsembleDeChiffre();
        e1.tirerAuHasard();
        e1.afficher();

        System.out.println("e2 random :");
        EnsembleDeChiffre e2 = new EnsembleDeChiffre();
        e2.tirerAuHasard();
        e2.afficher();

        if (e1.estInclusDans(e2)){
            System.out.println("e1 est inclus dans e2");
        }else{
            System.out.println("e1 n'est pas inclus dans e2");
        }

        
        System.out.println("e1 && e2 :");
        e2.unionAvec(e1).afficher();

        
        System.out.println("e1 :");
        e1 = new EnsembleDeChiffre();
        e1.ajoute(2);
        e1.ajoute(3);
        e1.ajoute(5);
        e1.afficher();

        
        System.out.println("e2 :");
        e2 = new EnsembleDeChiffre();
        e2.ajoute(0);
        e2.ajoute(2);
        e2.ajoute(3);
        e2.ajoute(5);
        e2.ajoute(7);
        e2.ajoute(9);
        e2.afficher();

        if (e1.estInclusDans(e2)){
            System.out.println("e1 est inclus dans e2");
        }else{
            System.out.println("e1 n'est pas inclus dans e2");
        }
        
        System.out.println("END");
    }
}
