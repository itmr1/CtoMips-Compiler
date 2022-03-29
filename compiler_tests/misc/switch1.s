g: 
addiu $29,$29,-12
sw $31,12($29)
sw $30,8($29)
move $30,$29
sw $4,4($29)
lw $2,4($30)
li $8,1
beq $8,$2,case2
nop
li $8,2
beq $8,$2,case3
nop
case2: 
li $2,10
b EoF0
nop
case3: 
li $2,11
b EoF0
nop
EndSwitch1:
EoF0:
move $29,$30
lw $31,12($29)
lw $30,8($29)
addiu $29,$29,12
j $31
nop
.global g
