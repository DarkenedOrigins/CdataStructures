; Implement a program to find the nearest smaller (or equal) perfect square of a given positive number
; The input will be stored in R2 and output (the nearest perfect square) should be stored in R3
; TODO: Write a subroutine called "PSquare" which returns the nearest perfect square of a given input and 
;       you must invoke this subroutine in the main part.
; Note : R2, R4, R5 and R6 must be left unchanged in PSquare.
;
; 
; PSquare :  input is stored in R2
;            output is stored in R3

.ORIG	x3000		; starting address is x3000
JSR	PSquare
	HALT
;;YOUR CODE STARTS HERE
PSquare
	ST r7, saver7
	ST r2, saver2
	ST r4, saver4
	ST r5, saver5
	ST r6, saver6
	
	NOT r2,r2
	ADD r2,r2,#1	; make r2 neagtive
	AND r4,r4,#0
	AND r5,r4,#0
CHECK	ADD r4,r4,#1
	ADD r5,r5,#1
	
	JSR mult
	
	ADD r6,r0,r2
	BRnz CHECK
	ADD r4,r4,#-1
	ADD r5,r5,#-1
	JSR mult
	ADD r3,r0,#0
	LD r7, saver7
	LD r2, saver2
	LD r4, saver4
	LD r5, saver5
	LD r6, saver6
	RET
 saver7	.BLKW #1
 saver2	.BLKW #1
 saver4	.BLKW #1
 saver5	.BLKW #1
 saver6	.BLKW #1

mult
	ST r5, MultSaveR5
	AND r0,r0,#0
LOOP	ADD r0,r0,r4
	ADD r5,r5,#-1
	BRp LOOP
	LD r5,  MultSaveR5
	RET
 MultSaveR5	.BLKW #1


.END



