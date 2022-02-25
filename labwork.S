  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

.global hexasc
.global time2string
.global delay
.global enable_interrupt

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

enable_interrupt: # enables interrupts globally
    ei
    j   return   

hexasc:
    andi     $a0, $a0, 0xf    # mask all bits except last 4
    slti     $t0, $a0, 10    # check if num or letter
    beq     $t0, $zero, letter
    nop
    addi     $v0, $a0, 0x30    # get apporpriate num
    jr     $ra
    nop
    
letter:
    addi     $v0, $a0, 0x37    # get appropriate letter
    jr     $ra
    
delay:
    blez     $a0, delayend    # if a0 = 0, branch to end delay
    nop
    addi     $a0, $a0, -1    # a0--
    addi     $t1, $0, 0     # a1 = 0
    
delayloop:
    beq     $t1, 4711, delay # if t1 = 4711, branch to outerloop
    addi     $t1, $t1, 1    # t1++
    j     delayloop
    
delayend:
    jr     $ra
    nop

time2string:
    PUSH     $ra        # save return address
    PUSH     $s0        # save s0
    
    move     $s0, $a0    # save address to s0
    
    srl     $a0, $a1, 12    # set a0 to the time shifted right by 12
    jal     hexasc        # convert to ascci char, result will be in v0
    nop
    sb     $v0, 0($s0)     # store ascii char to string
    
    srl     $a0, $a1, 8     # set a0 to the time shifted right by 8
    jal     hexasc        # convert to ascci char, result will be in v0
    nop
    sb     $v0, 1($s0)    # store ascii char to string
    
    addi     $t0, $0, 0x3a    # t0 = :
    sb     $t0, 2($s0)     # store : in string
    
    srl     $a0, $a1, 4     # set a0 to the time shifted right by 4
    jal     hexasc         # convert to ascci char, result will be in v0
    nop
    sb     $v0, 3($s0)     # store ascii char to string
                
    and     $a0,$a1,0xf    # mask
    jal     hexasc        # convert ascii char
    nop
    sb     $v0,4($s0)    # store ascii char code to string
    
    sb     $0,5($s0)    # append null byte

    
    POP     $s0
    POP     $ra
    jr     $ra
    nop

return:
    jr $ra
    nop