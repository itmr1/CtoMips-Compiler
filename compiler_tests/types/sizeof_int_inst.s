f: 
addiu $29,$29,-12
sw $31,12($29)
sw $30,8($29)
move $30,$29
lw $4,4($30)
jal sizeof
nop
b EoF0
nop
EoF0:
move $29,$30
lw $31,12($29)
lw $30,8($29)
addiu $29,$29,12
j $31
nop
.global f
