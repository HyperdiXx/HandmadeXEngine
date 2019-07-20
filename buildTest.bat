@echo off

set enginepath=%cd%
set "projectName=XEngine"

set compilerFlags=
set linkerFlags=

set "buildFlag=Release" 
set "buildBase=%projectName%"

set "platform=Win64"

if "%~1"=="-debug" set "buildFlag=Debug"
if "%~2"=="-x86" set "platform=Win32"

set "buildDir=%buildBase%%BuildFlag%%platform%

IF NOT EXIST "%buildDir%" mkdir "%buildDir%"
pushd "%buildDir%" 

mkdir build
mkdir data
mkdir libs

popd

set "resDir=%enginepath%\%buildDir%\data"
set "dataDir=%enginepath%\HandmadeGlRenderer\data"

echo %resDir%
echo %dataDir%

xcopy "%dataDir%" "%resDir%" /E /Q

