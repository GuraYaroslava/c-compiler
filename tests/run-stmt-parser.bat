for /L %%i in (0,1,9) do compiler -d stmt-parser/00%%i.in stmt-parser/00%%i.out
for /L %%i in (10,1,26) do compiler -d stmt-parser/0%%i.in stmt-parser/0%%i.out
