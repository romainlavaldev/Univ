public class Rationnel{
    private int p;
    private int q;

    //CONSTRUCTORS
    public Rationnel(int p, int q){
        this.p = p;
        this.q = q;
    }

    //CLASS METHODS
    public static Rationnel moyenne(Rationnel[] t){
        Rationnel somme = t[0];
        for (int i = 1; i < t.length; i++) {
            somme = somme.somme(t[i]);
        }

        return somme.quotient(new Rationnel(t.length, 1));
    }

    public static Rationnel[] system(int a, int b, int c, int d, int e, int f){
        Rationnel[] solution = new Rationnel[2];
        solution[0] = null;
        solution[1] = null;

        int determinant = a*e - b*d;

        if (determinant == 0){
            return solution;
        }else{
            solution[0] = new Rationnel(b*f - c*e, determinant);
            solution[1] = new Rationnel(c*d - a*f, determinant);
        }
        return solution;
    }



    public static Rationnel sqrt(Rationnel r, Rationnel precision){

        Rationnel uk1 = r.quotient(new Rationnel(2, 1));
        Rationnel uk;
        Rationnel tmp;

        do {
            
            uk = new Rationnel(1, 2).produit( uk1.somme( r.quotient(uk1) ) );
            tmp = uk1.clone();
            uk1 = uk.clone();

        } while (tmp.difference(uk).abs().compareTo(precision) >= 0);

        return uk;
    }

    public static Rationnel std(Rationnel[] t, Rationnel precision){
        Rationnel moy = moyenne(t);

        Rationnel s = t[0].difference(moy).produit(t[0].difference(moy));

        for (int i = 1; i < t.length; i++) {
            s.somme(t[i].difference(moy).produit(t[i].difference(moy)));
        }

        Rationnel total = s.produit(new Rationnel(1, t.length));

        return sqrt(total.simplify(), precision);

    }


    //METHODS
    public int nom(){
        return p;
    }

    public int den(){
        return q;
    }

    public double toDouble(){
        return (double)p/q;
    }

    public Rationnel somme(Rationnel r){
        return new Rationnel(this.nom() * r.den() + this.den() * r.nom(), this.den() * r.den());
    }

    public Rationnel difference(Rationnel r){
        return new Rationnel(this.nom() * r.den() - this.den() * r.nom(), this.den() * r.den());
    }

    public Rationnel produit(Rationnel r){
        return new Rationnel(this.nom() * r.nom(), this.den() * r.den());
    }

    public Rationnel quotient(Rationnel r){
        return this.produit(new Rationnel(r.den(), r.nom()));
    }

    public String toString() {
        return p+"/"+q;
    }

    public int compareTo(Rationnel r){
        int nomThis = this.nom() * r.den();
        int nomR = r.nom() * this.den();

        return (nomThis == nomR) ? 0:nomThis-nomR;
    }

    public Rationnel abs(){
        return new Rationnel((nom() < 0 ) ? -nom():nom(), (den() < 0 ) ? -den():den());
    }

    protected Rationnel clone(){
        return new Rationnel(nom(), den());
    }

    public Rationnel simplify(){
        int pgcd = 0;

        for(int i=1; i <= nom() && i <= den(); i++)
        {
            if(nom()% i==0 && den()%i==0)
                pgcd = i;
        }

        if (pgcd != 0){
            return new Rationnel(nom()/pgcd, den()/pgcd);
        }else{
            return this;
        }
    }

}
