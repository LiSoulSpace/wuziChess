#include "gamechoose.h"
#include "ui_gamechoose.h"

GameChoose::GameChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameChoose)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

GameChoose::~GameChoose()
{
    delete ui;
}

void GameChoose::on_pushButton_clicked()
{
    wuzi_ui = new wuziChessUI();
    wuzi_ui->show();
}
