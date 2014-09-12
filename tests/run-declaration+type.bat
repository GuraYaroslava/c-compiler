for /L %%i in (0,1,9) do compiler -d "declaration+type/00%%i.in" "declaration+type/00%%i.out"
for /L %%i in (10,1,80) do compiler -d "declaration+type/0%%i.in" "declaration+type/0%%i.out"
