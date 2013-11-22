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
SCNLINE				= $FF0C						; pointer current screen line in video ram
CURCOLOR			= $FF0E						; pointer current color ram location
CURCOL				= $FF10						; cursor column on current line
RESET_VEC 		= $FFFC
IRQ_VEC 			= $FFFE

.org KERNEL_START

; start of kernel 
reset:
	
	mov [SCNLINE], VIDEO_RAM			; initialize current screen line in video ram
	mov [CURCOLOR], COLOR_RAM			; initialize current color ram location
	mov BYTE [CURCOL], $0					; cursor column on current line
		
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
	
	call update_clk								; update jiffy clock
	call flash_cursor							; flash the cursor
	call scn_key									; scan the keyboard
		
	pop x
	pop d
	pop c
	pop b
	pop a
	reti													; return from interrupt

; update jiffy clock
;
update_clk:
	inc BYTE [JIFFY_CLK1]
	jnz ucend
	inc BYTE [JIFFY_CLK2]
	jnz ucend
	inc BYTE [JIFFY_CLK3]
ucend:
	ret
	
; flash cursor every 20 jiffies
;
flash_cursor:
	dec BYTE [COUNTDOWN]					; countdown
	jnz fcend
	
	mov BYTE [COUNTDOWN], $14			; reset countdown
	
	mov ah, 0
	mov al, [CURCOL]							; cursor column on current line
	mov x, a
	
	mov c, [SCNLINE]							; current screen line in video ram
	mov d, [CURCOLOR]							; current color ram location
	xor BYTE [c+x], $dc						; flash cursor
	xor BYTE [d+x], $4
	
fcend:
	ret
	
; scan the keyboard
;
scn_key:
	ret
	
	.byte $00 dup (RESET_VEC-$$)	; fill rest of kernel area with zeros

	.word reset										; reset vector
	.word irq_handler							; IRQ vector
 
