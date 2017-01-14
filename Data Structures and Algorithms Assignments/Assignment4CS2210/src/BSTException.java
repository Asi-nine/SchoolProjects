/**
 * BSTException extends the RuntimeException
 * Represents a situation in which either there already exists an entry in the BST containing
 * the same key as the key which is being inserted, or that an entry does not exist in the BST
 * with a key of one that is being deleted. Provides the user with a message based on what happened.
 * 
 * @author Peter Valovcik
 * @version 1.0, 9/11/15
 */

public class BSTException extends RuntimeException {
	public BSTException(String errorString){
		super("Something happened: " + errorString);
	}
}
