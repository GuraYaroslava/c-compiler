for /L %%i in (0,1,9) do compiler -s scanner/00%%i.in scanner/00%%i.out
for /L %%i in (10,1,42) do compiler -s scanner/0%%i.in scanner/0%%i.out
