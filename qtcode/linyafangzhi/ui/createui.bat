uic ui_mainwindow.ui -o ui_mainwindow.h

uic ui_searchdockwidget.ui -o ui_searchdockwidget.h



copy ui_mainwindow.h ..\src\ui_mainwindow.h
copy ui_searchdockwidget.h ..\src\ui_searchdockwidget.h

pause
