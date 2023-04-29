@echo off
tsc /m edisasm.pr /v2 /b
echo Compile done!
echo Press any key to run SDBG using COM1 @ 57600 bps
pause
sdbg -b57600 edisasm.app
