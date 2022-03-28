f: 
addiu $29,$29,-40
sw $31,40($29)
sw $30,36($29)
move $30,$29
li $2,0
sll $2,2
addiu $8,$30,-4
addu $2,$2,$8
li $8,23
sw $8,4($29)
li $2,0
sll $2,2
addiu $8,$30,0
addu $2,$2,$8
lw $2,4($29)
b EoF0
nop
EoF0:
move $29,$30
lw $31,40($29)
lw $30,36($29)
addiu $29,$29,40
j $31
nop
.global f
