echo. 2> log.out

for /L %%i in (0,1,9) do fc /B "00%%i.res" "00%%i.ans" && echo test 00%%i: Ok>>log.out||echo test 00%%i: No>>log.out
for /L %%i in (10,1,29) do fc /B "0%%i.res" "0%%i.ans" && echo test 0%%i: Ok>>log.out||echo test 0%%i: No>>log.out
