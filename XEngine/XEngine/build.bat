@echo off

set app_name=xengine.exe
set compiler_flags= -EHsc -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4018 -wd4201 -wd4100 -wd4505 -wd4701 -wd4189 -FC -Z7
set linker_flags= -incremental:no -opt:ref winmm.lib gdi32.lib opengl32.lib user32.lib shell32.lib ../lib/glfw643.lib ../lib/assimp-vc140-mt.lib 
set includes= ..\inc
if not exist build mkdir build
pushd build

REM 64-bit build
del *.pdb > NUL 2> NUL
cl /MD /I %includes% %compiler_flags% ..\src\main.cpp /link %linker_flags% /out:%app_name%

popd
