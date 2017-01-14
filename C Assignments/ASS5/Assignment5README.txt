To compile this program make sure the makefile, operation.c, operation_functions.c and operation_functions.h are in the same directory.

The command for compilation is:

make all

The command to test various cases is:

make test

Note that if one wishes to test other cases then one can edit the makefile on lines 23-35.

To test failure from too few arguments the command is:

make testfew

To test failure from too many arguments the command is:

make testmany

To clean the directory the commant is:

make clean
