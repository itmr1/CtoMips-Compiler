f: 
addiu $29,$29,-8
sw $30,4($29)
move $30,$29
li $2,0
beq $0,$2EndIf1
li $2,11
b EoF0
EndIf1
li $2,10
b EoF0
EoF0:
lw $30,4($29)
addiu $29,$29,8
j $31
nop