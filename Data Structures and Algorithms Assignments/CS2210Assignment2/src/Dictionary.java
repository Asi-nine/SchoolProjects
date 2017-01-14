/**
 * Dictionary class implementing the DictionaryADT
 * This class represents a Dictionary storing strings and codes to retrieve those strings within a
 * hash table. It stores nodes that contain the entries so that separate chaining may be used as a method
 * for dealing with collisions.
 * 
 * @author Peter Valovcik
 * @version 1.0, 21/10/15
 */

public class Dictionary implements DictionaryADT {

	/*
	 * Helper class Node
	 * Used to allowed for implementation of separate chaining via linked list.
	 */

	private static class Node {

		private DictEntry keyAndCode; 	     	// a DictEntry
		private Node next;					 	// pointer to the next Node

		/**
		 * Sets the DictEntry and the pointer to the next Node
		 * 
		 * @param pair, a DictEntry (contains a key and a code itself)
		 * @param nextEntry, a pointer to the next Node, or null if there is no next Node
		 */

		private Node(DictEntry pair, Node nextEntry){
			this.keyAndCode = pair;
			this.next = nextEntry;
		}

		/**
		 * Returns the DictEntry stored in the Node
		 * 
		 * @return keyAndCode, a DictEntry
		 */

		private DictEntry getkeyAndCode(){
			return this.keyAndCode;
		}

		/**
		 * Returns the next Node in the list
		 * 
		 * @return next, a Node
		 */

		private Node getNext(){
			return this.next;
		}

		/**
		 * Sets the next Node in the list
		 * 
		 * @param nextEntry, a Node
		 */

		private void setNext(Node nextEntry){
			this.next = nextEntry;
		}

		/**
		 * Sets the keyAndCode of the Node
		 * 
		 * @param pair, a DictEntry
		 */

		private void setkeyAndCode(DictEntry pair){
			this.keyAndCode = pair;
		}

	}


	private int dictSize; 			// size of the hash table

	private Node[] dictionary; 		// Array of Node helper class to use as hash table

	private int total; 				// counter to keep track of # elements in table

	/**
	 * Creates a Dictionary of the given size and initializes it.
	 * @param size, size of the hash table in the Dictionary
	 */
	public Dictionary(int size){

		dictSize = size;
		total = 0;
		dictionary = new Node[dictSize];			// Creation of hash table

		for (int i = 0; i < dictSize; i++){			// Initialization of the hash table
			dictionary[i] = null;
		}
	}

	/**
	 * insert will insert a DictEntry into the hash table as a Node if there is no other entry
	 * with a matching key.
	 * 
	 * @param pair, a DictEntry to be inserted into the hash table
	 */

	public int insert (DictEntry pair) throws DictionaryException {
		Node toinsert = new Node(pair, null); 			// make a Node with the DictEntry
		int hashValue = hashFunction(pair.getKey());	// get hash value based on key

		if (this.find(pair.getKey()) != null){			// check if key exists in dictionary, if so throw exception
			throw new DictionaryException("An entry with the same key already exists.");

		} else if (dictionary[hashValue] == null){		// check if location is null, if so insert and increment total
			dictionary[hashValue] = toinsert;
			total++;
			return 0;									// report no collision

		} else {										// if location to insert not null, set Node to be inserted as
			toinsert.setNext(dictionary[hashValue]);	// new head of linked list and increment total.
			dictionary[hashValue] = toinsert;
			total++;
			return 1;									// report a collision
		}
	}

	/**
	 * remove will check if a key exists in the table, throw an exception if it doesn't exist,
	 * or otherwise will remove the entry with that key.
	 * 
	 * @param key, unique key used as basis for removal from hash table
	 */

	public void remove (String key) throws DictionaryException {

		int hashValue = hashFunction(key); 		// get the hash value of the key

		if (this.find(key) == null) {
			throw new DictionaryException("No entry with that key found."); 	// throws an exception if there is no
																				// entry with the key.
		} else {	
			
			Node current = dictionary[hashValue];		// set up current node
			Node previous =new Node(null, null);		// set up previous node

			if (dictionary[hashValue].getkeyAndCode().getKey().equals(key)){	// removes if first node in array is the one
				dictionary[hashValue] = null;									// with the matching key, decrements total
				total--;
			} else {
				/*
				 * Iterate through the linked list one node at a time (keeping track of the previous,
				 * current node) while the key does not match the input key, and the 
				 * node is not null.
				 */
				while (!(current.getkeyAndCode().getKey().equals(key))) {
					previous = current;
					current = current.getNext();		
				}
				previous.setNext(current.getNext()); 	 // set the previous node to the next node of the node containing the key
				total--;								 // once it is found and decrements total.
			}
		}
	}

	/**
	 * Will search the hash table based on the hash value of the key. Will return
	 * null if there exists no entry with said key, or return the DictEntry if one
	 * exists with said key.
	 * 
	 * @param key, unique key used to look up an entry in the hash table
	 */


	public DictEntry find (String key) {

		int hashValue = hashFunction(key);			// get the hash value of the key
		if (dictionary[hashValue] == null){			// returns null if there is no entry at the hash value
			return null;
		} else {
			
			Node current = dictionary[hashValue];						// set the first node to a variable
			
			/*
			 * loop until node with DictEntry with matching key is found of until end of the linked list
			 */
			while (!current.getkeyAndCode().getKey().equals(key)){
				if (current.getNext() == null){			// return null if end of list without matching key
					return null;
				}else{
					current = current.getNext();
				}
			}
			return current.getkeyAndCode();				// return the DictEntry with matching key
		}
	}

	/**
	 * numElements returns the number of elements contained in the dictionary
	 */

	public int numElements() {
		return total;
	}

	/**
	 * Performs a hash function on a numeric representation of the key and returns a value.
	 * Does not allow for storing in values larger than the size of the dictionary.
	 * 
	 * @param key
	 * @return hashNumber, a number that is the result of performing a hash function
	 */

	private int hashFunction(String key){
		int hashNumber = 0;
		for (int i = 0; i < key.length(); i++){						// convert the characters into integers
			int j = (int)key.charAt(i);
			hashNumber = (((hashNumber + j)*2333)) % dictSize;		// perform some arithmetic on the integers using a prime number 
		}															// and makes sure to not exceed dictionary size for hash number
		return hashNumber;
	}
}
