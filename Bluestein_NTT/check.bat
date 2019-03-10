@echo off
a=1
:loop
echo %a%
set /a a=a+1
gen.exe
a.exe
a1.exe
fc a.out a1.out
if not errorlevel 1 goto loop