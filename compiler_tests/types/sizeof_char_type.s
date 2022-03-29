f: 
addiu $29,$29,-8
sw $31,8($29)
sw $30,4($29)
move $30,$29
lw $4,0($30)
jal sizeof
nop
b EoF0
nop
EoF0:
move $29,$30
lw $31,8($29)
lw $30,4($29)
addiu $29,$29,8
j $31
nop
.global f
