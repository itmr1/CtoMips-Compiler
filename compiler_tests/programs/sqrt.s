bsqrt: 
addiu $29,$29,-28
sw $31,28($29)
sw $30,24($29)
move $30,$29
sw $4,4($29)
sw $5,8($29)
sw $6,12($29)
lw $8,4($30)
move $9,$8
li $8,1
add $8,$8,$9
move $9,$8
lw $8,8($30)
slt $8,$9,$8
beq $0,$8,LoopEnd2
nop
LoopStart1:
lw $9,4($30)
move $10,$9
lw $9,8($30)
add $9,$9,$10
move $10,$9
li $9,1
sra $9,$10,$9
sw $9,16($29)
lw $9,16($30)
move $10,$9
lw $9,16($30)
mult $9,$10
mflo $9
sw $9,20($29)
lw $2,20($30)
move $9,$2
lw $2,12($30)
slt $2,$2,$9
xori $2,$2,1
beq $0,$2,Else3
nop
lw $2,16($30)
sw $2,4($30)
b EndIfElse4
nop
Else3:
lw $2,16($30)
sw $2,8($30)
EndIfElse4:
lw $8,4($30)
move $9,$8
li $8,1
add $8,$8,$9
move $9,$8
lw $8,8($30)
slt $8,$9,$8
bne $0,$8,LoopStart1
nop
LoopEnd2:
lw $2,4($30)
move $8,$2
lw $2,4($30)
mult $2,$8
mflo $2
move $8,$2
lw $2,12($30)
slt $2,$8,$2
beq $0,$2,Else5
nop
lw $2,8($30)
b EoF0
nop
b EndIfElse6
nop
Else5:
lw $2,4($30)
b EoF0
nop
EndIfElse6:
EoF0:
move $29,$30
lw $31,28($29)
lw $30,24($29)
addiu $29,$29,28
j $31
nop
.global bsqrt
