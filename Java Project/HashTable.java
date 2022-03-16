import java.util.LinkedList;


public class HashTable {
	LinkedList<Point>[]hashArr;
	int m;

	@SuppressWarnings("unchecked")
	public HashTable(int m) {
		this.hashArr = new LinkedList[m];
		this.m=m;
		for (int i=0;i<m;i++) {
			hashArr[i]=null;
		}
	}
	
	public int hashFunc(ObjectWithCoordinates p) {
		return (p.getX() + p.getY())%this.m;
	}
	public void insert(ObjectWithCoordinates object){
		int idx = hashFunc(object);
		if (this.hashArr[idx] == null) {
			LinkedList<Point> linkedLst = new LinkedList<Point>();
			linkedLst.addFirst((Point)object);
			hashArr[idx] = linkedLst;
		}
		else {
			hashArr[idx].addFirst((Point)object);
		}
	}

	public ObjectWithCoordinates search(int x, int y){
		int idx = (x+y)%this.m;
		if (hashArr[idx] == null) {
			return null;
		}
		for (int i = 0; i < hashArr[idx].size(); i++) {
			if (hashArr[idx].get(i).getX() == x && hashArr[idx].get(i).getY() == y) {
				return hashArr[idx].get(i);
			}
			
		}
		return null;	
	}
}

