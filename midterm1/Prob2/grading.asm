; x3000

LD R2, STRSTART

LOOP
LDR R0, R2, #0
BRz FINISH		; We are done when we hit NULL
LD R1, BITMASK
JSR BITSWAP		; Do the bitswap
STR R0, R2, #0		; Writes back to the original location
ADD R2, R2, #1
BRnzp LOOP 
FINISH 
HALT

STRSTART .FILL x4000
BITMASK .FILL x0003	; set n = 3

;Do not touch or change and code above this line
;---------------------------------------------
;You must not change the separation line above
;Please write ALL your code for BITSWAP in between the separations lines,
;including all the labels, code, and .FILL commands

 
;Subroutine to swap bits
;Input: 
;R0: the ascii that to be swapped 
;R1: the number of bits to be swapped
; You can assume R1 is always 0, 1, 2, or 3
;Output: R0, the swapped ascii

;;YOUR CODE STARTS HERE

BITSWAP
	ST r7,SAVER7
	ADD r6,r0,#0	;move to r6 for safe keeping
	ADD r0,r1,#0	;check if r1 is 1,2,3,4 and bitmask middle values appropiatly 
	BRz ZERO
	ADD r0,r1,#-1
	BRz ONE
	ADD r0,r1,#-2
	BRz TWO
	ADD r0,r1,#-3
	BRz THREE
	ADD r0,r1,#-4
	BRz FOUR
	ZERO 
		BR DONE	;if r1 is zero (n=0)then finish
	ONE LD r5, bitmask1		; the bit masking is to isolate the middle bits 
BR STUFF
	TWO LD r5, bitmask2
BR STUFF
THREE	LD r5, bitmask3
BR STUFF
FOUR	LD r5, bitmask4

STUFF	AND r3,r6,r5	;r3 contains middle and nothing else
	ADD r0,r6,#0
	JSR EXTRACT
	ADD r4,r0,#0	;r4 has least significant and nothing else
	
	NOT r1,r1
	ADD R1,r1,#1	;r1 being made neg to do 8-n
	AND r5,R5,#0	;clear r5
	ADD r5,r5,#8	;fill with 8
	ADD r5,r5,r1 ; For 8-n 
loop2	ADD r6,r6,r6 ;left shift of input
	ADD r5,r5,#-1;for 8-n times
	BRp loop2	
			;r6 now has the most significant value and other stuff in the upper 8 bits
	ADD R0,r6,r3	;ADD together the isolated values r3 has middle
	ADD r0,r0,r4	;add the least significant
	LD r6, lastmask	;mask off the first 8 bits 
	AND r0,r0,r6
	LD r7,SAVER7
DONE	RET
SAVER7	.BLKW #1
lastmask	.FILL	xFF
bitmask1	.FILL	x7e
bitmask2	.FILL	x3c
bitmask3	.FILL	x18
bitmask4	.FILL	x0

;You must not change the separation line below.
;Write all your code for BITSWAP above this line
;=============================================


;DO NOT CHANGE THE GIVEN CODE BELOW
;=============================================
;;EXTRACT Subroutine (Given Code) 
;;Input: R0 - ASCII value
;;       R1 - n (between 0 and 4) bits to be extracted
;;Output:R0 - value of the n most significant bits of input

EXTRACT
ST R1, SAVER1
ST R2, SAVER2
ST R3, SAVER3
NOT R1, R1 
ADD R1, R1, #9
ETOP
ADD R1, R1, #0 
BRz EBOT
ADD R1, R1, #-1
LD R3, MASK
AND R0, R0, R3
AND R2, R2, #0

EINNER 
ADD R3, R2, R2
NOT R3, R3
ADD R3, R3, #1
ADD R3, R3, R0
BRz EINNERBOT
ADD R2, R2, #1
BRnzp EINNER

EINNERBOT
ADD R0, R2, #0
BRnzp ETOP

EBOT
LD R1, SAVER1
LD R2, SAVER2
LD R3, SAVER3
RET
MASK .FILL x00FE
SAVER1 .FILL #0
SAVER2 .FILL #0
SAVER3 .FILL #0

.END
