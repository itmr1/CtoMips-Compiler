g: 
addiu $29,$29,-12
sw $30,8($29)
move $30,$29
sw $4,4($29)
lw $2,4($30)
b EoF0
nop
EoF0:
lw $30,8($29)
addiu $29,$29,12
j $31
nop
.global g
f: 
addiu $29,$29,-8
sw $30,4($29)
move $30,$29
jal g
nop
b EoF1
nop
EoF1:
lw $30,4($29)
addiu $29,$29,8
j $31
nop
.global f
