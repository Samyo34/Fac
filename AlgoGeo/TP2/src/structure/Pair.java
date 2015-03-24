package structure;

import utils.vecteur.PointVisible;

public class Pair implements Comparable{
	private PointVisible point;
	private double angle;
	
	public Pair(PointVisible point, double angle){
		this.point = point;
		this.angle = angle;
	}
	
	public PointVisible getPoint(){
		return point;
	}
	
	public double getAngle(){
		return angle;
	}

	@Override
	public int compareTo(Object o) {
		double angle1 = ((Pair) o).getAngle();
		double angle2 = this.getAngle();
		if(angle1 > angle2){
			return -1;
		}else if (angle1 == angle2){
			return 0;
		}else{
			return 1;
		}
	}

}
