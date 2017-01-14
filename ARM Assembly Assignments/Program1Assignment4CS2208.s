;Program to concatenate 2 strings, with the resulting string having a max length of 255 including its null character and being written to memory
;Author: Peter Valovcik

	AREA Program1, CODE, READONLY 
	
ENTRY 

DEFINITIONS

NULLCHAR	EQU				0x00									;defining null character which is 0x00 in ASCII

INITIALIZE

					LDR				R1, =STRING1					;Load the first string into R1
					LDR				R2, =STRING2					;Load the second string into R2
					LDR				R3, =STRING3					;Load the third string space into R3
					
FIRSTSTRING

					LDRB			R5, [R1], #1						;Load byte of string1 into R5
					CMP				R5, #NULLCHAR				;Check for end of string
					BEQ				SECONDSTRING				;if it's the end of string move to copying second string
					STRB			R5, [R3], #1						;Store character
					B					FIRSTSTRING					;loop to check next character
					
					
SECONDSTRING

					LDRB			R5, [R2], #1						;Load byte of string2 into R5
					STRB			R5, [R3], #1						;Store character
					CMP				R5, #NULLCHAR				;Check for end of string
					BNE				SECONDSTRING				;loop to check next character if not end of string
																				;fall through to finished if end of second string
FINISHED

					B					FINISHED							;infinite loop to keep program running without trying to run data as instructions
		
	AREA program1, DATA, READONLY

STRING1		DCB		"This is a test string1"				;String1 
EoS1			DCB 	NULLCHAR								;end of string1 
STRING2		DCB		"This is a test string2"				;String2
EoS2    		DCB		NULLCHAR								;end of string2 
					ALIGN

	AREA program1, DATA, READWRITE 

STRING3 		space 	0xFF 										;space for cancatenation of strings 1 and 2
					ALIGN
		
		
					END