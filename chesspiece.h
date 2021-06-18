#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QWidget>
#include <QColor>
#include <QGraphicsItem>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "wuzi_chess.h"

class ChessPiece : public QGraphicsItem
{
public:
    ChessPiece(const QPixmap pixmax, int x, int y, bool isPiecet);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
private:
    int x;
    int y;
    int number;
    bool isPiece;
    QPixmap pixmap;
    QList<QPointF> stuff;
};

#endif // CHESSPIECE_H
