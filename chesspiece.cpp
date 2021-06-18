#include "chesspiece.h"
#include <QGraphicsSceneMouseEvent>


ChessPiece::ChessPiece(const QPixmap pixmax, int x, int y, bool isPieset)
{
    this->pixmap = pixmax;
    this->x = x;
    this->y = y;
    this->isPiece = isPieset;
}

QRectF ChessPiece::boundingRect() const
{
    return QRectF(0, 0, 110, 70);
}

void ChessPiece::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    pixmap = pixmap.scaled(44, 44);
    painter->drawPixmap(0, 0, pixmap);
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void ChessPiece::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void ChessPiece::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
