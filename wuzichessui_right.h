#ifndef WUZICHESSUI_RIGHT_H
#define WUZICHESSUI_RIGHT_H

#include <QWidget>

namespace Ui {
class wuziChessUI_right;
}

class wuziChessUI_right : public QWidget
{
    Q_OBJECT

public:
    explicit wuziChessUI_right(QWidget *parent = nullptr);
    ~wuziChessUI_right();
    void setLabel(QString s);
    void setTextEditAppend(QString s);
    void setLabel2(QString s);

private:
    Ui::wuziChessUI_right *ui;
};

#endif // WUZICHESSUI_RIGHT_H
