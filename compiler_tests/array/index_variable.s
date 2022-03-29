f: 
addiu $29,$29,-44
sw $31,44($29)
sw $30,40($29)
move $30,$29
li $8,0
sw $8,4($30)
b CondCheck3
nop
StartOfLoop2:
lw $2,4($30)
sll $2,2
addiu $9,$30,8
addu $9,$9,$2
lw $2,4($30)
sw $2,($9)
lw $2,4($30)
addi $2,$2,1
sw $2,4($30)
CondCheck3:
lw $8,4($30)
move $10,$8
li $8,8
slt $8,$10,$8
bne $8,$0,StartOfLoop2
EndOfLoop1:
li $2,4
sll $2,2
addiu $8,$30,8
addu $8,$8,$2
lw $2,($8)
b EoF0
nop
EoF0:
move $29,$30
lw $31,44($29)
lw $30,40($29)
addiu $29,$29,44
j $31
nop
.global f
