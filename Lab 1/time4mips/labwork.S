  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.global delay
.global time2string

.macro	PUSH reg
	addi	$sp, $sp, -4
	sw	\reg, 0($sp)
.endm

.macro	POP reg
	lw	\reg, 0($sp)
	addi	$sp, $sp, 4
.endm
  #
  # Please add your own code below this line
  #

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text

time2string:
	#save registers
	PUSH $s0
	PUSH $s1
	PUSH $ra

	move $s0, $a0 # address
	move $s1, $a1 #timeinfo
	
	#first digit
	andi $t0, $s1, 0xF000 
	srl $a0, $t0, 12	#shift right to get value
	jal hexasc
	nop
	sb $v0, 0($s0)
	
	#second digit
	andi $t0, $s1, 0x0F00 
	srl $a0, $t0, 8	#shift right to get value
	jal hexasc
	nop
	sb $v0, 1($s0)
	
	#add colon
	li $t0, 0x3a
	sb $t0, 2($s0)
	
	#third digit
	andi $t0, $s1, 0x00F0 
	srl $a0, $t0, 4	#shift right to get value
	jal hexasc
	nop
	sb $v0, 3($s0)
	
	#4th digit
	andi $t0, $s1, 0x000F 
	move $a0, $t0
	jal hexasc
	nop
	sb $v0, 4($s0)
	
	#add NUL
	li $t1, 0x0
	sb $t1, 5($s0)
	
	#restore registers
	POP $ra
	POP $s1
	POP $s0
	
	jr $ra
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
hexasc: 
	and $a0, 0x0000000F #only care about last 4 bits
	slti $t1, $a0, 10 #t1 is 1 if a0<10
	
	beqz $t1, letter
	nop
	
	addi $t0, $0, 0x30
	add $v0, $a0, $t0
	
	jr $ra
	nop

letter:
	addi $t0, $t0, 0x37
	add $v0, $a0, $t0
	
	jr $ra
	nop
	
delay:
	PUSH $ra
	PUSH $s0
	PUSH $s1
	
	move $s0, $a0 #s0 -> remaining ms
	li $s1, 6 # for loop constant
	
	while: 
		ble $s0, 0, exit #check if ms <= 0, if yes, exit
		nop
		
		addi $s0, $s0, -1 # ms--
		li $t1, 0 #i = 0
		
		for: 
			bge $t1, $s1, while # i>=constant , if yes go to while loop
			nop
			
			addi $t1, $t1, 1 #i++
			j for #repeat for loop
			nop
		
	
	exit:
		POP $s1
		POP $s0
		POP $ra
		
		jr $ra
		nop
