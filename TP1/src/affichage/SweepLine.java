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
	int pos, step, maxStep, stepWidth;
	
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
		//rempStatus();
		//TODO: parcourir les segment de vue et verifier si ce segment ne croise pas la Line
		if (eventPoints.size() > 0) {
				ballayage();
			} else {
				pos = step * stepWidth;
		}
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
	}
	
	// Supprime de status les Segment qui ne sont plus dedans
	public void videStatus(){
		// TODO :  verifier si la sweepLine sort des points evenement
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
