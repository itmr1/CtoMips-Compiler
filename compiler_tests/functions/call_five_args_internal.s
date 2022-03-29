g: 
addiu $29,$29,-28
sw $31,28($29)
sw $30,24($29)
move $30,$29
sw $4,4($29)
sw $5,8($29)
sw $6,12($29)
sw $7,16($29)
sw $8,20($29)
lw $2,20($30)
move $8,$2
lw $2,16($30)
move $9,$2
lw $2,12($30)
move $10,$2
lw $2,8($30)
move $11,$2
lw $2,4($30)
add $2,$2,$11
add $2,$2,$10
add $2,$2,$9
add $2,$2,$8
b EoF0
nop
EoF0:
move $29,$30
lw $31,28($29)
lw $30,24($29)
addiu $29,$29,28
j $31
nop
.global g
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
b EoF1
nop
EoF1:
move $29,$30
lw $31,8($29)
lw $30,4($29)
addiu $29,$29,8
j $31
nop
.global f
