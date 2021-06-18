#ifndef GAMECHOOSE_H
#define GAMECHOOSE_H

#include <QWidget>
#include "wuzichessui.h"

namespace Ui {
class GameChoose;
}

class GameChoose : public QWidget
{
    Q_OBJECT

public:
    explicit GameChoose(QWidget *parent = nullptr);
    ~GameChoose();

private slots:
    void on_pushButton_clicked();

private:
    Ui::GameChoose *ui;
    wuziChessUI* wuzi_ui;
};

#endif // GAMECHOOSE_H
