@echo off

set enginepath=E:\HandmadeXEngine\

set compilerFlags=
set linkerFlags=

set buildFlag=%~1 
set buildBase=build

if "%~2"==-x86 set platform=win32
if "%~2"==-x64 set platform=win64

set buildDir=%buildBase%%BuildFlag%

IF NOT EXIST "%buildDir%" mkdir "%buildDir%"
pushd "%buildDir%"" 

mkdir data
mkdir libs

popd

set dataDir=%enginepath%HandmadeGlRenderer\data
set resDir=%enginepath%%buildDir%\data

echo %enginepath%%buildDir%
echo %dataDir%

xcopy "%dataDir%" "%resDir%" /E /Q

