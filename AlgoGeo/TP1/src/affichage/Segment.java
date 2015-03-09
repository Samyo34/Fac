package affichage;


import java.awt.Color;
import java.awt.Graphics2D;

class Segment {
	PointVisible gauche;
	PointVisible droit;
	Color lineColor;

	//Precondition: f.x < t.x par convention et pour les besoins de l'algorithme de balayage gauche droite
	Segment(PointVisible f, PointVisible t) {
		gauche = f;
		droit = t;
		lineColor =  Couleur.nw;
		gauche.segment = this;
		droit.segment = this;
	}

	public void dessine(Graphics2D g) {
		g.setColor(lineColor);
		g.drawLine((int) gauche.x , (int) gauche.y , (int) droit.x, (int) droit.y);
	}
	
	public boolean gauche(Segment s1){
		 return (this.gauche.getX()<s1.gauche.getX());

	}
	
	public boolean intersect(Segment s1){
		boolean res;
		 // on suppose : this = AB, s1 = CD
		Segment AC = new Segment(this.gauche,s1.gauche);
		Segment AD = new Segment(this.gauche,s1.droit);
		Segment CA = new Segment(s1.gauche,this.gauche);
		Segment CB = new Segment(s1.gauche,this.droit);
		if((determinant(this,AC) * determinant(this, AD))>0){
			res = false;
		}else if((determinant(s1, CA)*determinant(s1, CB))<0){
			res = true;
		}else{
			res = false;
		}
		
		return res;
	}
	
	// calcul d�terminant
		public double determinant(Segment s0, Segment s1){
			return (s0.droit.x - s0.gauche.x) * (s1.droit.y - s1.gauche.y) - (s1.droit.x - s1.gauche.x) * (s0.droit.y - s0.gauche.y);
		}
		
	public PointVisible getGauche(){
		return gauche;
	}
	
	public PointVisible getDroit(){
		return droit;
	}
	
	public String toString(){
		return "X1: " +gauche.getX() + " Y1: "+gauche.getY()+" | X2: "+ droit.getX() + " Y2: "+ droit.getY();
	}
}

