;Program to evaluate the expression, y = ax^2 +bx +c, where R0 is initially x, AA is a, BB is b, CC is c, DD is d, and the result is stored into R0 after evaluation if it
;is less than or equal to d, otherwise d's value is stored. This is accomplished with a subroutine call which should not alter any working registers other than R0.
;After the subroutine call, the value in R0 should be doubled and that result stored in R1.
;Author: Peter Valovcik

	AREA program3, CODE, READONLY 
	
ENTRY

INITIALIZE

					MOV			R0, #0x3						;initialize R0 as the x value, 3 in this case
					MOV			R2, #0x4						;putting a 4 into R2, this is to test to make sure that the subroutine is returning values to used registers properly 
					ADR				SP, STACK1					;initialize the stack pointer
					BL				SUBROUTINE				;call leaf subroutine to perform some arithmetic
					ADD				R1, R0, R0					;store double the value that was stored in R0 from the subroutine call in R1

FINISHED

					B					FINISHED						;infinite loop to keep program running without trying to run data as instructions

SUBROUTINE

					STMDB			SP!, {R1-R3}					;Store the values that are in registers that will be used into the stack so they can be used during the subroutine
					LDR				R1, AA							;put the value of a into R1
					LDR				R2, BB							;put the value of b into R2
					MLA				R3, R0, R1, R2				;Multiply a by x, and then add b (ax+b), and store result in register 3
					LDR				R1, CC							;put the value of c into R1
					MLA				R2, R0, R3, R1				;Multiply x by the previous result, then add c (x(ax+b)+c), and store the result in register 2
					LDR				R1, DD							;put the value of d into R1
					CMP				R2, R1							;Compare the result of ax^2+bx+c to d
					MOVGE		R0, R1							;if the result is larger than or equal to d, move d to R0
					MOVLT			R0, R2							;if the result is less than d, move the result to R0
					LDM				SP!, {R1-R3}					;Restore the registers that were used to their original values (default of LDM is IA)
					MOV			PC, LR							;Return to caller

	AREA program3, DATA, READONLY
					
AA				DCD				0xFFFFFFFB				;Storing variable "a" as AA
BB				DCD				0x6								;Storing variable "b" as BB
CC				DCD				0x7								;Storing variable "c" as CC
DD				DCD				0xA								;Storing variable "d" as DD
					
						
	AREA program3, DATA, READWRITE 
					
					SPACE 		0xFF							;Space for stack
					ALIGN
STACK1		DCD 			0x00								;Marking top of stack for pointer
					
						
					END