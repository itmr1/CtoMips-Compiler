#!/bin/bash
wrong=0
correct=0

for driver in compiler_tests/*/*_driver.c ; do
    base=${driver: : -9}
    pair="${base}.c"
    echo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    bin/print_canonical -S ${pair} -o ${base}.s
    mips-linux-gnu-gcc -mfp32 -o ${base}.o -c ${base}.s
    mips-linux-gnu-gcc -mfp32 -static -o ${base} ${base}.o ${driver}
    qemu-mips ${base}
    if [ "$?" -eq "0" ]
    then
    echo "PASS ${base}"
    correct=$(( correct + 1 ))
    else
    echo "FAILED ${base}"
    wrong=$(( wrong + 1 ))
    fi
    echo %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    printf "\n"

done

 echo "Correct: "${correct}
 echo "Incorrect: "${wrong}




