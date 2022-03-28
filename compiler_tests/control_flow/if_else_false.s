f: 
addiu $29,$29,-8
sw $31,8($29)
sw $30,4($29)
move $30,$29
li $2,0
beq $0,$2,Else1
nop
li $2,11
b EoF0
nop
b EndIfElse2
nop
Else1:
li $2,10
b EoF0
nop
EndIfElse2:
EoF0:
move $29,$30
lw $31,8($29)
lw $30,4($29)
addiu $29,$29,8
j $31
nop
.global f
