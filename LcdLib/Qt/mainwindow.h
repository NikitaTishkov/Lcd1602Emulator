#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "lcd.h"
#include "QCell.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void MainCycle();
    QCell **m_aCells;
    Lcd* GetLcd();
    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void on_initButton_clicked();

private:
    Ui::MainWindow *ui;
    Lcd *lcd;
};
#endif // MAINWINDOW_H
