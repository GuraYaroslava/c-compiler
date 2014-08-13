rem for /L %%i in (0,1,9) do fc /B "00%%i.out" "00%%i.res" >> log.txt


echo. 2> log.out

for /L %%i in (0,1,9) do fc /B "00%%i.out" "00%%i.res" && echo test 00%%i: Ok >> log.out || echo test 00%%i: No >> log.out
for /L %%i in (10,1,62) do fc /B "0%%i.out" "0%%i.res" && echo test 0%%i: Ok >> log.out || echo test 0%%i: No >> log.out

PING -n 5 -w 1000 127.0.0.1 > nul