import java.util.*;


public class ArrayIterator2<T> implements Iterator {

	private int count;    // the number of elements in the collection
	   private int current;  // the current position in the iteration 
	   private T[] items; 

	   /**
	    * Sets up this iterator using the specified items.
	    * 
	    * @param collection  the collection for which the iterator will be created
	    * @param size        the size of the collection
	    */
	   public ArrayIterator2 (T[] collection, int size)
	   {
	      items = collection;
	      count = size;
	      current = size;
	   }

	   /**
	    * Returns true if this iterator has at least one more element
	    * to deliver in the iteraion.
	    *
	    * @return  true if this iterator has at least one more element to deliver
	    */
	   public boolean hasNext()
	   {
	      return (current > 0);
	   }

	   /**
	    * Returns the next element in the iteration. If there are no
	    * more elements in this itertion, a NoSuchElementException is
	    * thrown.
	    *
	    * @return  the next element in the iteration
	    * @throws NoSuchElementException  if a no such element exception occurs
	    */
	   public T next()
	   {
	      if (! hasNext())
	         throw new NoSuchElementException();

	 	  current--;
	 	  
	      return items[current]; 
	   }

	   /**
	    * The remove operation is not supported in this collection.
	    *
	    * @throws UnsupportedOperationException  if an unsupported operation
	    *                                        exception occurs
	    */
	   public void remove() throws UnsupportedOperationException
	   {
	      throw new UnsupportedOperationException();
	   }
	
}
