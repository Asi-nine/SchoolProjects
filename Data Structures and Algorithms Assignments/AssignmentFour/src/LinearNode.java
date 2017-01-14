
/**
 * Linear node represents a node in a linked list
 * @author beth
 *
 */
public class LinearNode<E> {

	//link
	private LinearNode<E> next;

	//data
	private E element;

	/** 
	 * Create an empty node
	 * 
	 */
	public LinearNode(){
		this.next = null;
		this.element = null;
	}

	/**
	 * Create a node storing a specific element
	 * @param element the element to store
	 */
	public LinearNode( E element){
		this.next = null;
		this.element = element;
	}

	/**
	 * Returns the next node
	 * 
	 * @return reference to the node following this one
	 */
	public LinearNode<E> getNext(){
		return this.next;
	}

	/**
	 * @return the element
	 */
	public E getElement() {
		return element;
	}

	/**
	 * @param next the next to set
	 */
	public void setNext(LinearNode<E> next) {
		this.next = next;
	}

	/**
	 * @param element the element to set
	 */
	public void setElement(E element) {
		this.element = element;
	}

	



}
