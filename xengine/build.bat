@echo off

set CommonCompilerFlags = -nologo -Zi -Od /I src/
set CommonLinkerFlags = -incremental:no -opt:ref /Debug:fastlink
set Libs = opengl32.lib kernel32.lib user32.lib gdi32.lib winmm.lib

IF NOT EXIST build mkdir build
pushd build

REM 64-bit build
del *.pdb > NUL 2> NUL
REM cl %CommonCompilerFlags% win32_main.cpp -Fmhandmade.map -LD /link -incremental:no -opt:ref -PDB:handmade_%RANDOM%.pdb /DLL -EXPORT:GameGetSoundSamples -EXPORT:GameUpdateAndRender

cl /Zi /EHsc -DPLATFORM_WINDOWS=1 /I ../src/ ../src/xengine/win32/win32_main.cpp /link opengl32.lib kernel32.lib user32.lib gdi32.lib winmm.lib %CommonLinkerFlags% -PDB:handmade_%RANDOM%.pdb /out:game.exe

popd