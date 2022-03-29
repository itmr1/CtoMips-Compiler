f: 
addiu $29,$29,-16
sw $31,16($29)
sw $30,12($29)
move $30,$29
li $8,10
sw $8,4($29)
lw $8,4($30)
move $9,$8
li $8,20
add $8,$8,$9
sw $8,8($29)
lw $2,8($30)
b EoF0
nop
EoF0:
move $29,$30
lw $31,16($29)
lw $30,12($29)
addiu $29,$29,16
j $31
nop
.global f
