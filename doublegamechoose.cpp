#include "doublegamechoose.h"
#include "ui_doublegamechoose.h"
#include <ctime>

DoubleGameChoose::DoubleGameChoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoubleGameChoose)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui->lineEdit_ip->setText("106.14.13.158");
    ui->lineEdit_port->setText("4568");
    ui->pushButton_quitconnect->setEnabled(false);
    ui->textEdit->setReadOnly(true);
    ui->pushButton_refresh->setEnabled(false);
    ui->pushButton_start->setEnabled(false);
    people_online = new QStringList();
    ui->lineEdit_name->setText("soulspace");
    ui->radioButton_random->setChecked(true);
}

DoubleGameChoose::~DoubleGameChoose()
{
    delete ui;
}

void DoubleGameChoose::doubleUICloseSlot()
{
    ui->textEdit_status->append("UI Closed!");
}

void DoubleGameChoose::insertMessage(QString s)
{
    ui->textEdit->append(s);
}

void DoubleGameChoose::closeEvent(QCloseEvent *event)
{
    emit showMainWindow();
}

void DoubleGameChoose::analysisMessage(QString s)
{
    qDebug()<<s;
    QStringList qsl = s.split(" ");
    QString s1 = qsl.at(0);
    QString myName = ui->lineEdit_name->text();
    if(!QString::compare(s1, "chat")){
        if(!QString::compare(qsl.at(2), "all")||!QString::compare(qsl.at(2), myName)){
            QString s = qsl.at(1)+" : ";
            for (int i = 3;i<qsl.size();i++) {
                s= s + qsl.at(i) + ' ';
            }
            s = s.mid(0, s.size()-2);
            insertMessage(s);
        }
    } else if (!QString::compare(s1, "gameRequest")){
        if(!QString::compare(qsl.at(2), myName)){
            if(!ui->checkBox->isChecked()) {
                socketTcp->send_Message("gameNoReady "+myName+" "+qsl.at(1));
                this->ui->textEdit_status->append("Receive request from "+qsl.at(1)+", but you are not ready.");
            }else{
                ChessStatus cs = NONE;
                QString temp;
                if(!QString::compare(qsl.at(3), "BLACK")){
                    cs = WHITE;
                    temp = "WHITE";
                }
                else if(!QString::compare(qsl.at(3), "WHITE")){
                    cs=BLACK;
                    temp="BLACK";
                }
                double_chess_ui  = new doubleWuziChessUI(nullptr, true, cs);
                connect(this, &DoubleGameChoose::sendCommendToUI, double_chess_ui, &doubleWuziChessUI::get_commend);
                connect(double_chess_ui, &doubleWuziChessUI::sendDownChessMessageSignal, this, &DoubleGameChoose::downChessCSlot);
                double_chess_ui->show();
                bool isForbidden = false;
                if(!QString::compare(qsl.at(4), "true"))isForbidden = true;
                else if(!QString::compare(qsl.at(4), "false"))isForbidden = false;
                double_chess_ui->setForbidden(isForbidden);
                double_chess_ui->setUIRightLabel(isForbidden);
                socketTcp->send_Message("gameStart "+myName+" "+qsl.at(1)+" "+qsl.at(3)+" "+qsl.at(4));
                double_chess_ui->setWindowTitle(qsl.at(2)+'('+qsl.at(3)+')'+"与 "+qsl.at(1)+"对战");
                nowOpponentName = qsl.at(1);
            }
        }
    }else if(!QString::compare(s1, "gameNotReady")){
        if(!QString::compare(qsl.at(2), myName)){
            this->ui->textEdit_status->append(qsl.at(1)+" is not ready.");
        }
    }else if(!QString::compare(s1, "gameStart")){
        if(!QString::compare(qsl.at(2), myName)){
            this->ui->textEdit_status->append("Game start with "+qsl.at(1));
            ChessStatus cs = NONE;
            if(!QString::compare(qsl.at(3), "BLACK"))cs = BLACK;
            else if(!QString::compare(qsl.at(3), "WHITE"))cs=WHITE;
            double_chess_ui = new doubleWuziChessUI(nullptr, true, cs);
            connect(this, &DoubleGameChoose::sendCommendToUI, double_chess_ui, &doubleWuziChessUI::get_commend);
            connect(double_chess_ui, &doubleWuziChessUI::sendDownChessMessageSignal, this, &DoubleGameChoose::downChessCSlot);
            bool isForbidden = false;
            if(!QString::compare(qsl.at(4), "true"))isForbidden = true;
            else if(!QString::compare(qsl.at(4), "false"))isForbidden = false;
            double_chess_ui->setForbidden(isForbidden);
            double_chess_ui->setUIRightLabel(isForbidden);
            double_chess_ui->setWindowTitle(qsl.at(2)+'('+qsl.at(3)+')'+"与 "+qsl.at(1)+"对战");
            double_chess_ui->show();
            nowOpponentName = qsl.at(1);
        }
    }else if(!QString::compare(s1, "pingAll")){
        if(!QString::compare(qsl.at(2), "all")){
            socketTcp->send_Message("pingBack "+myName+' '+qsl.at(1));

        }
    }else if(!QString::compare(s1, "pingBack")){
        if(!QString::compare(qsl.at(2), myName)){
            people_online->append(qsl.at(1));
            ui->listWidget->addItem(qsl.at(1));
        }
    }else if(!QString::compare(s1, "downChess")){
        qDebug()<<myName<<" "<<nowOpponentName;
        if(!QString::compare(qsl.at(2), myName)&&!QString::compare(qsl.at(1), nowOpponentName)){
            emit sendCommendToUI(qsl.at(3));
        }
    }
}

