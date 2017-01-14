/**
 * BinaryTreeNode represents a node in a binary tree with a left and 
 * right child.
 * 
 * @author Dr. Lewis
 * @author Dr. Chase
 * @version 1.0, 8/19/08
 */

public class BinaryTreeNode<T>
{
   private T element;
   private BinaryTreeNode<T> left, right;

   /**
    * Creates a new tree node with the specified data.
    *
    * @param obj  the element that will become a part of the new tree node
   */
   BinaryTreeNode (T obj) 
   {
      element = obj;
      left = null;
      right = null;
   }
   
   /**
    * Sets the element reference
    * 
    * @param obj	the element that will become referenced
    */
   
   public void setElement(T obj)
   {
	   element = obj;
   }
   
   /**
    * Gets the element reference
    * 
    * @return	the element reference
    */
   
   public T getElement()
   {
	   return element;
   }
   
   /**
    * Sets the reference to the left child of the node
    * 
    * @param newLeft	the reference to a node or null on the left
    */

   public void setLeft(BinaryTreeNode<T> newLeft)
   {
	   left = newLeft;
   }
   
   /**
    * Gets the reference to the left child of the node
    * 
    * @Return	the reference to a node or null on the left
    */

   public BinaryTreeNode<T> getLeft()
   {
	   return left;
   }
   
   /**
    * Sets the reference to the right child of the node
    * 
    * @param newRight	the reference to a node or null on the right
    */

   public void setRight(BinaryTreeNode<T> newRight)
   {
	   right = newRight;
   }
   
   /**
    * Gets the reference to the right child of the node
    * 
    * @Return	the reference to a node or null on the right
    */

   public BinaryTreeNode<T> getRight()
   {
	   return right;
   }
   
   /**
    * Returns the number of non-null children of this node.
    * This method may be able to be written more efficiently.
    *
    * @return  the integer number of non-null children of this node 
    */
   public int numChildren() 
   {
      int children = 0;

      if (left != null)
         children = 1 + left.numChildren();

      if (right != null)
         children = children + 1 + right.numChildren();

      return children;
   }
}

