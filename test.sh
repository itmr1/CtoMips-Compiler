#!/bin/bash
bin/print_canonical -S compiler_tests/default/test_ADD0.c -o compiler_tests/default/test_ADD0.s
mips-linux-gnu-gcc -mfp32 -o compiler_tests/default/test_ADD0.o -c compiler_tests/default/test_ADD0.s
mips-linux-gnu-gcc -mfp32 -static -o compiler_tests/default/test_ADD0 compiler_tests/default/test_ADD0.o compiler_tests/default/test_ADD0_driver.c
qemu-mips compiler_tests/default/test_ADD0


if [ "$?" -eq "0" ]
then
echo "PASS"
else
echo "FAILED"
fi