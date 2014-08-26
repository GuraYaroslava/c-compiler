for /L %%i in (0,1,9) do compiler -p expr-parser/00%%i.in expr-parser/00%%i.out
for /L %%i in (10,1,63) do compiler -p expr-parser/0%%i.in expr-parser/0%%i.out