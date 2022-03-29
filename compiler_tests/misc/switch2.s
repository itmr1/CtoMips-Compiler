g: 
addiu $29,$29,-16
sw $31,16($29)
sw $30,12($29)
move $30,$29
sw $4,4($29)
li $2,0
sw $2,8($30)
lw $2,4($30)
li $8,0
beq $8,$2,case2
nop
b EndSwitch1
nop
li $8,2
beq $8,$2,case3
nop
li $8,1
beq $8,$2,case4
nop
b EndSwitch1
nop
case2: 
li $2,1
sw $2,8($30)
case3: 
li $2,2
sw $2,8($30)
case4: 
li $2,1
move $8,$2
lw $2,8($30)
add $2,$2,$8
sw $2,8($30)
case5: 
li $2,1
move $8,$2
lw $2,4($30)
add $2,$2,$8
sw $2,8($30)
EndSwitch1:
lw $2,8($30)
b EoF0
nop
EoF0:
move $29,$30
lw $31,16($29)
lw $30,12($29)
addiu $29,$29,16
j $31
nop
.global g
