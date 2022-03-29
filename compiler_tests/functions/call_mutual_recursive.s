r1: 
addiu $29,$29,-12
sw $31,12($29)
sw $30,8($29)
move $30,$29
sw $4,4($29)
lw $2,4($30)
move $8,$2
li $2,0
xor $2,$2,$8
sltiu $2,$2,1
beq $0,$2,Else1
nop
li $2,1
b EoF0
nop
b EndIfElse2
nop
Else1:
li $4,1
move $9,$4
lw $4,4($30)
sub $4,$4,$9
jal r2
nop
move $8,$2
li $4,1
move $9,$4
lw $4,4($30)
sub $4,$4,$9
jal r2
nop
add $2,$2,$8
b EoF0
nop
EndIfElse2:
EoF0:
move $29,$30
lw $31,12($29)
lw $30,8($29)
addiu $29,$29,12
j $31
nop
.global r1
