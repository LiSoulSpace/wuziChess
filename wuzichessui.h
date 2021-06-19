#ifndef WUZICHESSUI_H
#define WUZICHESSUI_H

#include <QWidget>
#include <QSplitter>
#include <QGraphicsScene>
#include <QMessageBox>
#include "chesspiece.h"
#include "chessuiboard.h"
#include "chess_main.h"
#include "wuzi_chess.h"
#include "wuzichessui_right.h"

namespace Ui {
class wuziChessUI;
}

class wuziChessUI : public QWidget
{
    Q_OBJECT

public:
    explicit wuziChessUI(QWidget *parent = nullptr);
    ~wuziChessUI();
    void addChess(coordinate<ChessStatus> c);
    void setFobidden(bool isFobidden);
    void setUIRight(bool isFobidden);
protected:
    void show_win_messagebox();
public slots:
    void add_chess(int x, int y);

private:
    wuziChessUI_right* wuziChessRight;
    QGraphicsScene *scene;
    Ui::wuziChessUI *ui;
    wuzi_chess<ChessStatus> *wuziChess;
    ChessStatus nowChessStatus;
    QPixmap *pixmap_black;
    QPixmap *pixmap_white;
    QGraphicsItem *item;
};

#endif // WUZICHESSUI_H
