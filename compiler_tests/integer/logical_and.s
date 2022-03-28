f: 
addiu $29,$29,-16
sw $31,16($29)
sw $30,12($29)
move $30,$29
sw $4,4($29)
sw $5,8($29)
lw $2,4($30)
beq $2,$0,A1
nop
lw $2,8($30)
beq $2,$0,A1
nop
li $2,1
b A2
nop
A1:
move $2,$0
A2:
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
