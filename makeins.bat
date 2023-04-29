@echo off
echo *** CREATING INSTALL TREE ***
rem 
rem Create directory structure of the Install tree
rem
deltree /Y INSTALL > NUL
mkdir INSTALL > NUL
cd INSTALL > NUL
mkdir APP > NUL
rem Copy EDisAsm
copy ..\EDISASM.APP APP\ > NUL
rem 
rem And finish back in the root directory
cd ..
echo *** All Done ***
