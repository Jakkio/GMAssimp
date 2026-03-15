It's a port for use assimp with GameMaker.
It uses 2 dll's, one is the real assimp, and the other is a bridge that allows to read values one at a time.

All the structs are meant to be the same 1:1, so you can use the original documentation (and tutorials!) for almost everything.

If you want to use the extension (dll) directly, the functions are basically the same as assimp and you can use the original documentation. All of them have the "ASSIMP_" prefix, and have a different naming convention, for hystorical reasons of this lib.
The only differences are that it works by using the "Bind" functions to make a specific struct the selected one, and then it will be used as context for the other functions.
Also every function that returns vectors/matrices/arrays is decomposed for specific values, one at a time.

DLL Assimp version: 6.0.2

I don't know how to use cmake or cleanup the visual studio project, so in "dll" folder you just find the source code of the bridge dll between GM and assimp.
If you want to compile it yourself: good luck. It should be nothing crazy, just configure the linker. If you want to help me with that, it is very appreciated.

In theory the code is not OS/target dependent so it should be compatible with every target that is supported by assimp, but I will release only windows binaries.
