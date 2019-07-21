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

set "resDir=%enginepath%\%buildDir%\data"
set "dataDir=%enginepath%\%projectName%\data"

rem xcopy "%dataDir%" "%resDir%" /E /Q

echo %enginepath%\%projectName%\XEngine.sln
echo %enginepath%\%projectName%\%projectName%\XEngine.vcxproj

pushd build

devenv %enginepath%\%projectName%\XEngine.sln /Project %enginepath%\%projectName%\%projectName%\XEngine.vcxproj /Build "Debug|x64" 
devenv %enginepath%\%projectName%\XEngine.sln /Project %enginepath%\%projectName%\Launcher\Launcher.csproj /Rebuild "Debug|x64" 

popd
