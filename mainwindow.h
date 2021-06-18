#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamechoose.h"
#include "doublegamechoose.h"
#include "settingui.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void showWindow();
private slots:
    void on_pushButton_single_clicked();

    void on_pushButton_quit_clicked();

    void on_pushButton_setting_clicked();

    void on_pushButton_double_clicked();

private:
    Ui::MainWindow *ui;
    GameChoose *gameChoose;
    DoubleGameChoose *doubleGameChoose;
};

#endif // MAINWINDOW_H
