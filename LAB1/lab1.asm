 ;Lab 1 
 ; assignment: develop a code to print a value stored in a register 
 ;             as a hexadecimal number to the monitor
 ; algorithm: turnin each group of four bits into a digit
 ;            calculate the corresponding ASCII character;
 ;            print the character to the monitor

 .ORIG x3000
	ADD R2,R2,#4
NEXCHAR	LD R5,FOUR
	AND R4,R4,#0
SETLOOP	ADD R3,R3,#0	
	BRn NEGLOOP
	ADD R4,R4,R4
	ADD R3,R3,R3
	ADD R5,R5,#-1	
	BRz PRINT
	BRnzp SETLOOP
NEGLOOP	ADD R4,R4,R4
	ADD R4,R4,#1
	ADD R3,R3,R3
	ADD R5,R5,#-1
	BRz PRINT
	BRnzp SETLOOP
PRINT	LD R5,TEN 
	ADD R5,R5,R4
	BRn NUM
	LD R4,SIXFIVE
	ADD R0,R4,R5
	OUT
	ADD R2,R2,#-1
	BRz FIN
	BRnzp NEXCHAR
NUM	LD R5,FOUREIGHT
	ADD R0,R5,R4
	OUT
	ADD R2,R2,#-1
	BRz FIN
	BRnzp NEXCHAR
FIN	HALT	   
SIXFIVE	.FILL	#65
FOUREIGHT	.FILL	#48
TEN	.FILL	#-10
FOUR	.FILL	#4
 .END

