		addi $a0,   $zero, 5
		jal fact
		add $a0, $v0, $zero
		addi $v0, $zero, 1
		syscall
		addi $a0, $zero, 10
		addi $v0, $zero, 11
		syscall
		addi $v0, $zero, 10
		syscall

fact:	addi $sp, $sp, -8
		sw $ra, 4($sp)
		sw $a0, 0($sp)
		slti $t0, $a0, 1
		beq $t0, $zero, L1
		addi $v0, $zero, 1
		addi $sp, $sp, 8
		jr $ra
L1:		addi $a0, $a0, -1
		jal fact
		lw $a0, 0($sp)
		lw $ra, 4($sp)
		addi $sp, $sp, 8
		mult $v0, $a0
		mflo $v0
		jr $ra
