f: 
addiu $29,$29,-12
sw $30,8($29)
move $30,$29
li $8,12345
sw 8,4($29)
lw $2,4($30)
b EoF0
EoF0:
lw $30,8($29)
addiu $29,$29,12
j $31
nop