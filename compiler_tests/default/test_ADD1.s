f: 
addiu $29,$29,-12
sw $30,8($29)
move $30,$29
sw $4,4($29)
lw $2,4($30)
move $8, $2
li $2,10
add $2, $2, $8
b EoF0
EoF0:
lw $30,8($29)
addiu $29,$29,12
j $31
nop
