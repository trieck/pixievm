; PixieVM kernel
;

VIDEO_RAM 		= $A000
COLOR_RAM 		= $B000
KERNEL_START 	= $D000
KERNEL_DATA 	= $FF00
BKGND_COLOR		= $FF06
BORDER_COLOR	= $FF07
JIFFY_CLK1		= $FF08
JIFFY_CLK2		= $FF09
JIFFY_CLK3		= $FF0A
COUNTDOWN			= $FF0B
RESET_VEC 		= $FFFC
IRQ_VEC 			= $FFFE

.org KERNEL_START

; start of kernel 
reset:

	mov BYTE [COUNTDOWN], $14			; blink countdown initialization, 20 jiffies
	mov BYTE [BKGND_COLOR], $fc		; background color
	mov BYTE [BORDER_COLOR], $4		; border color

endk:
	jmp endk

; irq/brk interrupt handler
irq_handler:

	push a
	push b
	push c
	push d
	push x
	
	call update_clk
	call flash_cursor
		
	pop x
	pop d
	pop c
	pop b
	pop a
	reti													; return from interrupt

; update jiffy clock
update_clk:
	inc BYTE [JIFFY_CLK1]
	jnz ucend
	inc BYTE [JIFFY_CLK2]
	jnz ucend
	inc BYTE [JIFFY_CLK3]
ucend:
	ret
	
; flash cursor every 20 jiffies
flash_cursor:
	mov c, VIDEO_RAM
	mov	d, COLOR_RAM
	
	dec BYTE [COUNTDOWN]					; countdown
	jnz fcend
	
	mov BYTE [COUNTDOWN], $14			; reset countdown
	
	xor BYTE [c+x], $db						; flash cursor
	xor BYTE [d+x], $4
	
fcend:
	ret
	
	.byte $00 dup (RESET_VEC-$$)	; fill rest of kernel area with zeros

	.word reset										; reset vector
	.word irq_handler							; IRQ vector
 
