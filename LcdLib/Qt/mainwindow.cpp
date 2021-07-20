#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "unistd.h"
#ifndef __cplusplus

extern "C"
{
#endif
    #include "mainfunction.h"
    void WorkCycle(Lcd *lcd);
#ifndef __cplusplus
}
#endif
#define USE_EMULATOR 1


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::MainCycle()
{
}

MainWindow::~MainWindow()
{
    delete ui;
}

Lcd* MainWindow::GetLcd()
{
    return lcd;
}

void MainWindow::on_startButton_clicked()
{
    WorkCycle(lcd);
}

void MainWindow::on_initButton_clicked()
{
    this->lcd = new Lcd;
    this->lcd->bIsCursorShift = true;
    this->lcd->bIsBlink = false;
    this->lcd->bIsSingleRow = false;
    this->lcd->QSymbols = ui->QDisplay;

    lcd_init(this->lcd);
}
