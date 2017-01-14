import java.io.*;
import java.util.Iterator;

public class TestPathToRoot {

	public static void main(String[] args) {
		LinkedBinaryTree<String> theTree = null;
		TreeBuilder<String> theTreeBuilder = null;

		try{
			theTreeBuilder = new TreeBuilder<String>(args[0]);
			theTree = theTreeBuilder.buildTree();
		}
		catch( MalformedTreeFileException e) {
			System.out.println( e.getMessage());
		}
		catch( IOException e){
			System.out.println("Error reading file: " + args[0] + "\n" + e.getMessage());
		}
		
		Iterator<String> temp = theTree.iteratorInOrder();
		while(temp.hasNext())
		{
			String element = temp.next();
			System.out.printf("For element: %s - the path to the root is: ", element);
			Iterator<String> temp2 = theTree.pathToRoot(element);
			while(temp2.hasNext())
			{
				System.out.print(temp2.next() + " ");
			}
			System.out.println();
		}
		/*
		System.out.print("For element: D - the path to the root is: ");
		
		Iterator<String> temp = theTree.pathToRoot("D");
		while(temp.hasNext())
		{
		System.out.print(temp.next() + " ");
		}
		
		System.out.print("\nFor element: B - the path to the root is: ");
		temp = theTree.pathToRoot("B");
		while(temp.hasNext())
		{
		System.out.print(temp.next() + " ");
		}
		
		System.out.print("\nFor element: E - the path to the root is: ");
		temp =theTree.pathToRoot("E");
		while(temp.hasNext())
		{
		System.out.print(temp.next() + " ");
		}
		
		System.out.print("\nFor element: A - the path to the root is: ");
		temp = theTree.pathToRoot("A");
		while(temp.hasNext())
		{
		System.out.print(temp.next() + " ");
		}
		
		System.out.print("\nFor element: F - the path to the root is: ");
		temp = theTree.pathToRoot("F");
		while(temp.hasNext())
		{
		System.out.print(temp.next() + " ");
		}
		
		System.out.print("\nFor element: C - the path to the root is: ");
		temp = theTree.pathToRoot("C");
		while(temp.hasNext())
		{
		System.out.print(temp.next() + " ");
		}
		
		System.out.print("\nFor element: G - the path to the root is: ");
		temp = theTree.pathToRoot("G");
		while(temp.hasNext())
		{
		System.out.print(temp.next() + " ");
		}
		*/

	}

}
