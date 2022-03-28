f: 
addiu $29,$29,-16
sw $30,12($29)
move $30,$29
li $2,13
sw $2,4($30)
lw $2,4($30)
b EoF0
nop
EoF0:
lw $30,12($29)
addiu $29,$29,16
j $31
nop
.global f
