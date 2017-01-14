/**
 * Map class represents a map of bus lines in a city using a graph. Creates a graph that represents bus
 * lines of a city from an input file.
 * 
 * @author Peter Valovcik
 * @version 1.0, 8/12/15
 */


import java.util.*;
import java.io.*;

public class Map {
	
	private String input, testLine;										// String of the input file and a bus line
	private Graph graph = null;												// graph representing the bus lines
	private int width, height, changes, changeCount, start, end;		// various parameters of the graph (self explanatory names)
	private Stack<Node> S;													// stack storing a path of nodes
	
	/**
	 * Constructor of a map representing bus lines in a city.
	 * 
	 * @param inputFile file to read
	 * @throws MapException
	 * @throws IOException
	 * @throws GraphException 
	 */
	
	public Map(String inputFile) throws MapException, IOException, GraphException{
		
		this.testLine = "Luka<3<3";			// initiate testline to a string that will not be seen from input
		this.changeCount = -1;				// initiate the change counter used for recursive calls in other methods
		this.input = inputFile;				// set the input file
		this.S = new Stack<Node>();			// initiate the stack storing a path
		
		// make a file and make sure it exists, throw an exception otherwise
		File inputFileTest = new File(this.input);
		if(!inputFileTest.exists()){
			throw new MapException("File attempting to be input does not exist.");
		}
				
		// create a buffered reader of the file
		BufferedReader inputScan = new BufferedReader(new FileReader(inputFileTest));
		
		int count = 0;
		String s;				// 1st string for parsing
		String s2 = null;		// 2nd string for parsing
		
		// loop through the first 4 lines of the input to parse necessary data
		while (count < 4){
			
			//read a line of the file
			s = inputScan.readLine();
			count++;
			
			//set width based on number on 2nd line
			if (count == 2){
				this.width = Integer.parseInt(s.trim());
			}
			
			//set height based on number on 3nd line
			if (count == 3){
				this.height = Integer.parseInt(s.trim());
			}
			
			//set changes based on number on 4th line
			if (count == 4){
				this.changes = Integer.parseInt(s.trim());
			}
		}
		//create a graph based on width and height
		this.graph = new Graph(this.width * this.height);
		
		int countNode = -1; 				// int to count the number of the node in the graph (corresponds to Node name)
		
		// read 2 lines of the file and store them in separate variables as long as it is not the end of the file
		s = inputScan.readLine();
		if (s!=null){
			s2 = inputScan.readLine();
		}
		
		// loop as long as there is 1 line to parse
		while (s!=null){
			// prepare 2 string readers to use to parse both strings (if both exist, only 1 if not)
			StringReader in = new StringReader(s);
			StringReader in2 = null;
			if (s2!=null){
				in2 = new StringReader(s2);
			}
			int j = 0;							// used to store int representation of characters in string 1
			int k = 0;							// used to store int representation of characters in string 2
			int stringLength = s.length();		// length of the strings (should be equal if input is valid)
			
			//loop through parsing the strings as long as they have characters to parse
			while (j != -1){
				j = in.read();
				if(s2!=null){
					k = in2.read();
				}
				
				// break out of loop if end of string is reached
				if (j == -1){
					break;
				}
				char c = (char)j;				// currently parsed char of string 1
				
				/*
				 * If the parsed character of string 1 is a 0, then increment the currentNode counter
				 * and set the start of the path equal to the currentNode. If the second string's parsed
				 * character is not white space and the second string exists, insert an edge between the
				 * currentNode, and the node in the same position of the next line with the busLine value
				 * of the second string's parsed character.
				 */
				if (c == '0'){
					countNode++;
					this.start = countNode;
					if (s2 !=null && (char)k != ' '){
						this.graph.insertEdge(this.graph.getNode(countNode), this.graph.getNode(countNode+((stringLength+1)/2)), Character.toString((char)k));
					}
				}
				
				/*
				 * If the parsed character of string 1 is a 1, then increment the currentNode counter
				 * and set the end of the path equal to the currentNode. If the second string's parsed
				 * character is not white space and the second string exists, insert an edge between the
				 * currentNode, and the node in the same position of the next line with the busLine value
				 * of the second string's parsed character.
				 */
				
				else if (c == '1'){
					countNode++;
					this.end = countNode;
					if (s2 !=null && (char)k != ' '){
						this.graph.insertEdge(this.graph.getNode(countNode), this.graph.getNode(countNode+((stringLength+1)/2)), Character.toString((char)k));
					}
				}
				
				/*
				 * If the parsed character of string 1 is a +, then increment the currentNode counter.
				 * If the second string's parsed character is not white space and the second string 
				 * exists, insert an edge between the currentNode, and the node in the same position 
				 * of the next line with the busLine value of the second string's parsed character.
				 */
				
				else if (c == '+'){
					countNode++;
					if (s2 !=null && (char)k != ' '){
						this.graph.insertEdge(this.graph.getNode(countNode), this.graph.getNode(countNode+((stringLength+1)/2)), Character.toString(((char)k)));
					}
				}
				
				// If the parsed character of string 1 is white space, do nothing.
				else if (c == ' '){
					// do nothing	
				}
				
				/*
				 * If the parsed character of string 1 is any other character, then it is a busLine name
				 * and thus add an edge with this as the busLine connecting the currentNode and the node
				 * immediately following. 
				 */
				
				else{
					this.graph.insertEdge(this.graph.getNode(countNode), this.graph.getNode(countNode+1), Character.toString(c));
				}
				
			}
			// get the next lines if they exist
			if (s2!=null){
				s = inputScan.readLine();
				if (s!=null){
					s2 = inputScan.readLine();
				}
			} else{
				s = null;
			}
			// close the string readers
			in.close();
			if (in2!=null){
				in2.close();
			}
		}
		// close the buffered reader
		inputScan.close();
	}
	
