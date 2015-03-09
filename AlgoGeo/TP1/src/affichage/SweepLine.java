package affichage;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Stroke;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Set;


public class SweepLine {
	Color sweepLineColor = Couleur.tb;
	int width, height;
	int pos, step, maxStep, stepWidth, posI;
	
	ArrayList<Segment> status; // la liste des segments qui croisent la ligne de balayage
	ArrayList<PointVisible> eventPoints = new ArrayList<PointVisible>(); // la liste des points g�n�rant des �v�nements (ie chgt de la sweepline
	Vue vue; // la vue qui contient les segments � �tudier
	
	public SweepLine(int n, int w, int h, Vue v){
		status = new ArrayList<Segment>();
		width = w;
		height = h;
		pos = 0;
		vue = v;
		stepWidth = w/100;
		step = 0;
		maxStep = w /stepWidth;
		eventPoints = rempEventPoint(vue.getSegments());
	}
	
	/*
	 * Rempli l'eventPoint avec les point important
	 * Retourne une liste de point trié de gauche à droite (en concervant les couplesgauche-droite) 
	 */
	public ArrayList<PointVisible> rempEventPoint(ArrayList<Segment> segments){
		ArrayList<PointVisible> points = new ArrayList<PointVisible>();
		for(Segment s : segments){
			points.add(s.gauche);
			points.add(s.droit);
		}
		return tri(points);
	}
	
	
	/*
	 * Tri les points (en gardant les couplent) en triant les points gauches
	 * A FAIRE !
	 */
	public ArrayList<PointVisible> tri(ArrayList<PointVisible> points){
		// TODO : pour chaque point gauche : trié du x le plus petit au plus grand (en concervant les couples)
		ArrayList<PointVisible> ptsTri =  new ArrayList<PointVisible>();
		int min;
		int posi = 0;// la position du point min
		boolean fin = false;
		while(!fin){
			min =points.get(0).x;// initialisation avec le premier element de la liste
			posi=0;
			for(int i =0;i<points.size();i+=2){
				if(points.get(i).x < min){
					min = points.get(i).x;
					posi = i;
				}
			}
			PointVisible p = points.get(posi);
			ptsTri.add(p);// ajout du point gauche a la liste trié
			ptsTri.add(points.get(pos+1)); // ajout du point droit a la liste trié
			pos++;
			points.remove(pos);// suppression du point droit de la liste
			pos--;
			points.remove(pos);// suppression du point gauche de la liste
			if(points.isEmpty()){// si la liste de point non trié est vide :
				fin = true;// on met fin au tri (il est terminé)
			}
		}
		
		return ptsTri;
	}
	
	
	public void dessine(Graphics2D g) {
		g.setColor(sweepLineColor);
		Stroke s = g.getStroke();
		g.setStroke(new BasicStroke(2));
		g.drawLine(pos,0,pos,height);
		g.setStroke(s);
	}

	// d�placement de la ligne de balayage	
	public void next() {
		step = step < maxStep ? step + 1 : 0; // si step < maxStep, step++ sinon  step = 0
		rempStatus();
		//if (status.size() > 0) {
				System.out.println(ballayage()+ " "+status.size());
		//	} else {
				pos = step * stepWidth;
		//}
		//videStatus();
	}
	
	// Rempli eventPoint avec les points evement (pour de debut et de fin de segement)
	public void rempEvenement(){
		for(Segment s : vue.getSegments()){
			eventPoints.add(s.getGauche());
			eventPoints.add(s.getDroit());
		}
	}
	
	// remplis status avec les segments qui croisent la SweepLine
	public void rempStatus(){
		//TODO : verifier que la sweepLine rentre dans les points evenements
		int i =0;
		while((i<eventPoints.size()-1)){
			if(eventPoints.get(i).x < pos && eventPoints.get(i+1).x > pos){
					Segment seg = new Segment(eventPoints.get(i), eventPoints.get(i+1));
					status.add(seg);
			}
			i+=2;
		}
	}
	
	// Supprime de status les Segment qui ne sont plus dedans
	public void videStatus(){
		// TODO :  verifier si la sweepLine sort des points evenement
		int i =0;
		while(i<eventPoints.size()-1){
			if(eventPoints.get(i+1).x<pos){
				
			}
		}
	}
	
	public boolean ballayage(){
		for(Segment s : this.status){
			for(Segment s2 : this.status){
				if(s.intersect(s2)){
					return true;
				}
			}
		}
		return false;
	}
	
	private void remove(Segment segment) {
		status.remove(segment);
	}
	
	// calcul d�terminant
	public double determinant(Segment s0, Segment s1){
		return (s0.droit.x - s0.gauche.x) * (s1.droit.y - s1.gauche.y) - (s1.droit.x - s1.gauche.x) * (s0.droit.y - s0.gauche.y);
	}
	
	public ArrayList<Segment> getStatus(){
		return status;
	}

}
