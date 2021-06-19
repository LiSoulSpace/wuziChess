#ifndef DOUBLEWUZICHESSUI_H
#define DOUBLEWUZICHESSUI_H

#include <QWidget>
#include <QSplitter>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QCloseEvent>
#include "chesspiece.h"
#include "chessuiboard.h"
#include "chess_main.h"
#include "wuzi_chess.h"
#include "wuzichessui_right.h"

class doubleWuziChessUI:public QWidget
{
    Q_OBJECT
public:
    doubleWuziChessUI(QWidget *parent = nullptr, bool isOnline_p = false, ChessStatus mineChessColor_t = BLACK);
    ~doubleWuziChessUI();
    void addChess(coordinate<ChessStatus> c);
    void setForbidden(bool isForbidden);
    void setUIRightLabel(bool isFobidden);
protected:
    void show_win_messagebox();
    void closeEvent(QCloseEvent *event);
public slots:
    void add_chess(int x, int y);
    void get_commend(QString s);
    void receive_chess(int x, int y);
signals:
    void abnormalInterrupt();
    void doubleWuziChessUIClose();
    void sendDownChessMessageSignal(int x, int y);
private:
    bool isOnline;
    bool isFinished;
    bool isYourTurn;
    wuziChessUI_right* wuziChessRight;
    ChessStatus mineChessColor;
    QString opponent;
    QGraphicsScene *scene;
    wuzi_chess<ChessStatus> *wuziChess;
    ChessStatus nowChessStatus;
    QPixmap *pixmap_black;
    QPixmap *pixmap_white;
    QGraphicsItem *item;

};

#endif // DOUBLEWUZICHESSUI_H
