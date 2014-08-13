for /L %%i in (0,1,9) do compiler -sp simple-parser/00%%i.in simple-parser/00%%i.out
for /L %%i in (10,1,62) do compiler -sp simple-parser/0%%i.in simple-parser/0%%i.out