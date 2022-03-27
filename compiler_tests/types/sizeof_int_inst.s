f: 
addiu $29,$29,-12
sw $30,8($29)
move $30,$29
b EoF0
EoF0:
lw $30,8($29)
addiu $29,$29,12
j $31
nop