	/**
	 * Returns the graph parameter of the Map class if it exists.
	 * 
	 * @return graph, the graph of this map
	 * @throws MapException
	 */
	
	public Graph getGraph() throws MapException{
		// check to make sure the graph exist
		if (this.graph == null){
			throw new MapException("No graph is defined.");
		}
		// return graph if it exists
		return this.graph;
	}
	
	/**
	 * Returns and iterator over a path of nodes leading from the start to the end and using only
	 * up to as many busLine changes as allowed (if such a path exists).
	 * 
	 * @return iterator over a node path if it exits, null otherwise
	 * @throws GraphException
	 */
	
	public Iterator<Node> findPath() throws GraphException{
		
		// create a start and end node
		Node begin = this.graph.getNode(this.start);
		Node finish = this.graph.getNode(this.end);
		// check to make sure a path exits between these nodes
		boolean test = findPath(begin, finish);
		if(test){
			// reset the variables of the map that were changed by invoking the findPath helper method
			this.testLine = "Luka<3<3";
			this.changeCount = -1;
			//return the iterator over the Stack of the Map that was modified by the findPath helper method
			return this.S.iterator();
		}
		// return null if a path does not exist
		return null;
	}
	
	/**
	 * findPath helper method determines whether there is a path from node b to node e
	 * using only the amount of bus line changes stores in the changes variable of map.
	 * It stores this path in the map variable S which is a stack.
	 * 
	 * @param b, beginning node
	 * @param e, ending node
	 * @return boolean, true if a path exits, false otherwise
	 * @throws GraphException
	 */
	
	private boolean findPath(Node b, Node e) throws GraphException{
		
		//mark start node and push it on stack
		b.setMark(true);
		this.S.push(b);
				
		// base case, start is the end and we did not exceed the number of bus changes limit
		if (this.changeCount <= this.changes && b == e){
			return true;
		}
		
		// variables to hold old values in case we need to change back
		int holdOldValue = this.changeCount;
		String holdLine = this.testLine;
		
		//iterator over the edges incident on the start node
		Iterator<Edge> iter = this.graph.incidentEdges(b);
		
		// loop through incident edges
		while(iter.hasNext()){
			Edge line = iter.next();
			String s = line.getBusLine();
			// increase the bus changes count if we change busLines
			if (!s.equals(this.testLine)){
				this.changeCount++;
			}
			// set the bus line to the current one we are on
			this.testLine = s;
			
			// take the node that is connected to start node via the edge
			Node u;
			if(line.secondEndpoint().equals(b)){
				u = line.firstEndpoint();
			}else{
				u = line.secondEndpoint();
			}
			// make sure node is not marked and perform a recursive call on it if
			// also make sure that the number of changes allowed has not already been exceeded
			if (u.getMark() != true && this.changeCount <= this.changes){
				if (findPath(u, e) == true){
					return true;
				}
			}
			// undo changes to bus change count and current bus line if we move backwards
			if (holdOldValue < this.changeCount){
				this.changeCount--;
				this.testLine = holdLine;
			}
			
		}
		// unset the start node so that other recursive calls can use it and pop it off the stack
		b.setMark(false);
		this.S.pop();
		
		return false;
	}
}
