.text

addi $a0, $zero, 5
addi $a1, $a0, 0
addi $a2, $a0, 0

beq $a0, $zero, zero #if input is 0, go to special label

addi $v0, $a0, 0  #v0 is initially n


factorial:
	addi	$a0, $a0, -1 #decrease a1
	beq	$a0, 1, end #if a0 is 1, we have multiplied to the end n * n-1 ... * 1
	
	add	$a2, $zero, $v0	# Store sum from multiplication
	add	$a1, $a0, $zero #a1 is n-1
	
	multiply: #multiply a1 by a2, result to v0 (a2 is total so far)
		addi	$a1, $a1, -1 #decrease a1
		
		add	$v0, $v0, $a2 #add a2 to total
		
		
		beq	$a1, 1, factorial # if we have multiplied a1 times, we go to the next multiplication in the factorial
		add $0, $0, $0 #nop
		
		beq	$zero, $zero, multiply # repeat
		add $0, $0, $0 #nop
		
			
zero:
	addi $v0, $zero, 1	
		
		
end: 
	beq $0, $0, end
	add $0, $0, $0
