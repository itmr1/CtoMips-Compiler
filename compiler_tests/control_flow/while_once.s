f: 
addiu $29,$29,-12
sw $31,12($29)
sw $30,8($29)
move $30,$29
li $2,1
sw $2,4($30)
lw $8,4($30)
beq $0,$8,LoopEnd2
nop
LoopStart1:
li $2,0
sw $2,4($30)
lw $8,4($30)
bne $0,$8,LoopStart1
nop
LoopEnd2:
li $2,19937
b EoF0
nop
EoF0:
move $29,$30
lw $31,12($29)
lw $30,8($29)
addiu $29,$29,12
j $31
nop
.global f
