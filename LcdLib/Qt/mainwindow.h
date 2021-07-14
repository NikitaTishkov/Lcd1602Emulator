#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "LcdLib/Inc/lcd.h"
#include "LcdLib/Inc/QCell.h"
#include "LcdLib/Inc/mainfunction.h"

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
    ~MainWindow();

private slots:
    void on_startButton_clicked();

    void on_initButton_clicked();

private:
    Ui::MainWindow *ui;
    Lcd *lcd;
};
#endif // MAINWINDOW_H
