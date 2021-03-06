import java.io.BufferedReader;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetSocketAddress;
import java.net.MalformedURLException;
import java.net.Proxy;
import java.net.URL;
import java.net.URLConnection;
import java.util.HashMap;


public class Main {
	
	static HashMap<String, String>dico = new HashMap<String,String>();
	
	public static void main(String[] args) throws IOException{
		dico.put("FMIN215","Algorithmique Géométrique - FMIN215");
		dico.put("GMIN20A","Algorithmique d'exploration et de mouvement - GMIN20A");
		dico.put("GMIN212","Modélisation et programmation - GMIN212");
		dico.put("GMIN215","Analyse et traitement d'images - GMIN215");
		dico.put("GMIN21C","Conduite de projets - GMIN21C");
		
		
		Date t = new Date();
		String host = "http://www.tom2ade.univ-montp2.fr/jsp/custom/modules/plannings/anonymous_cal.jsp?resources=2471,3161,3213,3216,3299&projectId=12&calType=ical&firstDate="+t.getDateDeb()+"&lastDate="+t.getDateFin();
		
		URL url;
		try {
			url = new URL(host);
			Proxy proxy = new Proxy(Proxy.Type.HTTP, new InetSocketAddress("162.38.218.204", 3128));
			URLConnection conn = new URL(host).openConnection(proxy);
			
			java.io.InputStream input = conn.getInputStream();
			String fileName = url.getFile().substring(url.getFile().lastIndexOf('/') + 1);
			FileOutputStream writeFile = new FileOutputStream(fileName);
			FileWriter fichier = new FileWriter("EdTM1"+".ics");
			
			try{
				//FileInputStream ips=new FileInputStream(input); 
				InputStreamReader ipsr=new InputStreamReader(input);
				BufferedReader br=new BufferedReader(ipsr);
				String ligne;
				while ((ligne=br.readLine())!=null){
					String[] spl = ligne.split(":");
					if(spl[0].equals("SUMMARY")){
						ligne = "SUMMARY:"+dico.get(spl[1]);
					}
					fichier.write(ligne+"\n");
				}
				br.close(); 
				fichier.close();
			}		
			catch (Exception e){
				System.out.println(e.toString());
			}
			

		} catch (MalformedURLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}

}
