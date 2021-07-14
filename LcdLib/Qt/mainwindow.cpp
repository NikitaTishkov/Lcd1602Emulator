#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "unistd.h"
#define USE_EMULATOR 1

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::MainCycle()
{
    WorkCycle(lcd);
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_startButton_clicked()
{
    this->MainCycle();
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
