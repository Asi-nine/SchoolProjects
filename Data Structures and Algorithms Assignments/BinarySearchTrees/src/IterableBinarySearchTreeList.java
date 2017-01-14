import java.util.Iterator;

public class IterableBinarySearchTreeList<T> extends BinarySearchTreeList<T> {
	
		/**
	    * Creates an empty BinarySearchTreeList.
	    */
	   public IterableBinarySearchTreeList() 
	   {
	      super();
	   }
	   
	   /**
	    * iterator to iterate over all elements in tree in descending order
	    * @return iterator
	    */
	   
	   public Iterator<T> iteratorInOrderDescending(){
		   
		   ArrayUnorderedList<T> tempList = new ArrayUnorderedList<T>();
		   inorderDescending(root, tempList);
		      
		   return tempList.iterator();
	   }
	   
	   /**
	    * Performs a recursive inorder traversal in descending order.
	    *
	    * @param node      the node to be used as the root for this traversal
	    * @param tempList  the temporary list for use in this traversal
	    */
	   protected void inorderDescending (BinaryTreeNode<T> node, 
	                           			ArrayUnorderedList<T> tempList) 
	   {
	      if (node != null)
	      {
	         inorderDescending (node.getRight(), tempList);
	         tempList.addToRear(node.getElement());
	         inorderDescending (node.getLeft(), tempList);
	      }
	   }

}
