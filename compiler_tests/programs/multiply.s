multiply: 
addiu $29,$29,-20
sw $31,20($29)
sw $30,16($29)
move $30,$29
sw $4,4($29)
sw $5,8($29)
li $8,0
sw $8,12($29)
lw $2,4($30)
move $8,$2
li $2,0
slt $2,$8,$2
beq $0,$2,EndIf1
nop
lw $4,4($30)
sub $4,$0,$4
lw $5,8($30)
jal multiply
nop
sub $2,$0,$2
b EoF0
nop
EndIf1:
lw $8,4($30)
move $9,$8
li $8,0
slt $8,$8,$9
beq $0,$8,LoopEnd3
nop
LoopStart2:
lw $9,8($30)
add $2,$2,$9
sw $2,12($30)
lw $2,4($30)
subi $2,$2,1
sw $2,4($30)
lw $8,4($30)
move $9,$8
li $8,0
slt $8,$8,$9
bne $0,$8,LoopStart2
nop
LoopEnd3:
lw $2,12($30)
b EoF0
nop
EoF0:
move $29,$30
lw $31,20($29)
lw $30,16($29)
addiu $29,$29,20
j $31
nop
.global multiply
