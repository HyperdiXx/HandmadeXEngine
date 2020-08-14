@echo off

IF NOT EXIST build\game mkdir build\game
pushd build\game

REM 64-bit build
del *.pdb > NUL 2> NUL
cl %CommonCompilerFlags% xengine\xengine\src\handmade.cpp -Fmhandmade.map -LD /link -incremental:no -opt:ref -PDB:handmade_%RANDOM%.pdb /DLL -EXPORT:GameGetSoundSamples -EXPORT:GameUpdateAndRender
cl %CommonCompilerFlags% xengine\xengine\src\win32_startfile.cpp /link %CommonLinkerFlags%

popd