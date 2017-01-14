/**
 * DictEntry represents an entry into a hash table dictionary.
 * 
 * 
 * @author Peter Valovcik
 * @version 1.0, 19/10/15
 */

public class DictEntry {
	
	private String keyValue; // a unique key, but also used to store a string that can be retrieved with the code
	private int codeValue; // code used to represent the unique key string

	/**
	 * Creates a new DictEntry with the specified data.
	 * 
	 * @param key the string that will act as a key in the hash table
	 * @param code the integer used to represent the key in a compression
	 */
	
	public DictEntry(String key, int code){	
		keyValue = key;
		codeValue = code;
	}
	
	/**
	 * Returns the string keyValue.
	 * 
	 * @return keyValue: the string that acts as a key in the hash table
	 */
	
	public String getKey(){
		return keyValue;
	}
	
	/**
	 * Returns the integer codeValue.
	 * 
	 * @return codeValue: the integer that can be used to replace a key string for compression
	 */
	
	public int getCode(){
		return codeValue;
	}	
}