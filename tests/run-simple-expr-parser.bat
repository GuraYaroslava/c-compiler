for /L %%i in (0,1,9) do compiler -sp simple-expr-parser/00%%i.in simple-expr-parser/00%%i.out
for /L %%i in (10,1,63) do compiler -sp simple-expr-parser/0%%i.in simple-expr-parser/0%%i.out

PING -n 5 -w 1000 127.0.0.1 > nul