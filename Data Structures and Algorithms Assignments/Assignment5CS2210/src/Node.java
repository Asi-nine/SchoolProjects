/**
 * Node class represents a vertex of a graph. It stores a name for reference and a mark
 * to help with searches.
 * 
 * @author Peter Valovcik
 * @version 1.0, 1/12/15
 */

public class Node {
	
	
	private boolean mark; 		// a boolean to keep track of the Node during searches
	private int name; 			// integer name for reference
	
	/**
	 * Creates a new Node with an integer name. The mark is left uninitialized.
	 * 
	 * @param name, the integer that will be used as a name for reference
	 */
	
	public Node(int name){
		this.name = name;
		this.mark = false;
	}
	
	/**
	 * Sets the mark to keep track of this Node during searches.
	 * 
	 * @param mark, a boolean to keep track of the Node during searches
	 */
	
	public void setMark(boolean mark){
		this.mark = mark;
	}
	
	/**
	 * Returns the mark of the Node.
	 * 
	 * @return mark, a boolean to keep track of the Node during searches
	 */
	
	public boolean getMark(){
		return this.mark;
	}
	
	/**
	 * Returns the name of the Node.
	 * 
	 * @return name, the integer that will be used as a name for reference
	 */
	
	public int getName(){
		return this.name;
	}
}
