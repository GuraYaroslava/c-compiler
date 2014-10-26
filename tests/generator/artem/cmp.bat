echo. 2> log.out

for /L %%i in (1,1,7) do fc /B "00%%i.out" "00%%i.res" && echo test 00%%i: Ok>> log.out|| echo test 00%%i: No>> log.out
echo test 008: float number
echo test 009: float number
for /L %%i in (10,1,17) do fc /B "0%%i.out" "0%%i.res" && echo test 0%%i: Ok>> log.out|| echo test 0%%i: No>> log.out
echo test 018: multi-dimensional arrays
echo test 019: multi-dimensional arrays
for /L %%i in (20,1,26) do fc /B "0%%i.out" "0%%i.res" && echo test 0%%i: Ok>> log.out|| echo test 0%%i: No>> log.out
echo test 027: lvalue required as left operand of assignment
for /L %%i in (28,1,30) do fc /B "0%%i.out" "0%%i.res" && echo test 0%%i: Ok>> log.out|| echo test 0%%i: No>> log.out
echo test 031: lvalue required as left operand of assignment
for /L %%i in (32,1,56) do fc /B "0%%i.out" "0%%i.res" && echo test 0%%i: Ok>> log.out|| echo test 0%%i: No>> log.out
echo test 057: inc
echo test 058: inc
echo test 059: do-while
echo test 060: do-while
echo test 061: INC
for /L %%i in (62,1,71) do fc /B "0%%i.out" "0%%i.res" && echo test 0%%i: Ok>> log.out|| echo test 0%%i: No>> log.out
echo test 072: typedef
echo test 073: typedef
echo test 074: typedef
echo test 075: typedef
echo test 076: typedef
echo test 077: typedef
echo test 078: typedef
echo test 079: inc
echo test 080: typedef
echo test 081: typedef
echo test 082: typedef
echo test 083: typedef
echo test 084: typedef
echo test 085: typedef
echo test 086: void
echo test 087: typedef
echo test 088: typedef
echo test 089: typedef
echo test 090: typedef
echo test 091: typedef
echo test 092: typedef
echo test 093: typedef
echo test 094: typedef
for /L %%i in (95,1,97) do fc /B "0%%i.out" "0%%i.res" && echo test 0%%i: Ok>> log.out|| echo test 0%%i: No>> log.out
echo test 098: do-while
echo test 099: inc
echo test 100: inc
echo test 101: inc
echo test 102: inc
echo test 103: inc
echo test 104: inc
echo test 105: do-while
echo test 106: typedef
for /L %%i in (107,1,136) do fc /B "%%i.out" "%%i.res" && echo test %%i: Ok>> log.out|| echo test %%i: No>> log.out
echo test 137-141: type()
echo test 142: inc
echo test 143: inc
for /L %%i in (144,1,144) do fc /B "%%i.out" "%%i.res" && echo test %%i: Ok>> log.out|| echo test %%i: No>> log.out
echo test 145: inc, type()
echo test 146-151: typedef
echo test 152: type()
echo test 153: inc
echo test 154: dec
for /L %%i in (155,1,159) do fc /B "%%i.out" "%%i.res" && echo test %%i: Ok>> log.out|| echo test %%i: No>> log.out