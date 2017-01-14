import java.util.Iterator;
/**
 *  @author Lewis and Chase
 *
 *  Represents a linked implementation of a stack.
 */

public class LinkedStack<T> implements StackADT<T>
{
  /** indicates number of elements stored */
  private int count;  
  /** pointer to top of stack */
  private LinearNode<T> top; 

  /**
   * Creates an empty stack.
   */
  public LinkedStack()
  {
    count = 0;
    top = null;
  }

  /**
   * Adds the specified element to the top of this stack.
   * @param element element to be pushed on stack
   */
  public void push (T element)
  {
    LinearNode<T> temp = new LinearNode<T> (element);

    temp.setNext(top);
    top = temp;
    count++;
  }

  /**
   * Removes the element at the top of this stack and returns a
   * reference to it. Throws an EmptyCollectionException if the stack
   * is empty.
   * @return T element from top of stack
   * @throws EmptyCollectionException on pop from empty stack
   */
  public T pop(){
    if (isEmpty())
      throw new EmptyCollectionException("Stack");

    T result = top.getElement();
    top = top.getNext();
    count--;
 
    return result;
  }
   
  /**
   * Returns a reference to the element at the top of this stack.
   * The element is not removed from the stack.  Throws an
   * EmptyCollectionException if the stack is empty.
   * @return T element on top of stack
   * @throws EmptyCollectionException on peek at empty stack  
   */
  public T peek()  {
    if (isEmpty())
      throw new EmptyCollectionException("Stack"); 

    return top.getElement();
  }

  /**
   * Returns true if this stack is empty and false otherwise. 
   * @return boolean true if stack is empty
   */
  public boolean isEmpty()
  {
    return count == 0;
  }
 
  /**
   * Returns the number of elements in this stack.
   * @return int number of elements in this stack
   */
  public int size()
  {
    return count;
  }

  
  /**
   * Returns a string representation of this stack. 
   * @return String representation of this stack
   */
  public String toString()
  {
	  LinearNode<T> current = top;
	  String s = "";
	  int i =1;
	  while (current.getNext() != null){
		s = s + current.getElement() + "\n";
		current = current.getNext();
		i++;
		}
	  s = s + current.getElement();
	  
	  return s;
  }
  
  /**
   * Returns an iterator for elements currently in the list. 
   * @return an iterator for elements in this list
   */
  public Iterator<T> iterator()
  {
	  return new LinkedIterator<T>(top, count);
	  
  }
  //Test harness
  public static void main(String[] args){
	  LinkedStack<String> stack = new LinkedStack<String>();
	  String onTop;
	  
	  stack.push("A");
	  stack.push("B");
	  stack.push("C");
	  stack.push("D");
	  
	  //test size and toString
	  System.out.println("stack contains " + stack.size() + " items: \n" + stack.toString());
	  
	  //test isEmpty
	  /*while (! stack.isEmpty()){
		  onTop = stack.pop();
		  System.out.println("popped item is " + onTop);
		  
	  } */
	  // iterate through the stack and print
      Iterator<String> iter = stack.iterator();
      while (iter.hasNext()){
    	  System.out.println(iter.next());
      }
  }
  
}