#include "mainwindow.h"
extern "C"
{
    #include "mainfunction.h"
}
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //WorkCycle(w.GetLcd());
    return a.exec();
}
