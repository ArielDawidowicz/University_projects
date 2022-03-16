import java.util.LinkedList;

public class test {
	public static void main(String[] args) {
		//System.out.println("Hash test: "+testHash());
		//System.out.println("AVL test: "+testAVL());
		//inRangeTest();
		//secondSolTest();
	}
public static Boolean testHash() {
	HashTable h1 = new HashTable(13);
	Point p1 = new Point(80,197,"Ben");
	Point p2 = new Point(100,200,"Ann");
	Point p3 = new Point(14,97,"Hen");
	h1.insert(p1);
	
	h1.insert(p2);
	h1.insert(p3);
		if(h1.search(11,0)!=null) {
			return false;}
		if(h1.search(80,197)!=p1) {
			return false;
		}
		if (h1.search(14,97)!=p3) {
			return false;
		}
		return true;	
	}
public static String testAVL() {
	AVL<Point> tree = new AVL<Point>();
	Point p1 = new Point(80,197,"Ben");
	Point p2 = new Point(100,200,"Ann");
	Point p3 = new Point(14,97,"Hen");
	Point p4 = new Point(45,21,"Jim");
	Point p5 = new Point(12,30,"Bar");
	tree.insert(p1.getX(), p1);
	tree.insert(p2.getX(), p2);
	tree.insert(p3.getX(), p3);
	tree.insert(p4.getX(), p4);
	tree.insert(p5.getX(), p5);
	if (tree.root.getData()!=p1 || tree.root.leftChild.getData()!=p3 || tree.root.rightChild.getData()!=p2) {
		return "test 1: Failed";
	}
	if(tree.root.leftChild.leftChild.getData()!=p5 || tree.root.leftChild.rightChild.getData()!=p4) {
		return "test2: Failed";
	}
	if (tree.search(12)!=p5 || tree.search(5)!=null) {
		return "search test: Failed";
	}
	Point p6 = new Point(9,30,"Bar");
	tree.insert(p6.getX(), p6);
	//LL Rotation check
	if (tree.root.getData()!=p3 || tree.root.rightChild.getData()!=p1 || tree.root.rightChild.leftChild.getData()!=p4) {
		return "test3: Failed";
	}
	Point p7 = new Point(125,165,"abc");
	Point p8 = new Point(90,321,"qwerty");
	Point p9 = new Point(40,7,"hhh");
	Point p10 = new Point(42,93,"zzz");
	Point p11 = new Point(85,293,"lll");
	tree.insert(p7.getX(), p7);
	tree.insert(p8.getX(), p8);
	tree.insert(p9.getX(), p9);
	tree.insert(p10.getX(), p10);
	if (tree.root.rightChild.leftChild.getData()!=p10 || tree.root.rightChild.leftChild.leftChild.getData()!=p9) {
		return "test 4 : Failed";
	}
	tree.insert(p11.getX(), p11);
	if(tree.root.getData()!=p1 || tree.root.rightChild.data!=p2 || tree.root.leftChild.data!=p3 ) {
		System.out.println(tree.root.getData());
		System.out.println(tree.getHeight(tree.root.leftChild));
		System.out.println(tree.getHeight(tree.root.rightChild));
		return "test 5: Failed";
	}
	return "True";
	
}
public static String inRangeTest() {
	AVL<Point> tree = new AVL<Point>();
	Point p1 = new Point(80,197,"Ben");
	Point p2 = new Point(100,200,"Ann");
	Point p3 = new Point(14,97,"Hen");
	Point p4 = new Point(45,21,"Jim");
	Point p5 = new Point(12,30,"Bar");
	tree.insert(p1.getX(), p1);
	tree.insert(p2.getX(), p2);
	tree.insert(p3.getX(), p3);
	tree.insert(p4.getX(), p4);
	tree.insert(p5.getX(), p5);
	LinkedList <Point> l=new LinkedList<Point> ();
//	INORDER method test
//	tree.inOrder(tree.root,l);
//	for(int i=0;i<l.size();i++) {
//		System.out.println(l.get(i));
//	}
	Point p6 = new Point(9,230,"Bar");
	tree.insert(p6.x, p6);
// InRange method test: 
//	l=tree.inRange(0,11);
//	for(int i=0;i<l.size();i++) {
//		System.out.println(l.get(i));
//	}
	//Successor and Predecessor tests: 
//	AVLNode<Point> succ= tree.findSuccessor(tree.root, tree.root,18 );
//	System.out.println(succ.getData());
//	AVLNode<Point> pred= tree.findPredecessor(tree.root, tree.root,12 );
//	System.out.println(pred.getData());
	
	return "";
	}
public static String[] secondSolTest (){
	StudentSolution studentSol=new StudentSolution();
	Point p1 = new Point(80,197,"Ben");
	Point p2 = new Point(100,200,"Ann");
	Point p3 = new Point(14,97,"Hen");
	Point p4 = new Point(45,21,"Jim");
	Point p5 = new Point(12,30,"Bar");
	Point p6 = new Point(9,230,"Bar");
	studentSol.xTree.insert(p1.getX(), p1);
	studentSol.xTree.insert(p2.getX(), p2);
	studentSol.xTree.insert(p3.getX(), p3);
	studentSol.xTree.insert(p4.getX(), p4);
	studentSol.xTree.insert(p5.getX(), p5);
	studentSol.xTree.insert(p6.x, p6);
	studentSol.yTree.insert(p1.getY(), p1);
	studentSol.yTree.insert(p2.getY(), p2);
	studentSol.yTree.insert(p3.getY(), p3);
	studentSol.yTree.insert(p4.getY(), p4);
	studentSol.yTree.insert(p5.getY(), p5);
	studentSol.yTree.insert(p6.getY(), p6);
	
    String [] res=studentSol.secondSolution(10, 0, 100, 100);
	for (int i=0;i<res.length;i++) {
		System.out.println(res[i]);
	}
	return null;
	}
	 
}


		
		
