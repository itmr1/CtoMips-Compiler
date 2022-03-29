#!/bin/bash
shortcut="local_var/constant_initialiser"
bin/print_canonical -S compiler_tests/${shortcut}.c -o compiler_tests/${shortcut}.s
mips-linux-gnu-gcc -mfp32 -o compiler_tests/${shortcut}.o -c compiler_tests/${shortcut}.s
mips-linux-gnu-gcc -mfp32 -static -o compiler_tests/${shortcut} compiler_tests/${shortcut}.o compiler_tests/${shortcut}_driver.c
qemu-mips compiler_tests/${shortcut}


echo ["$?"]
if [ "$?" -eq "0" ]
then
echo "PASS"
else
echo $?
echo "FAILED"
fi