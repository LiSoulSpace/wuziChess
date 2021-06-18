#ifndef DOUBLEGAMECHOOSE_H
#define DOUBLEGAMECHOOSE_H

#include <QWidget>
#include <QTcpServer>
#include <sockettcp.h>
#include <QCloseEvent>
#include <doublewuzichessui.h>

namespace Ui {
class DoubleGameChoose;
}

class DoubleGameChoose : public QWidget
{
    Q_OBJECT

public:
    explicit DoubleGameChoose(QWidget *parent = nullptr);
    ~DoubleGameChoose();
    void insertMessage(QString s);
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void sendCommendToUI(QString s);
    void showMainWindow();
public slots:
    void doubleUICloseSlot();
    void analysisMessage(QString s);
    void downChessCSlot(int x, int y);
private slots:
    void on_pushButton_connect_clicked();

    void on_pushButton_quitconnect_clicked();

    void on_pushButton_start_clicked();

    void on_lineEdit_messageInput_returnPressed();

    void on_pushButton_refresh_clicked();

private:
    QString nowOpponentName;
    doubleWuziChessUI* double_chess_ui;
    Ui::DoubleGameChoose *ui;
    SocketTcp *socketTcp;
    QStringList *people_online;
};

#endif // DOUBLEGAMECHOOSE_H
