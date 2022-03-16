import java.util.LinkedList;
import java.util.Iterator;

public class StudentSolution  implements MyInterface{
	
	AVL<Point> xTree;
	AVL<Point> yTree;
	
	public StudentSolution () {
		this.xTree=new AVL<Point>();
		this.yTree=new AVL<Point>();
	}
	
	@Override
	public void insertDataFromDBFile(String objectName, int objectX, int objectY) {
		Point obj = new Point(objectX, objectY, objectName);
		xTree.insert(objectX, obj);
		yTree.insert(objectY, obj);
	}
	
	@Override
	public String[] firstSolution(int leftTopX, int leftTopY, int rightBottomX,
			int rightBottomY) {
		LinkedList<Point> m1=xTree.inRange(Math.min(rightBottomX, leftTopX),Math.max(rightBottomX, leftTopX));
		LinkedList<Point> m2=yTree.inRange(Math.min(rightBottomY, leftTopY),Math.max(rightBottomY, leftTopY));
		if (m1==null ||m2==null) {
			return new String [0];
		}
		HashTable hash=new HashTable(m1.size()+m2.size());
		LinkedList<Point> shorter=new LinkedList <Point> ();
		LinkedList<Point> longer=new LinkedList <Point> ();
		if (m1.size()<=m2.size()) {
			longer=m2;
			shorter=m1;
		}else {
			longer=m1;
			shorter=m2;
		}
		String [] res=new String [shorter.size()];
		int resIndex=0;
		Iterator <Point> iter1=shorter.iterator();
		Iterator <Point> iter2=longer.iterator();
		for (int i=0;i<longer.size();i++) {
			hash.insert(iter2.next());
		}
		for (int j=0;j<shorter.size();j++) {
			Point p=iter1.next();
			if (hash.search(p.getX(), p.getY())!=null){
				res[resIndex]=p.toString();
				resIndex++;
			}
		}
		if (resIndex==0) {
			return new String [0];
		}
		return res;
	}

	@Override
	public String[] secondSolution(int leftTopX, int leftTopY,
			int rightBottomX, int rightBottomY) {
		LinkedList<Point> m1=xTree.inRange(Math.min(rightBottomX, leftTopX),Math.max(rightBottomX, leftTopX));
		LinkedList<Point> m2=yTree.inRange(Math.min(rightBottomY, leftTopY),Math.max(rightBottomY, leftTopY));
		String [] res;
		if (m1==null ||m2==null) {
			return new String [0];
		}
		int xSize=m1.size();
		int ySize=m2.size();
		Point[] arrX= convertArr(m1, xSize);
		Point[] arrY= convertArr(m2, ySize);
		int resIndex=0;
		if(xSize<=ySize) {
			res=new String [xSize];
			for(int i=0;i<xSize;i++) {
				int y=arrX[i].getY();
				Point found=searchY(arrY, y, ySize-1, 0);
				if(found!=null) {
					res[resIndex]=found.toString();
					resIndex++;
				}
			}
		}else {
			res=new String [ySize];
			for(int i=0;i<ySize;i++) {
				int x=arrY[i].getX();
				Point found=searchX(arrX, x, xSize-1, 0);
				if(found!=null) {
					res[resIndex]=found.toString();
					resIndex++;
				}
			}
		}
		if (resIndex==0) {
			return new String [0];
		}
		return res;
	}
	
	//converting LL to arrays
	public Point[] convertArr(LinkedList<Point> ll,int size) {
		Point [] arr=new Point[size];
		Iterator <Point> it=ll.iterator();
		for (int i=0;i<size;i++) {
			arr[i]=it.next();
		}
		return arr;
	}
	
	public Point searchY(Point[] arr,int y,int right,int left) {
		if (right>=left) {
			int mid=Math.round((left+right)/2);
			if (arr[mid].getY()==y) {
				return arr[mid];
			}
			if (arr[mid].getY()>y) {
				return searchY(arr,y,mid-1,left);
			}
			return searchY(arr,y,right,mid+1);
		}
		return null;
	}
	public Point searchX(Point[] arr,int x,int right,int left) {
		if (right>=left) {
			int mid=Math.round((left+right)/2);
			if (arr[mid].getX()==x) {
				return arr[mid];
			}
			if (arr[mid].getX()>x) {
				return searchX(arr,x,mid-1,left);
			}
			return searchX(arr,x,right,mid+1);
		}
		return null;
	}
	
}
