;This is a program to verify the validitiy of a UPC code using checksum
;Made by: Peter Valovcik, 2016/03/03

	AREA prog1, CODE, READONLY
		
INITIALIZNG
		
			LDR		R1, =UPC							;Load address of UPC
			
			MOV	R2, #0								;Going to use R1 as a counter, so initializing it as 0
			MOV	R4, #0								;Using R4 as a sum total for even digits, so initializing it as 0
			MOV	R8, #0								;Using R4 as a sum total for odd digits, so initializing it as 0
			
PARSELOOP
			
			ADD			R2, R2, #2					;Increment count by 2
			LDRB		R3, [R1], #1 					;Load byte of upc code into R3
			SUB			R3, R3, #0x30				;Offset the ASCII value of the digit by 48 to get the decimal digit
			ADD			R8, R8, R3					;Add the current odd digit in R3 to the total stored in R8
			LDRB		R3, [R1], #1 					;Load byte of upc code into R3
			SUB			R3, R3, #0x30				;Offset the ASCII value of the digit by 48 to get the decimal digit
			CMP			R2, #12							;Is the count equal to 12? ((Length of UPC codes)
			BEQ			CONTINUE					;If yes, stop loop
			ADD			R4, R4, R3					;Add the current even digit in R3 to the total stored in R4
			B				PARSELOOP				;Loop for next 2 digits
			
CONTINUE
			
			MOV	R5, R3								;Move the 12th digit to Register 5 to use for checksum later on
			ADD		R8, R8, R8, LSL #1			;Shift left to get a multiplication by 3 on the odd sum
			ADD		R9, R4, R8						;Add the even sum to the previously calculated sum and store the result in R9 as per UPC calculation protocol
			SUB		R9, R9, #1						;Subtracting 1 from the previous step's total

MODULOTEN

			CMP		R9, #10								;Check if digit is 0-9
			BLT		RESULTSTORAGE			;Stop loop if R9 is less than 10 (thus should be 0-9)
			SUB		R9, R9, #10						;Subtract 10 from the value
			B			MODULOTEN					;Loop to check if digit is 0-9 again
			
RESULTSTORAGE

			RSB			R9, R9, #9					;Need to subtract that remainder from 9
			CMP			R9, R5							;Need to compare that remainder to the UPC code's last digit
			MOVEQ	R0, #1							;Store a 1 if the UPC code is valid
			MOVNE	R0, #2							;Store a 2 if the UPC code is invalid
															
			
FINISH	B				FINISH							;Stop program from executing DATA section
			
	AREA prog1, DATA, READWRITE
		
UPC	DCB	"060383755577"						;UPC string
			ALIGN
		
		END