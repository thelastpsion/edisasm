@echo off
call checkvid
REM tsc /zq /m edisasm.pr /smain=edisasm /%jpivid%
tsc /m edisasm.pr /%jpivid%
call makeins
