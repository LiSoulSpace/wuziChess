#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(330, 440);
}

MainWindow::~MainWindow()
{
    delete ui;
    setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::showWindow()
{
    this->show();
}


void MainWindow::on_pushButton_single_clicked()
{
    gameChoose = new GameChoose();
    gameChoose->show();
}

void MainWindow::on_pushButton_quit_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_setting_clicked()
{

}

void MainWindow::on_pushButton_double_clicked()
{
    doubleGameChoose= new DoubleGameChoose();
    connect(doubleGameChoose, &DoubleGameChoose::showMainWindow, this, &MainWindow::showWindow);
    doubleGameChoose->show();
    this->hide();
}
