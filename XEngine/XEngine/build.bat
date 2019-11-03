@echo off

set app_name=xengine.exe
set compiler_flags= -nologo -EHsc -Gm- -GR- -EHa- -Od -Oi -W4 -wd4018 -wd4201 -wd4100 -wd4505 -wd4701 -wd4189 -FC -Z7
set linker_flags= -incremental:no -opt:ref winmm.lib gdi32.lib opengl32.lib user32.lib shell32.lib ..\..\xengine\lib\math.lib ..\..\xengine\lib\glfw643.lib
set includes= ..\..\xengine\inc
set includesfiles= ..\..\xengine\src
if not exist ..\out\xengine mkdir ..\out\xengine
pushd ..\out\xengine

REM 64-bit build
del *.pdb > NUL 2> NUL
cl /MD /I %includes% /I %includesfiles% %compiler_flags% ..\..\xengine\src\glad.c ..\..\xengine\src\main.cpp /link %linker_flags% /out:%app_name%

if %ERRORLEVEL% == 0 (
   goto good
) else (   
   goto bad		
)
	
:good
   echo.
   echo Compiled successfully
   echo Starting %app_name%
   start %app_name%
   echo.
   goto end

:bad
   echo.
   echo Error on compile or linking
   echo Error code %ERRORLEVEL%
   echo.
   goto end
:end
   
popd


