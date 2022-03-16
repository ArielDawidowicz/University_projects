
public class Point implements ObjectWithCoordinates {
	
		int x; 
		int y;
		String name;
	
	public Point(int x,int y, String name) {
		this.x = x;
		this.y = y;
		this.name = name;
	}
	public Point() {
		this.x = 0;
		this.y = 0;
		this.name = null;
	}
	public int getX() {
		return x;
		
	}
	public int getY(){
		return y;		
	}
	public Object getData() {
		return name;  
		
	}
	@Override
	public String toString() {
		String res="";
		res+=this.name;
		res+=" X=";
		res+=this.getX();
		res+=" Y=";
		res+=this.getY();
		return res;
	}
}

