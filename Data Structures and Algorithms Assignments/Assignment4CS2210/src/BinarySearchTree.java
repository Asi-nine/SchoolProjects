/**
 * BinarySearchTree implementing BinarySearchTreeADT.
 * This class represents a BST storing data, left/right child and parent in each of its nodes.
 * The data stored is DictEntry which contains position (key) and color of a pixel.
 * 
 * @author Peter Valovcik
 * @version 1.0, 19/11/15
 */

public class BinarySearchTree implements BinarySearchTreeADT {

	/*
	 * Helper class BinaryTreeNode
	 * Used to create linked nodes when implementing the BST.
	 */

	private static class BinaryTreeNode{

		private BinaryTreeNode parent, left, right;		// pointers to the children and parent
		private DictEntry data;							// DictEntry containing position (key) and color

		/**
		 * creates an empty, initialized BinaryTreeNode 
		 */

		private BinaryTreeNode(){
			this.data = null;
			this.parent = null;
			this.left = null;
			this.right = null;
		}

		/**
		 * creates a BinaryTreeNode containing only data
		 * 
		 * @param data, a DictEntry, contains a position (key) and a color
		 */

		private BinaryTreeNode(DictEntry data){
			this.data = data;
			this.parent = null;
			this.left = null;
			this.right = null;
		}

		/**
		 * creates a BinaryTreeNode containing a parent and data
		 * 
		 * @param parent, a BinaryTreeNode that is the parent of the node to be created
		 * @param data, a DictEntry, contains a position (key) and a color
		 */

		private BinaryTreeNode(BinaryTreeNode parent, DictEntry data){
			this.data = data;
			this.parent = parent;
			this.left = null;
			this.right = null;

		}

		/**
		 * creates a BinaryTreeNode containing a parent, a left and right child and data
		 * 
		 * @param parent, a BinaryTreeNode that is the parent of the node to be created
		 * @param left, a BinaryTreeNode that is the left child of the node to be created
		 * @param right, a BinaryTreeNode that is the right child of the node to be created
		 * @param data, a DictEntry, contains a position (key) and a color
		 */

		private BinaryTreeNode(BinaryTreeNode parent, BinaryTreeNode left, BinaryTreeNode right, DictEntry data){
			this.data = data;
			this.parent = parent;
			this.left = left;
			this.right = right;

		}

		/**
		 * getParent the parent node
		 * 
		 * @return parent, the parent of the node
		 */

		private BinaryTreeNode getParent(){
			return this.parent;
		}

		/**
		 * getLeft returns the left child of the node
		 *
		 * @return left, the left child of the node
		 */

		private BinaryTreeNode getLeft(){
			return this.left;
		}

		/**
		 * getRight returns the right child of the node
		 *
		 * @return right, the right child of the node
		 */

		private BinaryTreeNode getRight(){
			return this.right;
		}

		/**
		 * getData returns the DictEntry of the node
		 *
		 * @return data, the data stored in the node
		 */

		private DictEntry getData(){
			return this.data;
		}

		/**
		 * setParent set the parent of the node
		 *
		 * @param node, the BinaryTreeNode to be set as the parent
		 */

		private void setParent(BinaryTreeNode node){
			this.parent = node;
		}

		/**
		 * setLeft set the left child of the node
		 *
		 * @param node, the BinaryTreeNode to be set as the left child
		 */

		private void setLeft(BinaryTreeNode node){
			this.left = node;
		}

		/**
		 * setRight set the right child of the node
		 *
		 * @param node, the BinaryTreeNode to be set as the right child
		 */

		private void setRight(BinaryTreeNode node){
			this.right = node;
		}

		/**
		 * setData set the data of the node
		 *
		 * @param data, the DictEntry to be set as the data
		 */

		private void setData(DictEntry data){
			this.data = data;
		}
	}

	private BinaryTreeNode root; // root of the BinarySearchTree

	/**
	 * creates an BinarySearchTree containing as the root a node with all parameters as null 
	 */

	public BinarySearchTree(){
		this.root = new BinaryTreeNode();
	}

	/**
	 * Invokes the private find method and retrieves the data from the node returned
	 * by that method.
	 * 
	 * @param key, unique key based on position used to look up an entry in the BST
	 * @return the DictEntry containing the key or null if no such key exists
	 */

	public DictEntry find(Position key) {
		return find(root, key).getData();
	}

