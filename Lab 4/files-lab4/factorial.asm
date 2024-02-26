.text

addi $a0, 0, 3
addi $a1, $a0, $zero
addi $a2, $a0, $zero
addi $a3, $a0, $zero


beq $a0, $zero, zero
addi $v0, $0, $a0  #v0 is initially n


multiply:

		
			
zero:
	$addi $v0, $zero, 1	
		
		
end: 
	beq $0, $0, end
	add $0, $0, $0