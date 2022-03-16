import java.util.LinkedList;

public class AVL<T> {
	AVLNode<T> root;
	
	public AVL() {
		this.root = null;
	}
	
	public int getHeight(AVLNode<T> node) {
		if (node == null) {
			return -1;
		}
		return node.height;
		
	}
	
	public void updateHeight(AVLNode<T> node){
		if (node == null) {
			return;
		}
		if (node.leftChild == null && node.rightChild == null) {
			node.height = 0;
			return;
		}
		if(node.leftChild != null && node.rightChild == null) {
			node.height = node.leftChild.height + 1 ;
			return;
			
		}
		if(node.leftChild == null && node.rightChild != null) {
			node.height = node.rightChild.height + 1 ;
			return;
			
		}
		node.height = Math.max(getHeight(node.getLeftChild()), getHeight(node.getRightChild())) + 1;
		return;
	}
	
	public void BSTinsert(AVLNode<T> node ,AVLNode<T> root) {
		if (root == null) {
			this.root = node;
			return;
		}
		if (node.getKey() < root.getKey()) {
			if (root.getLeftChild() == null) {
				root.leftChild = node;
				node.father = root;
				return;
			}
			else {
				BSTinsert(node, root.getLeftChild());
			}
		}
		if (node.getKey() > root.getKey()) {
			if (root.rightChild == null) {
				root.rightChild = node;
				node.father = root;
				return;
			}
			else {
				BSTinsert(node, root.getRightChild());
		}
	}
}
	// Balance factor for rebalancing the AVL tree
	public int getBf(AVLNode<T> node) {
		if(node.leftChild == null && node.rightChild == null) {
			return 0;
		}
		
		if(node.leftChild == null && node.rightChild != null) {
			return Math.abs(-1 - node.rightChild.height);
			
		}
		if(node.leftChild != null && node.rightChild == null) {
			return Math.abs(node.leftChild.height + 1);
			
		}
		
		return Math.abs(getHeight(node.getLeftChild())-getHeight(node.getRightChild()));
	}
	
	public void LLrotation(AVLNode<T> k2) {
		AVLNode<T> k1 = k2.getLeftChild();
		if (k2.father == null) {
			this.root = k1;
			k1.father = null;
		}
		if (k2.father != null) {
			k1.father = k2.father;
			k1.father.leftChild = k1;
		}
		k2.leftChild = k1.rightChild;
		if (k1.rightChild != null) {
			k1.rightChild.father = k2;
		}
		k1.rightChild = k2;
		k2.father = k1;
		updateHeight(k2);
		updateHeight(k1);
		updateHeight(k1.father);
	}
	public void LRrotation(AVLNode<T> k2) {
		AVLNode<T> k1 = k2.getLeftChild();
		AVLNode<T> k3 = k1.getRightChild();
		k2.leftChild = k3;
		k3.father = k2;
		k1.rightChild = k3.leftChild;
		if (k1.rightChild != null ) {
			k1.rightChild = k1;
		}
		k3.leftChild = k1;
		k1.father = k3;
		updateHeight(k1);
		updateHeight(k3);
		updateHeight(k2);
		LLrotation(k2);	
	}
	public void RRrotation(AVLNode<T> k2) {
		AVLNode<T> k1 = k2.getRightChild();
		if (k2.father == null) {
			this.root = k1;
			k1.father = null;
		}
		if (k2.father != null) {
			k1.father = k2.father;
			k1.father.rightChild = k1;
		}
		k2.rightChild = k1.leftChild;
		if (k1.leftChild != null) {
			k1.leftChild.father = k2;
		}
		k1.leftChild = k2;
		k2.father = k1;
		updateHeight(k2);
		updateHeight(k1);
		updateHeight(k1.father);	
	}
	public void RLrotation(AVLNode<T> k2) {
		AVLNode<T> k1 = k2.getRightChild();
		AVLNode<T> k3 = k1.getLeftChild();
		k2.rightChild = k3;
		k3.father = k2;
		k1.leftChild = k3.rightChild;
		if (k3.rightChild != null ) {
			k3.rightChild.father = k1;
		}
		k3.rightChild = k1;
		k1.father = k3;
		updateHeight(k1);
		updateHeight(k3);
		updateHeight(k2);
		RRrotation(k2);						
	}
	
	

	public void reBalance(AVLNode<T> k2) {
		if (getHeight(k2.leftChild) > getHeight(k2.rightChild)) {
			if(getHeight(k2.leftChild.leftChild) > getHeight(k2.leftChild.rightChild)) {
				LLrotation(k2);
				return;
			}
			LRrotation(k2);
			return;
		}
		if (getHeight(k2.leftChild) < getHeight(k2.rightChild)) {
			if(getHeight(k2.rightChild.rightChild) > getHeight(k2.rightChild.leftChild)) {
				RRrotation(k2);
				return;
			}
			RLrotation(k2);
			return;
	}
}
	
