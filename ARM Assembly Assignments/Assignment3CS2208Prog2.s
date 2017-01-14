;This is a program to verify whether an alphabet string is a palindrome or not.
;Made by: Peter Valovcik, 2016/03/03

	AREA prog2, CODE, READONLY
		
INITIALIZING
			
				LDR				R1, =STRING					;Load the string to be tested into R1
			
				MOV			R2, R1								;Copy the string in R1 to R2
				MOV			R3, #0								; Initialize R3 to 0 to use as a counter for length
				MOV			R12, #0								; Initialize R12 to 0 to use as a counter for character count

LENGTH
			
				LDRB			R4, [R1], #1						; Load byte of string in R1 into R4
				CMP				R4, #0								;Check for end of string
				BEQ				LENGTHDONE					;Done calculating length so get out of loop
				ADD				R3, R3, #1						;Increment length counter
				CMP				R4, #0x41							;check to see if the character is an alphabet char
				BLT				LENGTH							;Go to next char if not alphabet char
				CMP				R4, #0x7A							;check to see if the character is an alphabet char
				BGT				LENGTH							;Go to next char if not alphabet char
				ADD				R12, R12, #1						;Increment character count if character is aphabet char
				B					LENGTH							;Keep looping through characters
			
LENGTHDONE
			
				MOV			R1, R2								;Move the string into R1 again
				LDR				R2,  =EoS							;Point R2 to end of string
				LDRB			R5, [R2], #-1						;Load the byte point to the EoS character
				ADD				R9, R12, LSR #1				;Put half the character count into R9
				CMP				R9, #0								;Check if half the characters rounds to 0 (0 or 1 characters)
				BEQ				PALINDROME					;Is a palindrom if the above check is equal, thus branch accordingly
				MOV			R8, #0								;Initialize R8 as a counter for number of characters compared
			
CHARACTERLOAD

				LDRB			R4, [R1], #1						;Load the first byte of the string to R4
				LDRB			R5, [R2], #-1						;Load the last byte of the string to R5

COMPARE
			
				CMP				R5, #0x41							;Compare R5 to the first alphabet character in ASCII
				BLT				LOADSECOND					;Branch if a non alphabet character was found
				CMP				R5, #0x7A							;Compare R5 to the last alphabet character in ASCII
				BGT				LOADSECOND					;Branch if a non alphabet character was found
				CMP				R4, #0x41							;Compare R4 to the first alphabet character in ASCII
				BLT				LOADFIRST						;Branch if a non alphabet character was found
				CMP				R4, #0x7A							;Compare R4 to the last alphabet character in ASCII
				BGT				LOADFIRST						;Branch if a non alphabet character was found
				ADD				R10, R4, #0x20					;Set R10 to the ASCII character 0x20 ahead of R4
				SUB				R11,	R4, #0x20					;Set R11 to the ASCII character 0x20 behind of R4
				CMP				R10, R5							;Check if R5 is a different case same character of R4
				BEQ				CHARARESAME				;Branch if characters are same but different case
				CMP				R11, R5							;Check if R5 is a different case same character of R4
				BEQ				CHARARESAME				;Branch if characters are same but different case
				CMP				R4, R5								;Compare the character values
				BEQ				CHARARESAME				;Branch if characters are the same
				B					NOTPALINDROME			;Not a Palindrome
			
LOADSECOND

				LDRB			R5, [R2], #-1						;Load the last byte of the string to R5
				B					COMPARE						;Compare again

LOADFIRST

				LDRB			R4, [R1], #1						;Load the first byte of the string to R4
				B					COMPARE						;Compare again

CHARARESAME

				ADD				R8, R8, #1						;Increment number of char successfully compared
				CMP				R8, R9								;Compare characters compared to half the character count
				BEQ				PALINDROME					;Is a palindrome
				B					CHARACTERLOAD			;Move to next two characters
			
PALINDROME
				
				MOV			R0, #1								;Put 1 in R0 if the the string is a palindrome
				B					FINISH								; go to end
			
NOTPALINDROME
				
				MOV			R0, #0								;Put 0 in R0 if the the string is not a palindrome
				
FINISH		B					FINISH								; Infinite loop so that data doesn't start overwriting things

	AREA prog2, DATA, READWRITE
		
STRING	DCB	"Was it a car or a cat I saw?"			;string
				ALIGN
EoS			DCB	0x00												;end of string 
				ALIGN
				
		END