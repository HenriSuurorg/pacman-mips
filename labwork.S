# Edited by Henri Suurorg
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

.global enable_interrupt

enable_interrupt: # enables interrupts globally
    PUSH $ra
    ei
    POP $ra
    j   $ra
    nop

stop:
    j stop
    nop