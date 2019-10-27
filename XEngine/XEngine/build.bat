@echo off

set app_name=xengine.exe
set compiler_flags= -EHsc -Gm- -GR- -EHa- -Od -O2 -Oi -WX -W4 -wd4018 -wd4201 -wd4100 -wd4505 -wd4701 -wd4189 -FC -Z7
set linker_flags= -incremental:no -opt:ref winmm.lib gdi32.lib opengl32.lib user32.lib shell32.lib ..\..\xengine\lib\math.lib ..\..\xengine\lib\glfw643.lib ..\..\xengine\lib\assimp-vc140-mt.lib 
set includes= ..\..\xengine\inc
if not exist ..\out\XEngine mkdir ..\out\XEngine
pushd ..\out\XEngine

REM 64-bit build
del *.pdb > NUL 2> NUL
cl /MD /I %includes% %compiler_flags% ..\..\xengine\src\main.cpp /link %linker_flags% /out:%app_name%

@if ERRORLEVEL == 0 (
   start %app_name%
)

popd



