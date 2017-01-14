/**
 * Edge class represents an edge that links two vertices of a graph. 
 * It stores both vertices it is linking, as well as a String that represents a bus line.
 * 
 * @author Peter Valovcik
 * @version 1.0, 1/12/15
 */

public class Edge {
	
	private Node firstEndpoint;			// Node representing one vertex
	private Node secondEndpoint;		// Node representing the other vertex
	private String busLine;				// A string that holds data; a bus line in this case
	
	/**
	 * Creates an Edge that represents a link between two Nodes (representing vertices of a graph)
	 * and holds String data which is a bus line in this case.
	 * 
	 * @param u, Node that represents a vertex of a graph
	 * @param v, Second Node that is a different vertex of the same graph
	 * @param busLine, a String storing data which is a bus line in this case
	 */
	
	public Edge(Node u, Node v, String busLine){
		this.firstEndpoint = u;
		this.secondEndpoint = v;
		this.busLine = busLine;
	}
	
	/**
	 * Returns a Node of the Edge
	 * 
	 * @return firstEndpoint, a Node representing one of the vertices the Edge is connecting
	 */
	
	public Node firstEndpoint(){
		return this.firstEndpoint;
	}
	
	/**
	 * Returns a different Node of the Edge
	 * 
	 * @return secondEndpoint, a Node representing one of the vertices the Edge is connecting
	 */
	
	public Node secondEndpoint(){
		return this.secondEndpoint;
	}
	
	/**
	 * Returns a String that contains the data of the Edge, in this case a bus line.
	 * 
	 * @return busLine, a String representing a bus line which is the data of the edge
	 */
	
	public String getBusLine(){
		return this.busLine;
	}
}
