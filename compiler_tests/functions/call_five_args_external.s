f: 
addiu $29,$29,-8
sw $31,8($29)
sw $30,4($29)
move $30,$29
li $4,1
li $5,2
li $6,3
li $7,4
li $8,5
jal g
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
