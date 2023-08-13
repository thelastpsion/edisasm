@echo off
call checkvid
REM tsc /zq /m edisasm.pr /smain=edisasm /%jpivid%
tscx /m edisasm.pr /%jpivid%
call makeins
