@echo off

set mode=%1
set app_name=xengine.exe
set compiler_flags_debug= -Od -Z7
set compiler_flags_release= -O2 
set compiler_flags= -EHsc -Gm- -GR- -EHa- -Oi -W4 -wd4018 -wd4201 -wd4100 -wd4505 -wd4701 -wd4189 -FC -D_CRT_SECURE_NO_WARNINGS
set linker_flags= -incremental:no -opt:ref winmm.lib gdi32.lib opengl32.lib user32.lib shell32.lib ..\..\xengine\lib\math.lib
set includes= ..\..\xengine\inc
set includesfiles= ..\..\xengine\src
if not exist ..\out\xengine mkdir ..\out\xengine
pushd ..\out\xengine

REM 64-bit build
del *.pdb > NUL  2> NUL

if "%mode%" == "" (
    goto mode
)

if "%mode%" == "debug" (
    cl /MD /I %includes% /I %includesfiles% %compiler_flags_debug% %compiler_flags% ..\..\xengine\src\glad.c ..\..\xengine\src\main.cpp /link %linker_flags% /out:%app_name%
)

if "%mode%" == "release" (
    cl /MD /I %includes% /I %includesfiles% %compiler_flags_release% %compiler_flags% ..\..\xengine\src\glad.c ..\..\xengine\src\main.cpp /link %linker_flags% /out:%app_name%
)

if %ERRORLEVEL% == 0 (
   goto good
) else (   
   goto bad		
)
	
:good
   echo.
   echo Config %mode%
   echo Compiled successfully
   echo Starting %app_name%
   start %app_name%
   echo.
   goto end

:bad
   echo.
   echo Error: Compile or Linking
   echo Error: Code %ERRORLEVEL%
   echo.
   goto end

:mode
   echo.
   echo Error: No build mode!
   echo.
   goto end

:end	

popd


