  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0, 1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop


time2string:
	#save registers
	PUSH ($s0)
	PUSH ($s1)
	PUSH ($ra)

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
	POP ($ra)
	POP ($s1)
	POP ($s0)
	
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
	PUSH ($ra)
	PUSH ($s0)
	PUSH ($s1)
	
	move $s0, $a0 #s0 -> remaining ms
	li $s1, 6 # for loop constant
	
	while: 
		ble $s0, 0, exit #check if ms <= 0, if yes, exit
		nop
		
		subi $s0, $s0, 1 # ms--
		li $t1, 0 #i = 0
		
		for: 
			bge $t1, $s1, while # i>=constant , if yes go to while loop
			nop
			
			addi $t1, $t1, 1 #i++
			j for #repeat for loop
			nop
		
	
	exit:
		POP ($s1)
		POP ($s0)
		POP ($ra)
		
		jr $ra
		nop
			
#delay:
#	jr $ra
#	nop
