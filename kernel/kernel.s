; PixieVM kernel
;

VIDEO_RAM 		= $A000
COLOR_RAM 		= $B000
KERNEL_START 	= $E000

BKGND_COLOR		= $D000
BORDER_COLOR	= $D001

DATA_PORT_A		= $D100
DATA_PORT_B		= $D101
DDR_REG_A			= $D102
DDR_REG_B			= $D103

IRQ_CTRL_REG	= $D10D
CTRL_REG_A		= $D10E
CTRL_REG_B		= $D10F

JIFFY_CLK1		= $00
JIFFY_CLK2		= $01
JIFFY_CLK3		= $02
COUNTDOWN			= $03
SCNLINE				= $04						; pointer current screen line in video ram
CURCOLOR			= $06						; pointer current color ram location
CURCOL				= $08						; cursor column on current line
CURKEY				= $0A						; matrix coordinate of current key pressed
SHFLAG				= $0B						; flag for shift/ctrl keypress

RESET_VEC 		= $FFFC
IRQ_VEC 			= $FFFE

.org KERNEL_START

; start of kernel 
reset:
	call init_io									; initialize i/o
	
	mov [SCNLINE], VIDEO_RAM			; initialize current screen line in video ram
	mov [CURCOLOR], COLOR_RAM			; initialize current color ram location
	mov BYTE [CURCOL], $0					; cursor column on current line
		
	mov BYTE [COUNTDOWN], $14			; blink countdown initialization, 20 jiffies
	mov BYTE [BKGND_COLOR], $12		; background color
	mov BYTE [BORDER_COLOR], $11	; border color

endk:
	jmp endk

; initialize i/o
init_io:
	mov a, $087F
	mov [IRQ_CTRL_REG], al
	mov [DATA_PORT_A], al
	
	mov [CTRL_REG_A], ah
	mov [CTRL_REG_B], ah
	
	mov BYTE [DDR_REG_B], $00
	
	ret

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
	xor BYTE [d+x], $11
	
fcend:
	ret
	
; scan the keyboard
;
scn_key:
	mov al, $00
	mov [SHFLAG], al							; no shift/ctrl pressed
	mov BYTE [CURKEY], $40				; no matrix key pressed
	mov [DATA_PORT_A], al					
	
	ret
	
	.byte $00 dup (RESET_VEC-$$)	; fill rest of kernel area with zeros

	.word reset										; reset vector
	.word irq_handler							; IRQ vector
 