	/**
	 * Look for the key in the BST by traversing the proper subtrees based on whether 
	 * the key being looked for is smaller or larger than keys in the nodes of the BST.
	 * 
	 * @param key, unique key based on position used to look up an entry in the BST
	 * @param node, root of a BST
	 * @return returnNode, a node either containing the data or a node of where the data would be but containing null
	 */

	private BinaryTreeNode find(BinaryTreeNode node, Position key) {
		
		// check nodes starting at the node input and moving down the tree based on whether the key is higher or
		// lower than the key that is being searched for. Will return the node once it finds it or the node that
		// would contain the key if it were in the tree (but contains null)
		while (node.getData() != null){
			if (node.getData().getPosition().compareTo(key) == 0){
				return node;
			} else if (node.getData().getPosition().compareTo(key) < 0){
				node = node.getRight();
			} else {
				node = node.getLeft();
			}
		}
		return node;
	}

	/**
	 * Look for the key in the BST by traversing the proper subtrees based on whether 
	 * the key being looked for is smaller or larger than keys in the nodes of the BST.
	 * 
	 * @param key, unique key based on position used to look up an entry in the BST
	 * @param node, root of a BST
	 * @return returnNode, a node either containing the data or a node of where the data would be but containing null
	 */

	public void insert(DictEntry data) throws BSTException {
		// check to make sure the node is not already in the tree
		if (find(data.getPosition()) != null){
			throw new BSTException("The tree already contains something with identical position coordinates.");
		} else {
			// insert the node once the position it should be in is found, and attach attach a left and right child
			// containing null to it, as well as setting that node as their parent
			BinaryTreeNode leftNull = new BinaryTreeNode();
			BinaryTreeNode rightNull = new BinaryTreeNode();
			BinaryTreeNode insertionPoint = find(root, data.getPosition());
			insertionPoint.setData(data);
			insertionPoint.setLeft(leftNull);
			insertionPoint.setRight(rightNull);
			leftNull.setParent(insertionPoint);
			rightNull.setParent(insertionPoint);
		}

	}

	/**
	 * Remove the node containing the key in the BST if it contains it.
	 * 
	 * @param key, unique key based on position used to find the node to remove in the BST
	 */

	public void remove(Position key) throws BSTException {
		// check to make sure the node with the key is in the BST
		if (find(key) == null){
			throw new BSTException("The tree does not contain anything with the given coordinates to remove.");
		} else {
			BinaryTreeNode nodeOfKey = find(root, key);
			BinaryTreeNode childLeft = nodeOfKey.getLeft();
			BinaryTreeNode childRight = nodeOfKey.getRight();
			// check if left child of node to see if it is a leaf
			if (childLeft.getData() == null){
				// set the root of the tree to the right child if the original root was the node to be removed
				// and the left child of the original root was a leaf
				if (nodeOfKey.equals(this.root)){
					this.root = childRight;
				} else {
					// check if node to be removed is the left or right child of its parent node, and set the new 
					// left or right of its parent accordingly to remove it
					BinaryTreeNode parent = nodeOfKey.getParent();
					if (parent.getLeft().equals(nodeOfKey)){
						parent.setLeft(childRight);
					} else {
						parent.setRight(childRight);
					}
				}
				// same as previous block of 14 lines but on right child
			} else if (childRight.getData() == null){
				if (nodeOfKey.equals(this.root)){
					this.root = childLeft;
				} else {
					BinaryTreeNode parent = nodeOfKey.getParent();
					if (parent.getLeft().equals(nodeOfKey)){
						parent.setLeft(childLeft);
					} else {
						parent.setRight(childLeft);
					}
				}
			} else {
				// check to make sure that invoking smallest on the right child will not yield root as the result and
				// remove the proper node if that had been the case.
				BinaryTreeNode removalPoint = new BinaryTreeNode();
				if (nodeOfKey.getRight().getLeft().getData() == null){
					removalPoint = nodeOfKey.getRight();
					BinaryTreeNode parent = removalPoint.getParent();
					nodeOfKey.setData(removalPoint.getData());
					parent.setRight(removalPoint.getRight());
				}else {
					//find the smallest node in the right subtree and use it to remove the node we wish to remove
					removalPoint = this.find(root, smallest(nodeOfKey.getRight()).getPosition());
					BinaryTreeNode parent = removalPoint.getParent();
					nodeOfKey.setData(removalPoint.getData());
					parent.setLeft(removalPoint.getRight());
				}
			}
		}
	}

