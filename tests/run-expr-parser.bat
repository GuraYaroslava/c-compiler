for /L %%i in (0,1,9) do compiler -p expr-parser/00%%i.in expr-parser/00%%i.out
for /L %%i in (10,1,99) do compiler -p expr-parser/0%%i.in expr-parser/0%%i.out
for /L %%i in (100,1,104) do compiler -p expr-parser/%%i.in expr-parser/%%i.out