del *.exe

copy "C:\Users\Yaroslava\Documents\Visual Studio 2010\Projects\compiler\Debug\compiler.exe" "C:\Users\Yaroslava\Documents\Visual Studio 2010\Projects\compiler\compiler\tests"

for /L %%i in (0,1,9) do compiler -g generator/00%%i.in generator/00%%i.out
for /L %%i in (10,1,77) do compiler -g generator/0%%i.in generator/0%%i.out

cd C:\Users\Yaroslava\Documents\Visual Studio 2010\Projects\compiler\compiler\tests\generator

echo off


echo. 2> *.asm

C:\masm32\bin\ml /coff /c *.asm
for /L %%i in (0,1,9) do C:\masm32\bin\Link /subsystem:console 00%%i.in.obj
for /L %%i in (0,1,9) do 00%%i.in.exe > 00%%i.out

for /L %%i in (10,1,77) do C:\masm32\bin\Link /subsystem:console 0%%i.in.obj
for /L %%i in (10,1,77) do 0%%i.in.exe > 0%%i.out

del *.obj
del *.exe

pause