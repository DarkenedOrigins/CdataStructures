.ORIG x3000

;;YOUR CODE STARTS HERE
	AND r0,r0,#0
	AND r1,r0,#0
	AND r2,r0,#0
AND r3,r0,#0
AND r4,r0,#0
AND r5,r0,#0
AND r6,r0,#0

	LD r1, STRING_START ;address into r1
PRINT	LDR r0,r1,#0	;fill r0 with value at r1
	BRz DONE			;if 0 is loaded go to halt
	LD r2,NEG_NINE		;check if value loaded is less than 9 to see if number or character
	ADD r2,r0,r2
	BRnz SUBSTRING
	OUT
	ADD r1,r1,#1
	BR PRINT

SUBSTRING
	LD r2, ASCII_NEG_ZERO 
	ADD r3,r0,r2
	ADD r4,r1,#1
F_ASK	ADD r1,r1,#1
	LDR r0,r1,#0
	LD r2,ASCII_NEG_ASTERISK 
	ADD r2,r0,r2
	BRp F_ASK
	ADD r2,r1,#1
	ADD r5,r1,#-1

	NOT r5,r5
	ADD r5,r5,#1

PRINT_O	ADD r6,r4,#0
PRINT_I	LDR r0,r6,#0
	OUT
	ADD r6,r6,#1
	ADD r0,r6,r5
	BRnz PRINT_I
	ADD r3,r3,#-1	
	BRp PRINT_O
	ADD r1,r2,#0
	BR PRINT
DONE	HALT	



NEG_NINE		.FILL #-57
ASCII_ZERO		.FILL x0030		;ASCII value of Zero
ASCII_NINE		.FILL x0039		;ASCII value of Nine
ASCII_NEG_ASTERISK   	.FILL xFFD6  		;negative of ascii value of *
ASCII_NEG_ZERO    	.FILL xFFD0		;negative of ascii value of 0
STRING_START 		.FILL x4000		;starting address of string
.END
