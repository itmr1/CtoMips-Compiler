f: 
addiu $29,$29,-12
sw $31,12($29)
sw $30,8($29)
move $30,$29
li $2,20
sw $2,4($30)
lw $8,4($30)
move $9,$8
li $8,10
slt $8,$8,$9
beq $0,$8,LoopEnd2
nop
LoopStart1:
lw $2,4($30)
move $9,$2
li $2,1
sub $2,$9,$2
sw $2,4($30)
lw $8,4($30)
move $9,$8
li $8,10
slt $8,$8,$9
bne $0,$8,LoopStart1
nop
LoopEnd2:
lw $2,4($30)
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
