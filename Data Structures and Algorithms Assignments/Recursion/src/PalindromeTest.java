import java.util.Scanner;



public class PalindromeTest {

	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		System.out.println("Please enter a word to check if it is a palindrome.");
		String s = scanner.next();
		if(isPalindrome(s)){
			System.out.println("Your word " +s + " is a palindrome!");

		}
		else
			System.out.println("Your word " +s + " is not a palindrome!");



	}



	public static String reverseString(String inString){
		if (inString.length() > 0){
			String endChar = inString.substring(inString.length()-1, inString.length());
			String reverseConcat = "";
			for(int i = (inString.length() - 2); i >= 0; i--){
				reverseConcat = reverseConcat + inString.charAt(i);

			}
			String reverse = endChar.concat(reverseConcat);
			return reverse;
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
