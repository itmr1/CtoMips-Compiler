fib: 
addiu $29,$29,-12
sw $30,8($29)
move $30,$29
sw $4,4($29)
lw $2,4($30)
move $8,$2
li $2,0
slt $2,$2,$8
xori $2,$2,1
beq $0,$2EndIf1
li $2,0
b EoF0
EndIf1
lw $2,4($30)
move $8,$2
li $2,1
xor $2,$2,$8
slti $2,$21
beq $0,$2EndIf2
li $2,1
b EoF0
EndIf2
move $8,$2
add $2,$2,$8
b EoF0
EoF0:
lw $30,8($29)
addiu $29,$29,12
j $31
nop
