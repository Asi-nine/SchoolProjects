import java.util.*;
import java.io.*;

public class TreeBuilder<T> {

	private String treeFile;
	private StringTokenizer tokens;

	public TreeBuilder(String inFile) {
		treeFile = inFile;
	}

	public LinkedBinaryTree<String> buildTree() throws IOException, MalformedTreeFileException{
		// set up the file reader and read the first line
		BufferedReader in=null;
		String line="";
		try{
			in = new BufferedReader(new FileReader(treeFile));
			line = in.readLine();

			// Tokenizen the first line - must contain whole tree
			tokens = new StringTokenizer(line);
		}catch (IOException e){
			throw new IOException("Unable to read file " + treeFile);
		}catch (NullPointerException e){
			throw new MalformedTreeFileException(treeFile, "No tokens found in file");
		}
		finally{
			if(in!=null)
				in.close();
		}
		LinkedBinaryTree<String> toReturn =  recursiveBuilder();
		return toReturn;
	}

	// we call the first time using 
	private LinkedBinaryTree<String> recursiveBuilder() throws MalformedTreeFileException{
		String token = null;
		// if we have entered here, we should have a new child 
		try{
			// should get the label as the first token
			token= tokens.nextToken();

			if ( token.equals("-")){
				return null;
			}
			//if it is an open brace, we make a left child and right child
			if ( token.equals("(")){
				LinkedBinaryTree<String> leftChild = recursiveBuilder();
				//read the comma
				tokens.nextToken();
				LinkedBinaryTree<String> rightChild = recursiveBuilder();
				// read the ")"
				tokens.nextToken();
				token = tokens.nextToken();		
				return new LinkedBinaryTree<String>(token, leftChild, rightChild);
			}

			else{  //otherwise, we have a leaf label
				return new LinkedBinaryTree<String>(token);
			}
			// must be no token

		}catch(Exception e){
			// Bundle exceptions caught here to IO exceptions, as they 
			// can only arise from a malformed file.
			throw new MalformedTreeFileException(this.treeFile, token);
		}
	}
}
