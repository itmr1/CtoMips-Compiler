f: 
addiu $29,$29,-20
sw $30,16($29)
move $30,$29
sw $4,4($29)
sw $5,8($29)
lw $2,4($30)
move $8,$2
lw $2,8($30)
or $2,$2,$8
sw $2,12($30)
lw $2,12($30)
b EoF0
EoF0:
lw $30,16($29)
addiu $29,$29,20
j $31
nop
.global f
