f: 
addiu $29,$29,-8
sw $31,8($29)
sw $30,4($29)
move $30,$29
li $8,0
beq $0,$8,LoopEnd2
nop
LoopStart1:
li $8,0
bne $0,$8,LoopStart1
nop
LoopEnd2:
li $2,19937
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
