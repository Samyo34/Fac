
public class Atome {
	int valeur;
	
	public Atome(){
		valeur = 0;
	}
	
	public Atome(int valeur){
		this.valeur = valeur;
	}
	
	public int getValeur(){
		return valeur;
	}
	
	public void setValeur(int val){
		this.valeur = val;
	}
	
	public String toString(){
		return String.valueOf(valeur);
	}
}
