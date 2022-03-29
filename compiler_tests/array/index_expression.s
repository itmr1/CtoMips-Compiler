f: 
addiu $29,$29,-48
sw $31,48($29)
sw $30,44($29)
move $30,$29
li $8,8
sw $8,4($30)
b CondCheck3
nop
StartOfLoop2:
lw $2,4($30)
move $9,$2
li $2,8
sub $2,$9,$2
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
li $8,16
slt $8,$10,$8
bne $8,$0,StartOfLoop2
EndOfLoop1:
li $2,0
sw $2,40($30)
li $8,0
sw $8,4($30)
b CondCheck6
nop
StartOfLoop5:
lw $2,40($30)
move $9,$2
lw $2,4($30)
move $10,$2
li $2,0
add $2,$2,$10
sll $2,2
addiu $10,$30,8
addu $10,$10,$2
lw $2,($10)
add $2,$2,$9
sw $2,40($30)
lw $2,4($30)
addi $2,$2,1
sw $2,4($30)
CondCheck6:
lw $8,4($30)
move $10,$8
li $8,8
slt $8,$10,$8
bne $8,$0,StartOfLoop5
EndOfLoop4:
lw $2,40($30)
b EoF0
nop
EoF0:
move $29,$30
lw $31,48($29)
lw $30,44($29)
addiu $29,$29,48
j $31
nop
.global f
