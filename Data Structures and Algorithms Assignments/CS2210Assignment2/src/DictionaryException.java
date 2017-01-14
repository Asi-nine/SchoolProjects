/**
 * DictionaryException extends the RuntimeException
 * Represents a situation in which either there already exists an entry in the dictionary containing
 * the same key as the key which is being inserted, or that an entry does not exist in the dictionary
 * with a key of one that is being deleted. Provides the user with a message based on what happened.
 * 
 * @author Peter Valovcik
 * @version 1.0, 19/10/15
 */

public class DictionaryException extends RuntimeException {
	
	public DictionaryException (String TEMP){
	      super ("Something happened: " + TEMP);
	   }
}
	

