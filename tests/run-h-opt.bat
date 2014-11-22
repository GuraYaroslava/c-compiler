del *.exe
del *.asm

copy "C:\Users\Yaroslava\Documents\Visual Studio 2010\Projects\compiler\Debug\compiler.exe" "C:\Users\Yaroslava\Documents\Visual Studio 2010\Projects\compiler\compiler\tests"

for /L %%i in (0,1,9) do compiler -g--opt h-optimization/00%%i.in h-optimization/00%%i.out
for /L %%i in (10,1,29) do compiler -g--opt h-optimization/0%%i.in h-optimization/0%%i.out

cd C:\Users\Yaroslava\Documents\Visual Studio 2010\Projects\compiler\compiler\tests\h-optimization

echo. 2> *.opt.asm
echo. 2> *.ans

C:\masm32\bin\ml /coff /c *.opt.asm
for /L %%i in (0,1,9) do C:\masm32\bin\Link /subsystem:console 00%%i.in.opt.obj
for /L %%i in (0,1,9) do 00%%i.in.opt.exe > 00%%i.ans

for /L %%i in (10,1,29) do C:\masm32\bin\Link /subsystem:console 0%%i.in.opt.obj
for /L %%i in (10,1,29) do 0%%i.in.opt.exe > 0%%i.ans

del *.obj
del *.exe

pause