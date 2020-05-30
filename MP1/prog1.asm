;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming studio, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST

; you will need to insert your code to print the histogram here
; The purpose of this code is to print the values that the previous code stored to the terminal in a formatted way. 
;my code does this by using 2 counters and a subroutine that i made in lab1. 
;r1 is a loop conuter becuase there are 27 enteries made by the previous program 1 for characters and 26 for the various letters.
;r6 is my up counter which indicates the offset i need to get to the corret mem location. it starts at zero since 
; i know where the infromation starts from. and after every print it goes up by one and is then added to the mem address.
;this point to the location of the next entry. 
; the way my print subroutine works is that it stores the bits four at a time. when four are stored it derterminds the coresponding hex value for that set of four. 
; after print r4 is cleared and another 4 values are stored inside r4 and the process begins again. 
;since lc3 has 16bit mem the loop runs for 4 iterations.  



;	LD R0,STR_START ; r0 is loadec with the adress of the string so the sting can be printed out
;	PUTS		;Sting is printed
;	LD R0,NEWLINE	; R0 is loaded with newline character
;	OUT		; this is printed twice
;	OUT
					;i had previously thought that i needed to print the line for the histogram as well so yeah


	LD R1, TWO_SEVEN	;r1 is loaded with the number 27
	AND R6,R6,#0	; r6 now contains zero
NEXLINE	LD R0,AT	; loads the ascii value for @ (where the histogram starts from) 
	ADD R0,R6,R0	; adds r6 the up counter to @ value to determind whihc letter
	OUT		; prints out this character
	LD R0,SPACE	; loads ascii character for space into r0
	OUT		;prints space
	LD R0,HIST_ADDR	; loads the addres where the histogram starts from in memory 
	ADD R0,R0,R6	; adds r6 to address to see which letter in the histogram we are on 
	LDR R3,R0,#0	; loads r3 with the value at the address stored into r0
			; this is where the hex print sub routine starts 
	LD R2,FOUR	;makes r2 4 this is the outer loop counter since 16 bits has 4 hex characters
NEXCHAR LD R5,FOUR	;makes r5 4 since each hex value corespond to 4 binary numbers 
        AND R4,R4,#0	;clears r4
SETLOOP ADD R3,R3,#0    ;adds zero to r3 to check is positive or negative 
        BRn NEGLOOP	;braches if first number is one
        ADD R4,R4,R4	;left shifts R4 becuase they are adding an zero to r4
        ADD R3,R3,R3	;left shifts r3
        ADD R5,R5,#-1   ; decrement r5
        BRz PRINT	;if r5 iz zero that means 4 numbers are inside r4 and its time to print the first hex character
        BRnzp SETLOOP	;starts the loop all over again 
NEGLOOP ADD R4,R4,R4	;if number was neg r4 is shifted
        ADD R4,R4,#1	; one is added 
        ADD R3,R3,R3	; r3 is shifted
        ADD R5,R5,#-1	; r5 is decremented
        BRz PRINT	; print is r5 is zero
        BRnzp SETLOOP	;do loop again 
PRINT   LD R5,TEN	;print time means there are 4 values in r4 
        ADD R5,R5,R4	; since r4 has a value between 0 and 15 and 10 to 15 means a letter needs to be printed we subtracts 10 from it
			; if number is negative it is stored in r5 and r4 is untouched and there for given an ascii offset and printed
			; if number is positive r5 now has the ascii offset nessescary for printing chracters 
        BRn NUM		;branch to number printing if negative
        LD R4,SIXFIVE	;if it was positve or zero that means r5 has the offset so r4 is loaded with 65
        ADD R0,R4,R5	;65 is the dec value for A in ascii we add r5 to this value to get the correct value
        OUT		;print
        ADD R2,R2,#-1	;dec print counter	
        BRz FIN		;finish loop if r2 is zero
        BRnzp NEXCHAR	;start next chracter loop again
NUM     LD R5,FOUREIGHT	;load r5 with 48 the dec value for ascii 0
        ADD R0,R5,R4	;add r4 to this so we have correct value 
        OUT		;pritn this
        ADD R2,R2,#-1	;dec counter 
        BRz FIN		; finsh if r2 is zero
        BRnzp NEXCHAR
				;end of subroutine 	

FIN     LD R0,NEWLINE	;if printing is done load newline character and print it to start next line
	OUT	
	ADD R6,R6,#1	;incriment r6 the upcounter 
	ADD R1,R1,#-1	;decrement r1 which says how many times we need to print 
	BRz DONE	;if 27 cycles have finished go to done 
	BRnzp NEXLINE	;if not keep going 
	
DONE	HALT		; halt

SIXFIVE .FILL   #65		;65 for ascii offset for characters 
FOUREIGHT       .FILL   #48	;for number ascii ofset 
TEN     .FILL   #-10		;for subroutine range test
FOUR    .FILL   #4		;for counters in subroutine 
NEWLINE	.FILL	x000A		;new line ascii chracter 
TWO_SEVEN	.FILL	#27	;for amount of entries in histogram and loop cycles 
AT	.FILL	x0040		;ascii chracter for @
SPACE	.FILL	x0020		;ascii chracter for space

; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address

; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
