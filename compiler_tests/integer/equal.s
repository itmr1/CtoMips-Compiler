f: 
addiu $29,$29,-16
sw $30,12($29)
move $30,$29
sw $4,4($29)
sw $5,8($29)
lw $2,4($30)
move $8,$2
lw $2,8($30)
xor $2,$2,$8
slti $2,$21
b EoF0
EoF0:
lw $30,12($29)
addiu $29,$29,16
j $31
nop
