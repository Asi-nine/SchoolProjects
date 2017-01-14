import java.io.*;

public class FindCommonAncestor {
	public static void main(String[] args){

		BufferedReader consoleReader  = new BufferedReader(new InputStreamReader(System.in));

		LinkedBinaryTree<String> linkedBinaryTree = null;
		TreeBuilder<String> theTreeBuilder = null;

		try{

			theTreeBuilder = new TreeBuilder<String>(args[0]);
			linkedBinaryTree = theTreeBuilder.buildTree();

			//Example prompt for user
			System.out.print("Enter first element: ");
			String firstElement = consoleReader.readLine();
			
			System.out.print("Enter second element: ");
			String secondElement = consoleReader.readLine();
			
			String result = linkedBinaryTree.lowestCommonAncestor(firstElement, secondElement);
			
			System.out.println("The Tree contains");
			System.out.println("The lowest common ancestor is: " + result);

		}
		catch( Exception e ){
			// you must handle exceptions as specified in the assignment description
			// consolereader.close or something
		} 

	}
}
