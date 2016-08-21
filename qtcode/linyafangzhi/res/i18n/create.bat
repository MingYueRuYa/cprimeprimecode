qmake -project ../../src -o linyafangzhi.pro

lupdate linyafangzhi.pro -ts linyafangzhi_en.ts -noobsolete
lupdate linyafangzhi.pro -ts linyafangzhi_zh_CN.ts -noobsolete

lrelease linyafangzhi_en.ts -qm linyafangzhi_en.qm
lrelease linyafangzhi_zh_CN.ts -qm linyafangzhi_zh_CN.qm

pause