void DoubleGameChoose::downChessCSlot(int x, int y)
{
    QString s = "downChess";
    QString myName = ui->lineEdit_name->text();
    s = s+ " "+myName+" "+nowOpponentName+" ";
    QString s1 = QString::number(x);
    QString s2 = QString::number(y);
    if(s1.length()==1)s1 = '0'+s1;
    if(s2.length()==1)s2 = '0'+s2;
    s = s + '('+s1+','+s2+')';
    socketTcp->send_Message(s);
}

void DoubleGameChoose::on_pushButton_connect_clicked()
{
    this->socketTcp = new SocketTcp(ui->lineEdit_ip->text(), ui->lineEdit_port->text().toInt(), true);
    connect(socketTcp, &SocketTcp::isGetMessage, this, &DoubleGameChoose::analysisMessage);
    ui->pushButton_connect->setEnabled(false);
    ui->pushButton_quitconnect->setEnabled(true);
    ui->pushButton_refresh->setEnabled(true);
    ui->pushButton_start->setEnabled(true);
}

void DoubleGameChoose::on_pushButton_quitconnect_clicked()
{
    this->socketTcp->disconnect();
    ui->pushButton_refresh->setEnabled(false);
    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_quitconnect->setEnabled(false);
    ui->pushButton_start->setEnabled(false);
}

void DoubleGameChoose::on_pushButton_start_clicked()
{
    QString myName = ui->lineEdit_name->text();
    QString opponentName = ui->lineEdit_other->text();
    if(!QString::compare(myName, opponentName))ui->textEdit_status->append("Please go to single play to have game with yourself.");
    else if(myName.isEmpty())ui->textEdit_status->append("Please input your name.");
    else if(opponentName.isEmpty())ui->textEdit_status->append("Please input your opponent's name!");
    else{
        QString str = "gameRequest ";
        str= str + myName + ' ' + opponentName + ' ';
        QString color_chess;
        if(ui->radioButton_black->isChecked())color_chess = "BLACK";
        else if(ui->radioButton_white->isChecked())color_chess = "WHITE";
        else if(ui->radioButton_random->isChecked()){
            srand(time(NULL));
            int n = rand() % 2;
            if (n==0)color_chess = "BLACK";
            else color_chess = "WHITE";
        }
        str = str+color_chess;
        QString isForbidden;
        if(ui->checkBox_isForbidden->isChecked())isForbidden = "true";
        else isForbidden = "false";
        str = str+' '+isForbidden;
        nowOpponentName = opponentName;
        socketTcp->send_Message(str);
    }
}

void DoubleGameChoose::on_lineEdit_messageInput_returnPressed()
{
    QString tempS = ui->lineEdit_messageInput->text();
    if(!tempS.isEmpty()&&!ui->lineEdit_name->text().isEmpty()){
        tempS+='\n';
        tempS = "chat "+ui->lineEdit_name->text()+" all "+tempS;
        socketTcp->send_Message(tempS);
        this->ui->lineEdit_messageInput->clear();
    }else if(ui->lineEdit_name->text().isEmpty()){
        this->ui->textEdit_status->append("No name");
    }
}

void DoubleGameChoose::on_pushButton_refresh_clicked()
{
    if(!ui->lineEdit_name->text().isEmpty()){
        socketTcp->send_Message("pingAll "+ui->lineEdit_name->text()+" all");
        people_online->clear();
        ui->listWidget->clear();
    }
}
