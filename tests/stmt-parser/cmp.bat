rem for /L %%i in (0,1,9) do fc /B "00%%i.out" "00%%i.res" >> log.txt


echo. 2> log.out

for /L %%i in (0,1,9) do fc /B "00%%i.out" "00%%i.res" && echo test 00%%i: Ok >> log.out || echo test 00%%i: No >> log.out
for /L %%i in (10,1,25) do fc /B "0%%i.out" "0%%i.res" && echo test 0%%i: Ok >> log.out || echo test 0%%i: No >> log.out
rem for /L %%i in (100,1,104) do fc /B "%%i.out" "%%i.res" && echo test 0%%i: Ok >> log.out || echo test 0%%i: No >> log.out