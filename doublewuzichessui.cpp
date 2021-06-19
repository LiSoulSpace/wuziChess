#include <QHBoxLayout>
#include <QSplitter>
#include <iostream>
#include "wuzi_chess.cpp"
#include "doublewuzichessui.h"

doubleWuziChessUI::doubleWuziChessUI(QWidget *parent, bool isOnline_p, ChessStatus mineChessColor_t) :
    QWidget(parent), isOnline(isOnline_p), mineChessColor(mineChessColor_t) ,scene(new QGraphicsScene(this))
{
    this->setFixedSize(1000, 720);
    nowChessStatus = BLACK;
    wuziChess = new wuzi_chess<ChessStatus>();
    this->setAttribute(Qt::WA_DeleteOnClose);
    QSplitter *vSplitter = new QSplitter;
    vSplitter->setOrientation(Qt::Horizontal);


    View *view = new View("wuzi chess view");
    scene->setSceneRect(0, 0, 680, 680);
    view->view()->setScene(scene);
    vSplitter->addWidget(view);

    wuziChessRight = new wuziChessUI_right;
    vSplitter->addWidget(wuziChessRight);
    wuziChessRight->setLabel("黑色");

    connect(view, &View::down_chess_signal_inView, this, &doubleWuziChessUI::add_chess);

    pixmap_black = new QPixmap(":/image/piece/black_piece.png");
    pixmap_white = new QPixmap(":/image/piece/white_piece.png");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(vSplitter);
    setLayout(layout);
}

doubleWuziChessUI::~doubleWuziChessUI(){}

void doubleWuziChessUI::setForbidden(bool isForbidden)
{
    this->wuziChess->setForbidden(isForbidden);
}

void doubleWuziChessUI::setUIRightLabel(bool isFobidden)
{
    if(isFobidden)
    this->wuziChessRight->setLabel2("禁手开启");
    else this->wuziChessRight->setLabel2("禁手关闭");
}

void doubleWuziChessUI::show_win_messagebox()
{
    ChessStatus cs = this->wuziChess->get_winner();
    QString s;
    if(cs == BLACK)s = "BLACK WIN";
    else if(cs == WHITE)s = "WHITE WIN";
    QMessageBox message(QMessageBox::NoIcon, "Finished", s);
    message.exec();
    message.setAttribute(Qt::WA_DeleteOnClose);
}

void doubleWuziChessUI::closeEvent(QCloseEvent *event)
{
    emit doubleWuziChessUIClose();
    if(!this->wuziChess->get_isFinished()){
        emit abnormalInterrupt();
    }
}

