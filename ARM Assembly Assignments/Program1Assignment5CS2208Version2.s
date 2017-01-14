;Program that will calculate a variable, x, to a power, n, in a recursive manner utilizing a stack data structure.
;Size of one frame is 0x24, thus with the stack size of 0x1BB a max of 0xC complete frames can exist. If more frames than this are needed, increase the stack size
;Author: Peter Valovcik, Date: March 31, 2016.


	AREA power, CODE, READONLY 

DEFINITIONS

x					EQU				0x3								;define the value of x here
n					EQU				0xc								;define the value of n here

MAIN

					MOV			R0, #n							;Initialize R0 as the n value
					CMP				R0, #0							;safety check for n not being less than 0
					BLT				FINISHED						;don't execute the program if n is less than zero since infinite recursion would occur, go to the end without doing anything
					ADR				SP, STACK1					;initialize the stack pointer
					STR 				R0, [SP], #0x4  			;push the n parameter on the stack
					MOV			R0, #x							;initialize R0 as the x value
					STR 				R0, [SP], #0x4  			;push the x parameter on the stack
					ADD				SP, SP, #0x4				;reserve a space in stack for return value
					BL				POWER						;call power subroutine
					LDR				R0, [SP, #-0x4]!				;load the result in r0 and pop it from the stack
					SUB				SP, SP, #0x8				;also remove the parameters from the stack
					ADR				R1, RESULT					;get the address of the result variable
					STR				R0, [R1]						;store the final result in the result variable
					
;--------------------------------------------------------------------------------
FINISHED
					B					FINISHED						;infinite loop, end of the program
;--------------------------------------------------------------------------------	 
POWER

					STM				SP!, {R0-R2, FP, LR}		;Store the values that are in registers that will be used into the stack so they can be used during the subroutine
					MOV  			FP, SP      					;set the fp for this call
					ADD				SP, SP, #0x4				;create space for the y local variable

					LDR				R0, [FP, #-0x1C]			;get the x parameter from the stack
					LDR				R1, [FP, #-0x20] 			;get the n parameter from the stack
					CMP				R1, #0							;compare n to 0
					MOVEQ		R2, #1							;prepare 1 as the return value if n is 0
					STREQ			R2, [FP, #-0x18]  			;store the return value in the stack
					BEQ				RETURN						;go to return from the function call
					
					ANDS			R2, R1, #1					;Check if n is odd
					BNE				ODDN							;If odd, break to section to deal with an odd n value
																			;Otherwise fall through to n being even
																			
EVENN
					
					MOV			R2, #0							;set 0 to use for logicla shift right addition in next step
					ADD				R1, R2, R1, LSR#1		;divide n by 2
					STR				R1, [SP], #0x4				;push the parameter n on the stack
					STR				R0, [SP], #0x4				;push the parameter x on the stack
					ADD				SP, SP, #0x4			    ;create space for the return value	

					BL				POWER						;recursive call
					
					LDR				R2, [SP, #-0x4]!				;Store the result from recursive call in R2 and pop stack
					STR				R2, [FP]						;Store the result as local variable y
					SUB				SP, SP, #0x8				;also remove the parameters from the stack
					MUL				R1, R2, R2					;Store the result of power(x, n/2) * power(x, n/2) in R1  ( same thing as y * y)
					STR				R1, [FP, #-0x18]			;Store result of previous multiplication in result space from the caller
					B					RETURN						;go to return from the function call
					
					
ODDN

					SUB				R1, R1, #1      				;prepare the new n parameter value
					STR				R1, [SP], #0x4				;push the parameter n on the stack
					STR				R0, [SP], #0x4				;push the parameter x on the stack
					ADD				SP, SP, #0x4			    ;create space for the return value	
					
					BL				POWER						;recursive call
					
					LDR				R2, [SP, #-0x4]!				;Store the result from recursive call in R2 and pop stack
					SUB				SP, SP, #0x8				;also remove the parameters from the stack
					MUL				R1, R0, R2					;Store the result of x * power(x, n-1) in R1
					STR				R1, [FP, #-0x18]			;Store result of previous multiplication in result space from the caller
																			;Fall through to return
					
RETURN

					MOV			SP, FP							;collapse all working spaces for this function call
					LDMDB			SP!, {R0-R2, FP, PC}		;load all registers and return to the caller

;--------------------------------------------------------------------------------

	AREA power, DATA, READWRITE 

RESULT		DCD				0x00								;Making space for result
STACK1		DCD 			0x00								;Marking top of stack for pointer					
					SPACE 		0x1bb							;Space for stack
					ALIGN
					
						
					END