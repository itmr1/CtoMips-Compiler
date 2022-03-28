f: 
addiu $29,$29,-8
sw $30,4($29)
move $30,$29
jal sizeof
nop
b EoF0
nop
EoF0:
lw $30,4($29)
addiu $29,$29,8
j $31
nop
.global f