void doubleWuziChessUI::add_chess(int x, int y)
{
    qDebug()<<"clicked on ("<<x<<','<<y<<')';
    bool isFinished = this->wuziChess->get_isFinished();
    if(!isFinished){
        if(!isOnline){
            if(this->wuziChess->get_position_status(x, y)==NONE){
                coordinate<ChessStatus> c;
                c.x = x;
                c.y = y;
                c.cs = nowChessStatus;
                this->wuziChess->down_chess(c);
                qDebug()<<"in wuziChessUI"<<x<<" "<<y;

                if(nowChessStatus==WHITE){
                    item = new ChessPiece(*pixmap_white, 0, 0, false);
                    item->setPos(QPointF(10+y*44, 10+x*44));
                    scene->addItem(item);
                    char s = 'A'+y;
                    this->wuziChessRight->setTextEditAppend("黑棋 : "+QString::number(x+1)+','+s);
                }
                else if(nowChessStatus==BLACK){
                    item = new ChessPiece(*pixmap_black, 0, 0, false);
                    item->setPos(QPointF(10+y*44, 10+x*44));
                    scene->addItem(item);
                    char s = 'A'+y;
                    this->wuziChessRight->setTextEditAppend("白棋 : "+QString::number(x+1)+','+s);
                }
                nowChessStatus = ChessStatus(3-nowChessStatus);
                QString str;
                if(nowChessStatus==WHITE) str = "白色";
                else if(nowChessStatus == BLACK) str = "黑色";
                this->wuziChessRight->setLabel(str);
            }
            //this->wuziChess->show_chessboard();
            if(this->wuziChess->get_isFinished()){
                ChessStatus cs = this->wuziChess->get_winner();
                QString s;
                if(cs == BLACK)s = "黑棋";
                else if(cs == WHITE)s = "白棋";
                this->wuziChessRight->setTextEditAppend(s+" 胜利");
                show_win_messagebox();
            }
        } else {
            if(nowChessStatus != mineChessColor){
                qDebug()<<nowChessStatus<<" != "<<mineChessColor;
                return;
            }
            else{
                qDebug()<<"sendDownChessMessageSignal in doublewuzichessui";
                emit sendDownChessMessageSignal(x, y);
                if(this->wuziChess->get_position_status(x, y)==NONE){
                    coordinate<ChessStatus> c;
                    c.x = x;
                    c.y = y;
                    c.cs = nowChessStatus;
                    this->wuziChess->down_chess(c);
                    if(nowChessStatus==WHITE){
                        item = new ChessPiece(*pixmap_white, 0, 0, false);
                        item->setPos(QPointF(10+y*44, 10+x*44));
                        scene->addItem(item);
                        char s = 'A'+y;
                        this->wuziChessRight->setTextEditAppend("黑棋 : "+QString::number(x+1)+','+s);
                    }
                    else if(nowChessStatus==BLACK){
                        item = new ChessPiece(*pixmap_black, 0, 0, false);
                        item->setPos(QPointF(10+y*44, 10+x*44));
                        scene->addItem(item);
                        char s = 'A'+y;
                        this->wuziChessRight->setTextEditAppend("白棋 : "+QString::number(x+1)+','+s);
                    }
                    nowChessStatus = ChessStatus(3-nowChessStatus);
                }
                this->wuziChess->show_chessboard();
                if(this->wuziChess->get_isFinished()){
                    ChessStatus cs = this->wuziChess->get_winner();
                    QString s;
                    if(cs == BLACK)s = "黑棋";
                    else if(cs == WHITE)s = "白棋";
                    this->wuziChessRight->setTextEditAppend(s+" 胜利");
                    show_win_messagebox();
                }
            }
        }
        if(this->wuziChess->get_isFinished()){
            show_win_messagebox();
        }
    }else{
        show_win_messagebox();
    }
}

void doubleWuziChessUI::get_commend(QString s)
{
    qDebug()<<"get_commend : "<<s;
    int x = s.mid(1, 2).toInt();
    int y = s.mid(4, 2).toInt();
    receive_chess(x, y);
}

void doubleWuziChessUI::receive_chess(int x, int y)
{
    qDebug()<<"receive_chess "<< x<<" "<<y;
    if(this->wuziChess->get_position_status(x, y)==NONE){
        coordinate<ChessStatus> c;
        c.x = x;
        c.y = y;
        c.cs = nowChessStatus;
        this->wuziChess->down_chess(c);
        if(nowChessStatus==WHITE){
            item = new ChessPiece(*pixmap_white, 0, 0, false);
            item->setPos(QPointF(10+y*44, 10+x*44));
            scene->addItem(item);
            char s = 'A'+y;
            this->wuziChessRight->setTextEditAppend("黑棋 : "+QString::number(x+1)+','+s);
        }
        else if(nowChessStatus==BLACK){
            item = new ChessPiece(*pixmap_black, 0, 0, false);
            item->setPos(QPointF(10+y*44, 10+x*44));
            scene->addItem(item);
            char s = 'A'+y;
            this->wuziChessRight->setTextEditAppend("白棋 : "+QString::number(x+1)+','+s);
        }
        nowChessStatus = ChessStatus(3-nowChessStatus);
        QString str;
        if(nowChessStatus==WHITE) str = "白色";
        else if(nowChessStatus == BLACK) str = "黑色";
        this->wuziChessRight->setLabel(str);
    }
    this->wuziChess->show_chessboard();
    if(this->wuziChess->get_isFinished()){
        ChessStatus cs = this->wuziChess->get_winner();
        QString s;
        if(cs == BLACK)s = "黑棋";
        else if(cs == WHITE)s = "白棋";
        this->wuziChessRight->setTextEditAppend(s+" 胜利");
        show_win_messagebox();
    }
}
