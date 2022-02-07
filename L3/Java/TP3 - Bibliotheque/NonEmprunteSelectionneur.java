/**
* @author LeNomDeLEtudiant
* @version 0.1 : Date : Mon Jan 24 13:52:02 CET 2022
*
*/
public class NonEmprunteSelectionneur implements Selectionneur{

	@Override
	public boolean estSatisfaitPar(Document d){
		return !d.getEmprunte();
	}
}