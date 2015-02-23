package affichage;
import javax.swing.*;

import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.util.ArrayList;
import java.util.Random;

public class Vue extends JPanel implements MouseWheelListener, MouseListener{
	Color bgColor = Couleur.bg; // la couleur de fond de la fen�tre
	Color fgColor = Couleur.fg; // la couleur des lignes
	int width, height;
	ArrayList<Segment> segments = new ArrayList<Segment>();
	SweepLine sweepLine;	

	// n : le nombre de lignes
	// width, height : largeur, hauteur de la fen�tre
	public Vue(int n, int width, int height) {
		setBackground(bgColor);
		this.width = width;
		this.height = height;
		setPreferredSize(new Dimension(width, height));
		sweepLine = new SweepLine(n, width, height, this);
		addMouseListener(this);
		addMouseWheelListener(this);
	}
	
	// initialisation random 
	public void init(int n){
		ArrayList<Segment> list = new ArrayList<Segment>();
		for(int i =0;i<n;i++){
			int x = random(20,400);
			int y = random(100,700);
			PointVisible p1 = new PointVisible(x,y,role.begin);
			int xj = random(x+1,x+100);
			int yj = random(y-50,y+50);
			PointVisible p2 =  new PointVisible(xj, yj, role.end);
			Segment s = new Segment(p1, p2);
			list.add(s);
		}
		this.segments = list;
	}
	
	// methode utilitaire 
	// retourne un entier compris entre xmin et xmax
	int random(int xmin,int xmax){
		Random rn = new Random();
		int randomNum = rn.nextInt((xmax-xmin)+1)+xmin;
		//int res = (int)(xmin + Math.random()*xmax);
		return randomNum;
	}
		
	public void paintComponent(Graphics g) {
		super.paintComponent(g);
		Graphics2D g2d = (Graphics2D) g;
		g2d.setPaintMode(); 
		g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,	RenderingHints.VALUE_ANTIALIAS_ON);	

		g2d.setColor(fgColor);
		
		for (Segment lg: segments) {
			lg.dessine(g2d);
		}
		sweepLine.dessine(g2d);
	}
	
	public ArrayList<Segment> getSegments(){
		return segments;
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		
		int n = segments.size();
		if (e.getClickCount() == 2){
				init(n);
				repaint();
		}
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		for(Segment s : sweepLine.getStatus()){
			System.out.println(s.toString());
		}
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
	}
	
	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		int scrollUnit = e.getWheelRotation();
		if (scrollUnit > 0)
			sweepLine.next();
		repaint();
	}

}
	

