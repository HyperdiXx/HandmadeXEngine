@echo off

set Defines= -DPLATFORM_WINDOWS=1 
set CommonCompilerFlags= -Zi -Od -EHsc -I ../include/
set CommonLinkerFlags= -incremental:no -opt:ref /Debug:fastlink
set PlatformLibs= opengl32.lib kernel32.lib user32.lib gdi32.lib winmm.lib ../freetype.lib
set GameLibs= opengl32.lib kernel32.lib

IF NOT EXIST build2 mkdir build2
pushd build2

REM 64-bit build
del *.pdb > NUL 2> NUL
REM cl %CommonCompilerFlags% win32_main.cpp -Fmhandmade.map -LD /link -incremental:no -opt:ref -PDB:handmade_%RANDOM%.pdb /DLL -EXPORT:GameGetSoundSamples -EXPORT:GameUpdateAndRender

cl %Defines% %CommonCompilerFlags% ../test.cpp /link %PlatformLibs% %CommonLinkerFlags% -PDB:game_%RANDOM%.pdb /out:game2.exe
popd