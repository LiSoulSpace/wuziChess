#include "wuzichessui.h"
#include "ui_wuzichessui.h"

#include <QHBoxLayout>
#include <QSplitter>
#include <iostream>
#include "wuzi_chess.cpp"

wuziChessUI::wuziChessUI(QWidget *parent) :
    QWidget(parent), scene(new QGraphicsScene(this)),
    ui(new Ui::wuziChessUI)
{
    nowChessStatus = BLACK;
    wuziChess = new wuzi_chess<ChessStatus>();
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    QSplitter *vSplitter = new QSplitter;
    vSplitter->setOrientation(Qt::Horizontal);

    View *view = new View("wuzi chess view");
    scene->setSceneRect(0, 0, 680, 680);
    view->view()->setScene(scene);
    vSplitter->addWidget(view);

    connect(view, &View::down_chess_signal_inView, this, &wuziChessUI::add_chess);

    pixmap_black = new QPixmap(":/image/piece/black_piece.png");
    pixmap_white = new QPixmap(":/image/piece/white_piece.png");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(vSplitter);
    setLayout(layout);
}

wuziChessUI::~wuziChessUI()
{
    delete ui;
}

void wuziChessUI::show_win_messagebox()
{
    ChessStatus cs = this->wuziChess->get_winner();
    QString s;
    if(cs == BLACK)s = "BLACK WIN";
    else if(cs == WHITE)s = "WHITE WIN";
    QMessageBox message(QMessageBox::NoIcon, "Finished", s);
    message.exec();
    message.setAttribute(Qt::WA_DeleteOnClose);
}

void wuziChessUI::add_chess(int x, int y)
{
    bool isFinished = this->wuziChess->get_isFinished();
    qDebug()<<"isFinished : "<<isFinished;
    if(!isFinished){
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
            }
            else if(nowChessStatus==BLACK){
                item = new ChessPiece(*pixmap_black, 0, 0, false);
                item->setPos(QPointF(10+y*44, 10+x*44));
                scene->addItem(item);
            }
            nowChessStatus = ChessStatus(3-nowChessStatus);
        }
        this->wuziChess->show_chessboard();
        if(this->wuziChess->get_isFinished()){
            show_win_messagebox();
        }
    }else{
        show_win_messagebox();
    }
}
