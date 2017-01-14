/**
 * Edge class represents an edge that links two vertices of a graph. 
 * It stores both vertices it is linking, as well as a String that represents a bus line.
 * 
 * @author Peter Valovcik
 * @version 1.0, 6/12/15
 */

import java.util.*;


public class Graph implements GraphADT {
	
	private Node node[];		// an array of the Nodes(vertices) of the graph 
	private Edge edge[][];		// a matrix representing edges of the graph
	private int numNodes;		// number of Nodes(vertices) in the graph
	
	/**
	 * Creates a graph with n Nodes. Initializes the Edges of the graph as well as
	 * creating all of the necessary Nodes.
	 * 
	 * @param n, an integer that is the number of Nodes the graph contains
	 */
	
	public Graph(int n){
		this.node = new Node[n];			
		this.edge = new Edge[n][n];			
		for(int i = 0; i < n; i++){
			this.node[i] = new Node(i);		// Loop through and insert Nodes
			for(int j = 0; j < n; j++){
				this.edge[i][j] = null;		// Loop through and initialize Edges
			}
		}
		this.numNodes = n;					// set the number of Nodes of the graph
	}
	
	/**
	 * Inserts an Edge into the matrix at both proper positions. Throws GraphException if either of the nodes does not exist
	 * in the graph or the Edge to be inserted already exists.
	 * 
	 * @param nodeu, Node that represents a vertex of a graph
	 * @param nodev, Second Node that is a different vertex of the same graph
	 * @param busLine, a String storing data which is a bus line in this case
	 */
	
	public void insertEdge(Node nodeu, Node nodev, String busLine) throws GraphException {
		// check to make sure both nodes exist in the graph
		if (this.findNode(nodeu) == null || this.findNode(nodev) == null){
			throw new GraphException("Either one or both of the nodes do not exist in the graph.");
		}
		// check to make sure this edge does not exist already(only checks 1 location as checking both would be redundant)
		if (this.edge[nodeu.getName()][nodev.getName()] != null){
			throw new GraphException("An edge already exists between the nodes " + nodeu + " and " + nodev + ".");
		}
		// create the new edge and insert it into the proper locations of the matrix based on it being symmetric
		Edge toInsert = new Edge(nodeu, nodev, busLine);
		this.edge[nodeu.getName()][nodev.getName()] = toInsert;
		this.edge[nodev.getName()][nodeu.getName()] = toInsert;
		
	}
	
	/**
	 * Returns the Node in the graph that has the same name as the input parameter, or throws an exception
	 * if the node does not exist in the graph.
	 * 
	 * @param name, the integer representing the name of a Node
	 * @return the Node in the graph that has the same name as the input parameter
	 */
	
	public Node getNode(int name) throws GraphException {
		Node node = new Node(name);
		// check to make sure the node is in the graph
		if(this.findNode(node) == null){
			throw new GraphException("No node with specified name exists in this graph.");
		}
		// return the node found by the helper method findNode
		return this.findNode(node);
	}
	
	/**
	 * Method to return an iterator that iterates over the Edges that are incident to the Node that 
	 * is input as a parameter.
	 * 
	 * @param u, Node for which the incident edges will be checked
	 * @return an iterator of the stack containing the incident Edges to the input Node
	 */
	
	public Iterator<Edge> incidentEdges(Node u) throws GraphException {
		// create a stack to use to store incident edges and later produce an iterator
		Stack<Edge> S = new Stack<Edge>();
		// loop through the nodes and check if they share an edge with input node, push edge to stack if so
		for(int i = 0; i < this.numNodes; i++){
			Node v = new Node(i);
			if(this.areAdjacent(u, v)){
				S.push(this.getEdge(u, v));
			}
		}
		// check to make sure the stack isn't empty
		if(S.isEmpty()){
			throw new GraphException("No incident edges on this node to iterate through!");
		}
		// return an iterator over the stack
		return S.iterator();
	}
	
	/**
	 * Method that returns the Edge that connects 2 nodes if it, and the 2 nodes exist. Throws an
	 * exception if either of the nodes doesn't exist in the graph or if there is no edge connecting
	 * them.
	 * 
	 * @param u, first Node
	 * @param v, second Node
	 * @return an edge that connects the 2 nodes
	 */
	
	public Edge getEdge(Node u, Node v) throws GraphException {
		// make sure both nodes are in the graph
		if (this.findNode(u) == null || this.findNode(v) == null){
			throw new GraphException("Either one or both of the nodes do not exist in the graph.");
		}
		// makes sure that an edge doesn't already exist between the nodes
		if (this.edge[u.getName()][v.getName()] == null && this.edge[v.getName()][u.getName()] == null){
			throw new GraphException("An edge does not exist between those two nodes");
		}
		// return the edge connecting the nodes
		return this.edge[u.getName()][v.getName()];
	}
	
	/**
	 * Method to determine whether there is an edge connecting two nodes. Throws a exception if
	 * either of the nodes does not exist in the graph.
	 * 
	 * @param u, first Node
	 * @param v, second Node
	 * @return boolean representing whether or not the two nodes have an edge connecting them.
	 */
	
	public boolean areAdjacent(Node u, Node v) throws GraphException {
		// check to make sure both nodes are in the graph
		if (this.findNode(u) == null || this.findNode(v) == null){
			throw new GraphException("Either one or both of the nodes do not exist in the graph.");
		}
		// if the edges are initialized to null and the nodes exist, return false
		if (this.edge[u.getName()][v.getName()] == null && this.edge[v.getName()][u.getName()] == null){
			return false;
		} else {
			// return true if the nodes share an edge
			return true;
		}

	}
	
	/**
	 * Helper method similar to getNode. Returns null instead of throwing an exception
	 * if the node doesn't exist in the graph.
	 * 
	 * @param node, Node to be searched for in the graph
	 * @return the node in the graph that matches the input node, or null if no such node exists in the graph
	 */
	
	private Node findNode(Node node){
		// loop through and compare every node's name to input node's name
		// return node if found or null if all elements checked with no match
		for(int i = 0; i < numNodes; i++){
			if(this.node[i].getName() == node.getName()){
				return this.node[i];
			}
		}
		return null;
	}
}
