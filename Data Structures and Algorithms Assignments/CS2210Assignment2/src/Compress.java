
/**
 * Compression class main method
 * Reads a file byte by byte and attempts to store repeating bytes in a has table dictionary which can later be 
 * retrieved with an integer code. As the length of stored strings increases, the efficiency also increases as
 * the size of the integer code corresponding to the string will become smaller in size in comparison to that string.
 * Ultimately produces a compressed (smaller size) file of the original file that can then be decompressed to 
 * return the original file. **** NOTE: **** THE DECOMPRESSION IS A SEPARATE METHOD ****
 * 
 * @author Peter Valovcik
 * @version 1.0, 10/23/15
 */

import java.io.*;

public class Compress {
	public static void main(String[] args) throws DictionaryException, IOException {

		Dictionary hashDictionary = new Dictionary(4099);  //create a dictionary of a prime number > 4096 size
		BufferedInputStream in = null;					   // initialize an input stream
		BufferedOutputStream out = null;				   // initialize an output stream.
		
		try {
			
			/*
			 * Loop through and input the 256 ASCII characters into the dictionary. 
			 */
			int i = 0;
			while ( i < 256 ) {
				char tempChar = (char)i;
				String setup = "" + tempChar;
				DictEntry setupEntry = new DictEntry(setup, i);
				hashDictionary.insert(setupEntry);
				i++;
			}
			
			String inputFile = args[0];					//read command line argument as input file
			String outputFile = inputFile + ".zzz";     	//make output file the input file with a zzz extension
			
			
			in = new BufferedInputStream(new FileInputStream(inputFile)); 	// set the input stream to the input file

			out = new BufferedOutputStream(new FileOutputStream(outputFile));	// set the output stream to the output file
			
			MyOutput compressedOutput = new MyOutput(); 		// create a MyOutput class for writing to output file
			
			/*
			 * initialize variables needed for adding entries into the dictionary and compression
			 */
			String testString1 = "";
			String testString2 = "";
			int j = in.read();

			while ((j > (-1))){

				char c = (char)j;					// cast a char of the read byte to store in a string
				testString1 = testString2;			// string that will be shorter by 1 character
				testString2 = testString2 + c;		// string that will be longer by 1 character

				
				// check if the longer string is not in the dictionary while the shorter one is
				if ((hashDictionary.find(testString2) == null) && (hashDictionary.find(testString1) != null)) {

					// make a dictionary entry if the limit of 4096 entries has not been surpassed
					if (i < 4096){	
						DictEntry toEnter = new DictEntry(testString2, i);
						hashDictionary.insert(toEnter);
						i++;
					}
					// write the code of the smaller string to the output and reset the larger string
					compressedOutput.output(hashDictionary.find(testString1).getCode(), out);
					testString2 = "" + c;
				}
				j = in.read(); 		// get the next byte
			} 

			// write the code of the string that was store at the end of the loop but not written out
			compressedOutput.output(hashDictionary.find(testString2).getCode(), out);

			// make sure there is no partial data left over and close both input and output streams
			compressedOutput.flush(out);
			in.close();
			out.close();

		}
		/*
		 * Catch block to deal with the DictionaryException and IOException that can be thrown.
		 * Will deal with them and print out their respective error messages.
		 */
		catch(DictionaryException e) {
			System.out.println(e.getMessage());
		}
		catch(IOException e) {
			System.out.println(e.getMessage());
		}
		/*
		 * Finally block to clean up.
		 * Will make sure that both streams used are closed.
		 */
		finally {
			if (in != null){
				in.close();
			}
			if (out != null){
				out.close();
			}
		}
	}
}