	/**
	 * Searches for the key that is the next higher one compared to the input key.
	 * 
	 * @param key, unique key based on position 
	 * @return the DictEntry of the next higher key versus the input key or null if there is no next higher key
	 */

	public DictEntry successor(Position key) {
		// return null if tree has no data
		if (root.getData() == null){
			return null;
		} else {
			// get the smallest from the right sub tree of the input key's node
			BinaryTreeNode nodeOfKey = find(root, key);
			if(nodeOfKey.getRight() != null && nodeOfKey.getRight().getData() != null){
				return smallest(nodeOfKey.getRight());
			} else {
				// check if key is in root
				if (nodeOfKey.getParent() == null){
					return null;
				}
				// get the data first node that would make the key's node its left child
				BinaryTreeNode parent = nodeOfKey.getParent();
				while (parent.getParent() != null && parent.getRight() == nodeOfKey){
					nodeOfKey = parent;
					parent = parent.getParent();
				}
				// return null if there is no successor
				if (parent.getParent() == null && parent.getRight() == nodeOfKey){
					return null;
				}
				return parent.getData();
			}
		}
	}

	/**
	 * Searches for the key that is the next lower one compared to the input key.
	 * 
	 * @param key, unique key based on position 
	 * @return the DictEntry of the next lower key versus the input key or null if there is no next lower key
	 */

	public DictEntry predecessor(Position key) {
		// return null if tree has no data
		if (root.getData() == null){
			return null;
		} else {
			// get the largest from the left sub tree of the input key's node
			BinaryTreeNode nodeOfKey = find(root, key);
			if(nodeOfKey.getLeft() != null && nodeOfKey.getLeft().getData() != null){
				return largest(nodeOfKey.getLeft());
			} else {
				// check if key is in root
				if (nodeOfKey.getParent() == null){
					return null;
				}
				// get the data of first node that would make the key's node its left child
				BinaryTreeNode parent = nodeOfKey.getParent();
				while (parent.getParent() != null && parent.getLeft() == nodeOfKey){
					nodeOfKey = parent;
					parent = parent.getParent();
				}
				// return null if there is no predecessor
				if (parent.getParent() == null && parent.getLeft() == nodeOfKey){
					return null;
				}
				return parent.getData();
			}
		}
	}

	/**
	 * Searches for the key that is the smallest one.
	 * 
	 * @return the DictEntry of the smallest key or null if the tree is just a root containing no data
	 */

	public DictEntry smallest() {
		// return null if no data in tree
		if (root.getData() == null){
			return null;
		} else {
			// loop through to the leftmost node and return the parent's data since leftmost will be a leaf
			BinaryTreeNode node = root;
			while (node.getData() != null){
				node = node.getLeft();
			}
			return node.getParent().getData();
		}
	}

	/**
	 * Searches for the key that is the smallest one.
	 * 
	 * @param node, the node to use as the root of the tree to begin the search
	 * @return the DictEntry of the smallest key or null if the tree is just a root containing no data
	 */


	// same concept as other smallest method but allows for an alternate root to be entered as a parameter
	private DictEntry smallest(BinaryTreeNode node) {
		if (node.getData() == null){
			return null;
		} else {
			BinaryTreeNode node2 = node;
			while (node2.getData() != null){
				node2 = node2.getLeft();
			}
			return node2.getParent().getData();
		}
	}

	/**
	 * Searches for the key that is the largest one.
	 * 
	 * @return the DictEntry of the largest key or null if the tree is just a root containing no data
	 */

	public DictEntry largest() {
		// return null if no data in tree
		if (root.getData() == null){
			return null;
		} else {
			// loop through to the rightmost node and return the parent's data since rightmost will be a leaf
			BinaryTreeNode node = root;
			while (node.getData() != null){
				node = node.getRight();
			}
			return node.getParent().getData();
		}
	}

	/**
	 * Searches for the key that is the largest one.
	 * 
	 * @param node, the node to use as the root of the tree to begin the search
	 * @return the DictEntry of the largest key or null if the tree is just a root containing no data
	 */

	// same concept as other largest method but allows for an alternate root to be entered as a parameter
	private DictEntry largest(BinaryTreeNode node) {
		if (node.getData() == null){
			return null;
		} else {
			BinaryTreeNode node2 = node;
			while (node2.getData() != null){
				node2 = node2.getRight();
			}
			return node2.getParent().getData();
		}
	}

}
