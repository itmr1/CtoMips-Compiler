f: 
addiu $29,$29,-8
sw $30,4($29)
move $30,$29
li $2,1
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
lw $30,4($29)
addiu $29,$29,8
j $31
nop
.global f
