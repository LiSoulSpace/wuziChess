#include "chessuiboard.h"

#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif
#include <QtWidgets>
#include <QtMath>

View::View(const QString &name, QWidget *parent)
    : QFrame(parent)
{
    this->setFixedSize(690, 690);
    setFrameStyle(Sunken | StyledPanel);
    graphicsView = new ChessUIBoard(this);
    connect(graphicsView, &ChessUIBoard::down_chess, this, &View::down_chess_inView);
    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
    QSize iconSize(size, size);

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addWidget(graphicsView, 1, 0);
    setLayout(topLayout);
}

QGraphicsView *View::view() const
{
    return static_cast<QGraphicsView *>(graphicsView);
}

void View::down_chess_inView(int x, int y)
{
    emit down_chess_signal_inView(x, y);
}

void ChessUIBoard::drawBackground(QPainter *painter, const QRectF &rect)
{
    QImage image(":/image/board/checkboard.png");

    Q_UNUSED(rect);

    //绘制指定图片作为背景
    painter->setRenderHints(QPainter::SmoothPixmapTransform);
    QPixmap pixmap(":/image/board/checkboard.png");
    pixmap = pixmap.scaled(680, 680);
    painter->drawPixmap(0, 0, pixmap);
    update();
}

void ChessUIBoard::mousePressEvent(QMouseEvent *event)
{
    QPointF point = event->position();
    int x = point.x();
    int y = point.y();
    if(x > 22 && x < 671){
        if(y > 10 && y < 671) {
            x = (x-10)/44;
            y = (y-10)/44;
            emit down_chess(y, x);
        }
    }

}

void ChessUIBoard::mouseMoveEvent(QMouseEvent *event)
{

}

