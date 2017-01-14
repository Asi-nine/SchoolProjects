import java.io.*;
import java.util.Iterator;
/**
 * PhoneTest.java:
 * This class creates an Ordered List of Phone objects.
 * @author CS1027 for Lab
 */

public class PhoneTest {

   public static void main(String[] args) throws Exception {

   // get the filename from the user
     
      BufferedReader keyboard = new BufferedReader
                                 (new InputStreamReader(System.in),1);       
      System.out.println("Enter name of the input file: ");
      String filename= keyboard.readLine();
    
   // create object that controls file reading and opens the file
         
      InStringFile reader = new InStringFile(filename);
      System.out.println("\nReading from file " + filename + "\n");

    // your code to create (empty) ordered list here
      ArrayOrderedList<Phone> phoneList = new ArrayOrderedList<Phone>();

           
      
   // read data from file two lines at a time (name and phone number)
     
      String name, phone;
      do {
        name = (reader.read());
        phone = (reader.read());

        // your code to add the entry to your ordered list here
        Phone phoneToAdd = new Phone(name, phone);
        phoneList.add(phoneToAdd);



              
      } while (!reader.endOfFile()); 
   
      System.out.println("Here is my phone book:");

      // your code to print the ordered list here
      System.out.println(phoneList.toString());
      
      // iterate through the file and print the names only
      Iterator<Phone> iter = phoneList.iterator();
      while (iter.hasNext()){
    	  System.out.println(iter.next().getName());
      }
      
   // iterate through the file and print the numbers only
      Iterator<Phone> iter2 = phoneList.iterator();
      while (iter2.hasNext()){
    	  System.out.println(iter2.next().getPhone());
      }
      
      

      //What file(s) would you need to add to your project if you changed phoneList so that it was declared and created by
      //LinkedOrderedList phoneList = new LinkedOrderedList();

      // You would need to add LinkedList.java, LinkedOrderedList.java and ListIterator.java
      
      
      //What would you then need to change in the code you wrote for steps 3 and 5?
      
      // Nothing.
   
      
      // Print toString2
      System.out.println(phoneList.toString2());
      
      
      //Question: Consider the linked implementation of the ListADT, LinkedList.java. Would the exact same toString2 method work in LinkedList.java too? 
      
      // Yes.
      
      
      // close file
      
      reader.close();
      System.out.println("\nFile " + filename + " is closed.");      
     
   }
}
