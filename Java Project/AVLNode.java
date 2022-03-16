
public class AVLNode<T> {
	 AVLNode<T> leftChild;
	 AVLNode<T> rightChild;
	 AVLNode<T> father;
	 int key, height;
	 T data;
	
	//added T data as input
	public AVLNode(int key,T data){
		this.leftChild = null;
		this.rightChild = null;
		this.father = null;
		this.key = key;
		this.data = data;
		this.height = 0;
	}

	
	public AVLNode<T> getLeftChild(){
		return this.leftChild;
	}
	
	public AVLNode<T> getRightChild(){
		return this.rightChild;
	}
	
	public AVLNode<T> getFather(){
		return this.father;
	}
	
	public int getKey(){
		return this.key;
	}
	
	public T getData(){
		return this.data;
	}
	
	@Override
	public String toString() {
		
		String s = "";
		
		if (getLeftChild() != null){
			s+="(";
			s+=getLeftChild().toString();
			s+=")";
		}
		s+=getKey();
		
		if (getRightChild() != null){
			s+="(";
			s+=getRightChild().toString();
			s+=")";
		}
		
		return s;
	}
}

