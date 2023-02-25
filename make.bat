@echo off
call checkvid
tsc /zq /m edisasm.pr /smain=edisasm /%jpivid%
copy edisasm.img edisasm.app > NUL:
del edisasm.img
del edisasm.exe
call makeins
