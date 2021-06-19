#include "wuzichessui_right.h"
#include "ui_wuzichessui_right.h"

wuziChessUI_right::wuziChessUI_right(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wuziChessUI_right)
{
    ui->setupUi(this);
}

wuziChessUI_right::~wuziChessUI_right()
{
    delete ui;
}

void wuziChessUI_right::setLabel(QString s)
{
    QString t = "当前棋子 : ";
    t = t+s;
    this->ui->label->setText(t);
}

void wuziChessUI_right::setTextEditAppend(QString s)
{
    this->ui->textEdit->append(s);
}

void wuziChessUI_right::setLabel2(QString s)
{
    this->ui->label_2->setText(s);
}

