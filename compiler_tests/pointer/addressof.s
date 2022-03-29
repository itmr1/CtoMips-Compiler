f: 
addiu $29,$29,-16
sw $31,16($29)
sw $30,12($29)
move $30,$29
addiu $8,$30,4
sw $8,8($29)
li $2,13
b EoF0
nop
EoF0:
move $29,$30
lw $31,16($29)
lw $30,12($29)
addiu $29,$29,16
j $31
nop
.global f
