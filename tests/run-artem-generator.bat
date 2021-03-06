del *.exe

copy "C:\Users\Yaroslava\Documents\Visual Studio 2010\Projects\compiler\Debug\compiler.exe" "C:\Users\Yaroslava\Documents\Visual Studio 2010\Projects\compiler\compiler\tests"

for /L %%i in (1,1,7) do compiler -g generator/artem/00%%i.in generator/artem/00%%i.out
rem test 008: float number
rem test 009: float number
for /L %%i in (10,1,17) do compiler -g generator/artem/0%%i.in generator/artem/0%%i.out
rem test 018: multi-dimensional arrays
rem test 019: multi-dimensional arrays
for /L %%i in (20,1,26) do compiler -g generator/artem/0%%i.in generator/artem/0%%i.out
rem test 027: lvalue required as left operand of assignment
for /L %%i in (28,1,30) do compiler -g generator/artem/0%%i.in generator/artem/0%%i.out
rem test 031: lvalue required as left operand of assignment
for /L %%i in (32,1,56) do compiler -g generator/artem/0%%i.in generator/artem/0%%i.out
rem test 057: inc
rem test 058: inc
rem test 059: do-while
rem test 060: do-while
rem test 061: inc
for /L %%i in (62,1,71) do compiler -g generator/artem/0%%i.in generator/artem/0%%i.out
rem test 072-078: typedef
rem test 079: inc
rem test 080-085: typedef
rem test 086: void
rem test 087-094: typedef
for /L %%i in (95,1,97) do compiler -g generator/artem/0%%i.in generator/artem/0%%i.out
rem test 098: do-while
rem test 099-104: inc
rem test 105: do-while
rem test 106: typedef
for /L %%i in (107,1,136) do compiler -g generator/artem/%%i.in generator/artem/%%i.out
rem test 137-141: type()
rem test 142: inc
rem test 143: inc
for /L %%i in (144,1,144) do compiler -g generator/artem/%%i.in generator/artem/%%i.out
rem test 145: inc, type()
rem test 146-151: typedef
rem test 152: type()
rem test 153: inc
rem test 154: dec
for /L %%i in (155,1,159) do compiler -g generator/artem/%%i.in generator/artem/%%i.out

cd C:\Users\Yaroslava\Documents\Visual Studio 2010\Projects\compiler\compiler\tests\generator\artem

echo off

echo. 2> *.asm

C:\masm32\bin\ml /coff /c *.asm
for /L %%i in (1,1,7) do C:\masm32\bin\Link /subsystem:console 00%%i.in.obj
for /L %%i in (1,1,7) do 00%%i.in.exe > 00%%i.out

for /L %%i in (10,1,17) do C:\masm32\bin\Link /subsystem:console 0%%i.in.obj
for /L %%i in (10,1,17) do 0%%i.in.exe > 0%%i.out

for /L %%i in (20,1,26) do C:\masm32\bin\Link /subsystem:console 0%%i.in.obj
for /L %%i in (20,1,26) do 0%%i.in.exe > 0%%i.out

for /L %%i in (28,1,30) do C:\masm32\bin\Link /subsystem:console 0%%i.in.obj
for /L %%i in (28,1,30) do 0%%i.in.exe > 0%%i.out

for /L %%i in (32,1,56) do C:\masm32\bin\Link /subsystem:console 0%%i.in.obj
for /L %%i in (32,1,56) do 0%%i.in.exe > 0%%i.out

for /L %%i in (62,1,71) do C:\masm32\bin\Link /subsystem:console 0%%i.in.obj
for /L %%i in (62,1,71) do 0%%i.in.exe > 0%%i.out

for /L %%i in (95,1,97) do C:\masm32\bin\Link /subsystem:console 0%%i.in.obj
for /L %%i in (95,1,97) do 0%%i.in.exe > 0%%i.out

for /L %%i in (107,1,136) do C:\masm32\bin\Link /subsystem:console %%i.in.obj
for /L %%i in (107,1,136) do %%i.in.exe > %%i.out

for /L %%i in (144,1,144) do C:\masm32\bin\Link /subsystem:console %%i.in.obj
for /L %%i in (144,1,144) do %%i.in.exe > %%i.out

for /L %%i in (155,1,159) do C:\masm32\bin\Link /subsystem:console %%i.in.obj
for /L %%i in (155,1,159) do %%i.in.exe > %%i.out

del *.obj
del *.exe

pause