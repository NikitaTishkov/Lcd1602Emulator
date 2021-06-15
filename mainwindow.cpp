#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "LcdLib/Inc/lcd.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::WorkCycle()
{
    /* User code 0 BEGIN*/
    Lcd my_lcd
    {
        .bIsCursorShift = true,
        .bIsBlink = false,
        .bIsSingleRow = false,
        .QSymbols = ui->QDisplay
    };

    //lcd_init(&my_lcd);
    /* User code 0 END*/
    while(1)
    {
        /* User code 1 BEGIN */

        /* User code 1 END */
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

