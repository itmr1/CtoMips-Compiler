f: 
addiu $29,$29,-12
sw $31,12($29)
sw $30,8($29)
move $30,$29
li $8,0
sw $8,4($30)
b CondCheck3
nop
StartOfLoop2:
li $2,1
b EoF0
nop
li $2,1
move $10,$2
lw $2,4($30)
add $2,$2,$10
sw $2,4($30)
CondCheck3:
lw $8,4($30)
move $10,$8
li $8,0
slt $8,$10,$8
bne $8,$0,StartOfLoop2
EndOfLoop1:
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
