f: 
addiu $29,$29,-12
sw $30,8($29)
move $30,$29
li $2,1
sw $2,4($30)
lw $2,4($30)
move $8,$2
lw $2,4($30)
add $2,$2,$8
sw $2,4($30)
lw $2,4($30)
b EoF0
nop
EoF0:
lw $30,8($29)
addiu $29,$29,12
j $31
nop
.global f
