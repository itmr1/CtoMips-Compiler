fib: 
addiu $29,$29,-12
sw $30,8($29)
move $30,$29
sw $4,4($29)
beq $0,$2EndIf1
li $2,0
b EoF0
EndIf1
beq $0,$2EndIf2
li $2,1
b EoF0
EndIf2
move $8, $2
add $2, $2, $8
b EoF0
EoF0:
lw $30,8($29)
addiu $29,$29,12
j $31
nop
