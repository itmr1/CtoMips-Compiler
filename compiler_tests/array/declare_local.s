f: 
addiu $29,$29,-44
sw $31,44($29)
sw $30,40($29)
move $30,$29
li $2,13
sw $2,4($30)
lw $2,4($30)
b EoF0
nop
EoF0:
move $29,$30
lw $31,44($29)
lw $30,40($29)
addiu $29,$29,44
j $31
nop
.global f
