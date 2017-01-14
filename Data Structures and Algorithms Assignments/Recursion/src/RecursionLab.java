import java.io.*;

public class RecursionLab{

	public static void reversePrint (String inString){

		if (inString.length() > 0)		// if string is not empty
		{

			// your code goes here
			

			System.out.print(inString.charAt(inString.length()-1));
			reversePrint(inString.substring(0, inString.length()-1));
			
			
				
			}
			

		}
	
	public static String reverseStringHelper (String inString){
		if (inString.length() > 0){
			
			
			return ("" + inString.charAt(inString.length()-1) + reverseStringHelper(inString.substring(0, inString.length()-1)));	
			}
		else
			return "";
	}



	public static void main(String[] args){
		String inString = "abcde";

		// test reversePrint
		reversePrint(inString);
		// test reverseString
		String revString = reverseString(inString);
		System.out.println(revString);
		
		// test isPalindrome
		System.out.println(isPalindrome(inString));
	}

	public static String reverseString(String inString){
		if (inString.length() > 0){
			String endChar = "" + inString.charAt(inString.length()-1);
			String finalString = endChar.concat(reverseStringHelper(inString.substring(0, inString.length()-1)));
			return finalString;
			
		}
		else
			return "";
	}
	
	public static boolean isPalindrome(String s){
		if(s.equals(reverseString(s))){
			return true;
		}
		else
			return false;
	}
}

