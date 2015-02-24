import java.util.ArrayList;


public class Clause {

		ArrayList<Atome> disjonction;
		
		public Clause(){
			this.disjonction = new ArrayList<Atome>();
		}
		
		public Clause(ArrayList<Atome> disj){
			disjonction = disj;
		}
		
		public Clause(String disj){
			String [] list = disj.split(" ");
			for(int i = 0; i < list.length;i++){
				disjonction.add(new Atome(Integer.parseInt(list[i])));
			}
		}
		
		public String toString(){
			String res = "(";
			int i =0;
			for(Atome a : disjonction){
				if(i==disjonction.size()){
					res += a.toString() + ")";
				}else{
					res += a.toString() + ",";
				}
				i++;
			}
			return res;
		}
}
