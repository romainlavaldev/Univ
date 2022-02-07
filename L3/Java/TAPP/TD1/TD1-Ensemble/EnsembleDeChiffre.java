import java.lang.Math;

public class EnsembleDeChiffre {
    private boolean[] present;

    public EnsembleDeChiffre(){
        present = new boolean[10];
    }

    public void ajoute(int i){
        present[i] = true;
    }

    public void retire(int i){
        present[i] = false;
    }

    public void tirerAuHasard(){
        for (int i = 0; i < present.length; i++) {
            present[i] = (Math.random() > 0.5);
        }
    }

    public boolean appartient(int i){
        return present[i];
    }

    public EnsembleDeChiffre intersectionAvec(EnsembleDeChiffre e){
        EnsembleDeChiffre inter = new EnsembleDeChiffre();

        for (int i = 0; i < present.length; i++) {
            inter.present[i] = this.present[i] && e.present[i];
        }

        return inter;
    }

    public EnsembleDeChiffre unionAvec(EnsembleDeChiffre e){
        EnsembleDeChiffre union = new EnsembleDeChiffre();

        for (int i = 0; i < present.length; i++) {
            union.present[i] = this.present[i] || e.present[i];
        }

        return union;
    }

    public boolean estInclusDans(EnsembleDeChiffre e){
        return e.equals(this.unionAvec(e));
    }

    public boolean equals(Object obj) {
        if (obj instanceof EnsembleDeChiffre){
            EnsembleDeChiffre e = (EnsembleDeChiffre)obj;
            for (int i = 0; i < present.length; i++) {
                if(present[i] != e.present[i]){
                    return false;
                }
            }
            return true;
        }else{
            return false;
        }
    }

    public String toString() {
        String s = "{";

        for (int i = 0; i < present.length; i++) {
            if (present[i]){
                s += i + " ";
            }
        }

        s = s.trim() + "}";

        return s;
    }

    public void afficher(){
        System.out.println(this);
    }
}