	public void insert(int key, T data){
		AVLNode<T> newNode = new AVLNode<T>(key,data);
		BSTinsert(newNode, this.root);
		AVLNode<T> tmp = newNode.father;
		while (tmp != null) {
			updateHeight(tmp);
			if (getBf(tmp) == 2) {
				reBalance(tmp);
				return;
			}
			tmp = tmp.father;
		}
		return;
		
	}
	// wrapper function for search method
	public AVLNode<T> searchHlp(AVLNode<T> curr, int key) {
		if (curr == null)  {
			return null;
		}
		if (curr.getKey() == key) {
			return curr;
		}
		if (key < curr.getKey()) {
			curr = curr.getLeftChild();
			return searchHlp(curr, key);
		}
		if (key > curr.getKey()) {
			curr = curr.getRightChild();
			return searchHlp(curr, key);
		}
		return curr; 
			
		}

	public T search(int key){
		AVLNode<T> tmp = searchHlp(this.root, key);
		if (tmp == null) {
			return null;
		}
		return tmp.getData();
		
	}

	public AVLNode<T> getRoot(){
		return this.root;
	}
	
	//returns a sorted (by keys) linked list of Point within range
	public LinkedList<T> inRange(int bottom,int top){
		if(root==null || findMaximum(root).getKey()<bottom || findMinimum(root).getKey()>top) {
			return null;
		}
		AVLNode<T> a=findSuccessor(this.root, root, bottom);
		AVLNode<T> b=findPredecessor(this.root, root, top);
		// Finding the node where a and b split
		AVLNode<T> splitNode=this.root;
		while (splitNode!=null && !(splitNode.getKey()>=a.getKey() && splitNode.getKey()<=b.getKey())) {
			if (splitNode.getKey()<a.getKey()) {	
				splitNode=splitNode.rightChild;
			}else {
				splitNode=splitNode.leftChild;
			}
		}
		if (splitNode==null) {
			return null;
		}
		LinkedList<T> inRlist=new LinkedList<T> ();
		pathToA(bottom,top, a, inRlist,splitNode);
		// condition to deal with splitNode == top-boundary
		if (splitNode.getKey()!=b.getKey()) {
		pathToB(top, b, inRlist, splitNode.rightChild);
		}
		return inRlist;
	}
	
	public AVLNode<T> findMinimum(AVLNode <T> root){
		while(root.leftChild!=null) {
			root=root.leftChild;
		}
		return root;
	}
	
	public AVLNode<T> findMaximum(AVLNode <T> root){
		while(root.rightChild!=null) {
			root=root.rightChild;
		}
		return root;
	}
	public AVLNode<T> findSuccessor(AVLNode <T> root,AVLNode<T> node, int key){
		if(root==null) {
			return node;
		}
		if (root.getKey()==key) {
			return root;
		}else if (key<root.getKey()) {
			node=root;
			return findSuccessor(root.leftChild, node, key);
		}else {
			return findSuccessor(root.rightChild, node, key);
		}
	}
	public AVLNode<T> findPredecessor(AVLNode <T> root,AVLNode<T> node, int key){
		if(root==null) {
			return node;
		}
		if (root.getKey()==key) {
			return root;
		}else if (key < root.getKey()) {
            return findPredecessor(root.leftChild, node, key);
		}else {
			 node = root;
	         return findPredecessor(root.rightChild,node, key);
	        }
	}
	// Adding to the LL all the nodes in range in path from split to a 
	public void pathToA(int bottom,int top, AVLNode<T> a, LinkedList<T> inRlist,AVLNode<T> splitNode) {
		// In case of split node is the bottom boundary
		if (a.getKey()==splitNode.getKey()) {
			if (a.getData()!=null) {
			inRlist.add(a.getData());
			}
			return ;
		}
		if (a.getData()!=null) {
			inRlist.add(a.getData());
		}
		inOrder(a.rightChild, inRlist);
		AVLNode<T> cur=a.father;
		while (cur!=null && cur.getKey()!=splitNode.getKey()) {
			if(cur.getKey()>bottom) {
				// in our range
				if (cur.getData()!=null) {
				inRlist.add(cur.getData());
				}
				inOrder(cur.rightChild, inRlist);
			}
			cur=cur.father;
		}
		//adding the split node itself
		if (cur.getData()!=null) {
		inRlist.add(cur.getData());
		}
		return;
	}
	// Adding to the LL all the nodes in range in path from split.rightChild to b
	public void pathToB(int top, AVLNode<T> b, LinkedList<T> inRlist,AVLNode<T> cur ) {
		while (cur.getKey()!=b.getKey()) {
			if(top>cur.getKey()) {
				// in our range
				inOrder(cur.leftChild, inRlist);
				if (cur.getData()!=null) {
				inRlist.add(cur.getData());
				}
				cur=cur.rightChild;
			}else {
				//Not in range don't need to add
				cur=cur.leftChild;
			}
		}
		inOrder(cur.leftChild, inRlist);
		if (cur.getData()!=null) {
			inRlist.add(cur.getData());
		}
		return;
	}
		
	//inorder adding the Points to a LinkedList
	public void inOrder (AVLNode<T> node,LinkedList<T> inRlist) {
		if (node==null) {
			return;
		}
		inOrder(node.leftChild,inRlist);
		if (node.getData()!=null) {
		inRlist.add(node.getData());
		}
		inOrder(node.rightChild,inRlist);
	}
	
}