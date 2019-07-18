@echo off

set CompilerFlags=
set LinkerFlags=

set Platform=win64
set BuildFlag="%~1" 
set BuildBase=build
set buildDir=%BuildBase%%BuildFlag%
if "%~2"=="x86" set buildDir=buildWin32

IF NOT EXIST "%buildDir%" mkdir "%buildDir%"
pushd "%buildDir%"" 

mkdir data
mkdir libs

