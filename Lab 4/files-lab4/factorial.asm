.text

addi $a0, $zero, 5
addi $a1, $a0, 0
addi $a2, $a0, 0
addi $a3, $a0, 0


beq $a0, $zero, zero #if input is 0, go to special label

addi $v0, $a0, 0  #v0 is initially n


factorial:
	addi	$a1, $a1, -1 #decrease a1
	beq	$a1, 1, end #if a1 is 1, we have multiplied to the end n * n-1 ... * 1
	
	add	$a3, $zero, $v0	# Store sum from multiplication
	add	$a2, $a1, $zero #a2 is n-1
	
	multiply: #multiply a2 by a3, result to v0 (a3 is total so far)
		addi	$a2, $a2, -1 #decrease a2
		
		add	$v0, $v0, $a3 #add a3 to total
		
		
		beq	$a2, 1, factorial # if we have multiplied a2 times, we go to the next multiplication in the factorial
		add $0, $0, $0 #nop
		
		beq	$zero, $zero, multiply # repeat
		add $0, $0, $0 #nop
		
			
zero:
	addi $v0, $zero, 1	
		
		
end: 
	beq $0, $0, end
	add $0, $0, $0
