;this code uses a stack to implement a calculator in reverse polish notation
;it uses getc and out to get characters from the keyboard and uses evaluate to determind which character 
;it does this by subtracting ascii values 
;it uses the pop_op to load r3 and r4 with the values in the stack 
;it then does the plus minus multiply divide and exponential to those values 
;in the order r4 (operator) r3 

.ORIG x3000
	
;your code goes here
BRnzp EVALUATE
POP_OP ;this subroutine fills r3 and r4 with values from the stack 
	ST R7, SAVE_R7 ;save r7 since we are jumping in a subroutine 
	JSR POP	;get value from stack
	ADD r5,r5,#0 ;check is we got a value 
	BRp INVALID ; no value invalid
	ADD R3,r0,#0;put value into r3
	JSR POP	;get value 
	ADD r5,r5,#0;check if we got a value 
    	BRp INVALID ; no value invalid
	ADD r4,r0,#0;put value in r4
	LD R7,SAVE_R7 ;load r7 with value 
	RET
SAVE_R7	.BLKW #1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX
	ST r3, SAVE_R3
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
        BRz PRINT	; print if r5 is zero
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
FIN	LD r5, SAVE_R3
	HALT
SIXFIVE		.FILL	#65
FOUREIGHT	.FILL	#48
TEN			.FILL	#-10
FOUR		.FILL	#4
SAVE_R3		.BLKW #1	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE
	GETC;get character 
	OUT;display character to monitor 
	LD r1, NEG_TREETWO ;load r1 with -32  
	ADD r1,r0,r1 ;add -32 to r0 beacuse it contains an ascii value 
	BRz EVALUATE	; if the ascii value was 32 (space) and since we subtraced 32 from it it should now be zero
			; if it is zero go back to beginning 
	LD R1, NEG_FIVENINE
	ADD r1,r0,r1	;check is the character entered is a semicolon 
	BRz SEMI_COLON 
	LD r1, NEG_NINEFOR
	ADD r1,r0,r1;check is the character entered is a carat (^) 
	BRz EXP
	LD r1, NEG_FIVEATE
	ADD r1,r0,r1;check is the character entered is a colon if it is go invalid 
	BRzp INVALID ; if the ascii character value is bigger than the semi colon go invalid
	LD r1, NEG_FORTWO
	ADD r1,r0,r1;check is the character entered is a astrik
	BRz MUL
	LD R1, NEG_FORTREE ;check is the character entered is a plus
	ADD r1,r0,r1
	BRz PLUS
	LD R1, NEG_FORFIVE
	ADD r1,r0,r1;check is the character entered is a hyphen 
	BRz MIN
	LD r1, NEG_FORSEVEN
	ADD r1,r0,r1 ;check is the character is a slash  
	BRz DIV
	BRn INVALID	;if the chracter is anything b4 slash go invalid
	LD r1, NEG_FORATE
	ADD r0,r1,r0	;subtract ascii offset from number and then push into stack 
	JSR PUSH
	BRNZP EVALUATE	
NEG_TREETWO	.FILL	#-32
NEG_FIVENINE	.FILL	#-59
NEG_NINEFOR	.FILL	#-94
NEG_FIVEATE	.FILL	#-58
NEG_FORTWO	.FILL	#-42
NEG_FORTREE	.FILL	#-43
NEG_FORFIVE	.FILL	#-45
NEG_FORSEVEN	.FILL	#-47
NEG_FORATE	.FILL	#-48

SEMI_COLON
	AND r0,r0,#0;clear r0
	JSR POP	;pop character
	ADD r3,r0,#0	;put into r3 for print hex
	ADD r5,r5,#0	;check if we got a value from pop
	BRp INVALID
	JSR POP	;pop again to check if there is anyother value in the stack
	ADD r5,r5,#0;if there is another value go invalid
	BRz INVALID
	BRNZP PRINT_HEX

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS	;r4+r3
;your code goes here
	JSR POP_OP ;fill r3 and r4 
	AND r0,r0,#0;clear r0
	ADD R0,r4,r3;add r3 and r4 
	JSR PUSH ;push r0 into stcack
	BRnzp EVALUATE ;go back to evaluate
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN	;r4-r3
	JSR POP_OP ;fill r3 and r4 `
	AND r0,r0,#0;clear r0
	NOT r3,r3;not r3 and add 1 to make negative
	ADD r3,r3,#1
	ADD r0,r3,r4	;add r4 and r3
	JSR PUSH	;push value
	BRnzp EVALUATE
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL	;r4*r3
	JSR POP_OP ;fill r3 and r4 
	AND r0,r0,#0	
MULT_LOOP
	ADD R0,R0,R4;add r4 to r0 r3 times 
	ADD R3,R3,#-1;decrement r3
	BRn ZERO_MUL ;if zero make r0 zero and push
	BRp MULT_LOOP ;loop if r3 isnt zero
	JSR PUSH
	BRNZP EVALUATE	
ZERO_MUL	AND R0,R0,#0
		JSR PUSH
		BRNZP EVALUATE	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV	;r4/r3
	JSR POP_OP ;fill r3 and r4 
	AND r0,r0,#0
	NOT r3,r3;make r3 negative and check if zero
	BRz INVALID ;cant divide by zero
	ADD r3,r3,#1
DIVLOOP	;r0 is the quotient 
	ADD r4,r4,r3;r4-r3
	BRz ZERO ;if zero add 1 to quotient,push and go back 
	BRn NEG ;push and go back
	ADD R0,R0,#1;if not zero start loop again after u add one to quotitent
	BRnzp DIVLOOP
ZERO	ADD r0,r0,#1
NEG	JSR PUSH
	BRNZP EVALUATE	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP	;r4^r3
	JSR POP_OP ;fill r3 and r4 
	ADD r3,r3,#-1;u multiply exponent minus 1 number of times 
	ADD r2,r4,#0;load r2 with r4 
	ADD r1,r4,#0;load r1 with r4 
	AND r0,r0,#0;clear r0
POWERLOOP
	ADD r0,r4,r0
	ADD r2,r2,#-1;multiplies r4 with its self cuz r4 is in r2
	BRp POWERLOOP
	ADD r2,r1,#0;refills r2 with initial r4 value
	ADD r4,r0,#0;put r0 value into r4
	AND R0,r0,#0;clear r0
	ADD r3,r3,#-1;decrements exponent 
	BRp POWERLOOP
	ADD r0,r4,#0;fills r0 with r4 to do the push
	JSR PUSH 
	BRNZP EVALUATE
;
;INVALID subroutine 
;
INVALID
	LEA R0, INVALID_STRING ;store address of string into r0
	PUTS;prints string
	HALT
INVALID_STRING	.STRINGZ	"Invalid Expression" 
	
;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET


POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
