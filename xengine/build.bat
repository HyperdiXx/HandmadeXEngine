@echo off

set Defines= -DPLATFORM_WINDOWS=1 -nologo
set CommonCompilerFlags= -Zi -Od -EHsc -I ../src/ -I ../src/xengine/external/
set CommonLinkerFlags= -incremental:no -opt:ref /Debug:fastlink
set PlatformLibs= opengl32.lib kernel32.lib user32.lib gdi32.lib winmm.lib ../src/xengine/libs/freetype.lib ../src/xengine/libs/assimp-vc141-mtd.lib
set GameLibs= opengl32.lib kernel32.lib ../src/xengine/libs/assimp-vc141-mtd.lib
set GameCompilerFlags= -Zi -FC -EHsc -I ../src/ -I ../src/xengine/external/
IF NOT EXIST build mkdir build
pushd build

REM 64-bit build
del *.pdb > NUL 2> NUL
REM cl %CommonCompilerFlags% win32_main.cpp -Fmhandmade.map -LD /link -incremental:no -opt:ref -PDB:handmade_%RANDOM%.pdb /DLL -EXPORT:GameGetSoundSamples -EXPORT:GameUpdateAndRender

cl %Defines% %CommonCompilerFlags% ../src/xengine/win32/win32_main.cpp /link %PlatformLibs% %CommonLinkerFlags% -PDB:handmade_%RANDOM%.pdb /out:game.exe
cl %Defines% %GameCompilerFlags% ../src/game/application.cpp /LD /link %GameLibs% -opt:ref -incremental:no /Debug:fastlink /out:application.dll
popd