#ifndef CHESSUIBOARD_H
#define CHESSUIBOARD_H

#include <QGraphicsView>
#include <QLabel>
#include <QToolButton>
#include <QSlider>

class View;

class ChessUIBoard : public QGraphicsView
{
    Q_OBJECT
public:
    ChessUIBoard(View *v) : QGraphicsView(), view(v) {
        this->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        this->setFixedSize(720, 720);
    }

signals:
    void down_chess(int x, int y);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    View *view;
};

class View : public QFrame
{
    Q_OBJECT
public:
    explicit View(const QString &name, QWidget *parent = nullptr);

    QGraphicsView *view() const;

signals:
    void down_chess_signal_inView(int x, int y);

public slots:
    void down_chess_inView(int x, int y);

private:
    ChessUIBoard *graphicsView;
    QToolButton *antialiasButton;
    QToolButton *printButton;
    QToolButton *resetButton;
    QSlider *zoomSlider;
    QSlider *rotateSlider;
};

#endif // CHESSUIBOARD_H
