#!/bin/bash
rm compiler_tests/*/*.o
rm compiler_tests/*/*.s
TESTFOLDERS=( "compiler_tests/*/*" )
file=( $TESTFOLDERS )
wrong=0
correct=0

for ((i=0; i<"${#file[@]}"; i=i+2)) do
    echo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    #echo ${file[i]}
    #echo ${file[i+1]}
    outputone=${file[i]%.*} 
    bin/print_canonical -S ${file[i]} -o ${outputone}.s
    mips-linux-gnu-gcc -mfp32 -o ${outputone}.o -c ${outputone}.s
    mips-linux-gnu-gcc -mfp32 -static -o ${outputone} ${outputone}.o ${file[i+1]}
    qemu-mips ${outputone}
    if [ "$?" -eq "0" ]
    then
    echo "PASS"
    correct=$(( correct + 1 ))
    else
    echo "FAILED"
    wrong=$(( wrong + 1 ))
    fi
    echo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    printf "\n"
    
done
 echo "SIUUUUUUUUUUUUUUUUUU: "${correct}
 echo "Incorrect: "${wrong}




