; PixieVM kernel
;

VIDEO_RAM = $8000
KERNEL_START = $D000
RESET_VEC = $FFFC

.org KERNEL_START

start:
	jmp start
	.byte $00 dup (RESET_VEC-$$)
reset:
	.word KERNEL_START	; reset vector
	.word $0000					; IRQ vector
 
