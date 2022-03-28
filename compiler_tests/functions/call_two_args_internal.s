g: 
addiu $29,$29,-16
sw $31,16($29)
sw $30,12($29)
move $30,$29
sw $4,4($29)
sw $5,8($29)
lw $2,4($30)
move $8,$2
lw $2,8($30)
add $2,$2,$8
b EoF0
nop
EoF0:
move $29,$30
lw $31,16($29)
lw $30,12($29)
addiu $29,$29,16
j $31
nop
.global g
f: 
addiu $29,$29,-8
sw $31,8($29)
sw $30,4($29)
move $30,$29
li $4,10
li $5,20
jal g
nop
b EoF1
nop
EoF1:
move $29,$30
lw $31,8($29)
lw $30,4($29)
addiu $29,$29,8
j $31
nop
.global f
