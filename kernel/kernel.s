; PixieVM kernel
;

VIDEO_RAM 		= $A000
COLOR_RAM 		= $B000
KERNEL_START 	= $D000
KERNEL_DATA 	= $FF00
BKGND_COLOR		= $FF06
BORDER_COLOR	= $FF07
RESET_VEC 		= $FFFC
IRQ_VEC 			= $FFFE

.org KERNEL_START

; start of kernel 
start:

	mov BYTE [BKGND_COLOR], 4
	mov BYTE [BORDER_COLOR], 252

	mov c, VIDEO_RAM
	mov	d, COLOR_RAM
	xor a, a
	xor x, x	
loop:
	cmp x, $1000
	jz endk
	mov [c+x], al
	mov [d+x], al
	inx
	inc al
	jmp loop
	
endk:
	jmp endk

; irq/brk interrupt handler
irq_handler:

	push a
	push b
	push c
	push d
	push x
	
	pop x
	pop d
	pop c
	pop b
	pop a
	reti													; return from interrupt
	
	.byte $00 dup (RESET_VEC-$$)	; fill rest of kernel area with zeros

	.word KERNEL_START						; reset vector
	.word irq_handler							; IRQ vector
 
