;Program that will take 1 string and remove any occurences of the word "the" and save the resulting string to memory.
;Author: Peter Valovcik

	AREA program2, CODE, READONLY 
	
ENTRY

DEFINITIONS

NULLCHAR	EQU				0x00													;defining null character which is 0x00 in ASCII
SPACEBAR	EQU				0x20													;defining space character which is 0x20 in ASCII
LOWT			EQU				0x74													;defining lowercase t character which is 0x74 in ASCII
LOWH			EQU				0x68													;defining lowercase h character which is 0x68 in ASCII
LOWE			EQU				0x65													;defining lowercase e character which is 0x65 in ASCII

INITIALIZE

					LDR				R0, =STRING3									;Load String being used as a queue into R0
					LDR				R1, =STRING1									;Load the string to have "the" removed from into R1
					LDR				R2, =STRING2									;Load the string to have the result copied into into R2
					MOV			R3, #0												;Initialize R3 as a counter for queue length

CHECKCHAR

					LDRB			R5, [R1], #1										;Load byte of string in R1 into R5
					CMP				R5, #SPACEBAR								;Check if the current character is a space
					BEQ				CHECKTHE										;Go to check for "the" starting with t if the stored char is a space
					CMP				R5, #NULLCHAR								;Check if the current character is the nullchar
					BEQ				CHECKTHE										;Go to check for "the" starting with t if the stored char is the nullchar
					B					QUEUECHAR									;Go to enter the character into the queue if it is neither of the 2 previous characters
					
COPYQUEUE

					LDR				R0, =STRING3									;Set address to beginning of queue

COPYLOOP

					CMP				R3, #0												;Make sure queue isn't empty
					BEQ				COPYSPECIALCHAR						;Move to copy the special character (space or null) if stack empty
					LDRB			R4, [R0], #1										;load first char and increment pointer
					STRB			R4, [R2], #1										;store the char into string 2
					SUB				R3, R3, #1										;decrement the queue length
					B					COPYLOOP										;loop and copy next char in queue
					
COPYSPECIALCHAR

					STRB			R5, [R2], #1										;Store the space or null character into string 2
					CMP				R5, #NULLCHAR								;check for end of string
					BEQ				FINISHED											;go to end of program if end of string
					LDR				R0, =STRING3									;reset queue pointer
					MOV			R3, #0												;reset length counter
					B					CHECKCHAR									;Check next character
					
QUEUECHAR

					STRB			R5, [R0], #1										;Store character
					ADD				R3, R3, #1										;Increment queue length
					B					CHECKCHAR									;Check next char

CHECKTHE
					CMP				R3, #3												;Check to see if the length of string to check for "the" is 3
					BNE				COPYQUEUE									;Copy whatever is in the queue if the length isn't 3 since it can't be "the"
					LDR				R0, =STRING3									;reset stack pointer
					LDRB			R4, [R0], #1										;load first char and increment pointer
					CMP				R4, #LOWT										;Check for lower case t
					BNE				COPYQUEUE									;Not "the" if it doesn't begin with t, so copy the queue
					LDRB			R4, [R0], #1										;load second character and increment pointer
					CMP				R4, #LOWH										;Check for lower case h
					BNE				COPYQUEUE									;Not "the" if second letter is not h, so copy the queue
					LDRB			R4, [R0], #1										;load third character and increment pointer		
					CMP				R4, #LOWE										;Check for lower case e
					BNE				COPYQUEUE									;Not "the" if third letter is not e, so copy the queue
					B					COPYSPECIALCHAR						;Move to copy space or null and ultimately reset queue deleting "the"
					
FINISHED

					B					FINISHED											;infinite loop to keep program running without trying to run data as instructions
			
	AREA program2, DATA, READONLY 
			
STRING1		DCB				"them   the   the1   1the bathe   the"	;String1 
EoS				DCB				NULLCHAR										;end of string1 
					ALIGN

	AREA program2, DATA, READWRITE 

STRING2		SPACE			0xFF												;Space for string 2
STRING3		SPACE 		0xFF												;Space for the string to be used as queue
					ALIGN
		
					END