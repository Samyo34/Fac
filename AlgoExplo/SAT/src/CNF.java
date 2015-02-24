import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;


public class CNF {
	
	ArrayList<Clause> conjonction;
	
	public CNF(){
		conjonction = new ArrayList<Clause>();
	}
	
	public CNF(ArrayList<Clause> conj){
		this.conjonction = conj;
	}
	
	public CNF(File fichier) throws FileNotFoundException{
		InputStream in =new FileInputStream(fichier); 
		InputStreamReader ipsr=new InputStreamReader(in);
		BufferedReader br=new BufferedReader(ipsr);
		String ligne;
		try {
			while((ligne = br.readLine()) != null){
				conjonction.add(new Clause(ligne));
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			System.err.println("erreur lors de la lecture du fichier CNF");
			e.printStackTrace();
		}
		try {
			br.close();
			ipsr.close();
			in.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			System.err.println("erreur lors de la fermeture des flux CNF");
			e.printStackTrace();
		}
		
		
	}
	
	public String toString(){
		String res = "(";
		int i = 0;
		for(Clause c : conjonction){
			if(i==conjonction.size()){
				res += c.toString() + "]";
			}else{
				res += c.toString() + ",";
			}
			i++;
		}
		return res;
	}
}
