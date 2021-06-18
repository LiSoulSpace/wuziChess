#ifndef SOCKETTCP_H
#define SOCKETTCP_H

#include <QObject>
#include <QTcpSocket>
#include <QMessageBox>
#include <QDataStream>
#include <QDialog>
#include <QTcpSocket>
class SocketTcp:public QObject
{
    Q_OBJECT
public:
    SocketTcp(QString ip, int port, bool isSend_get);
    void send_Message(QString s);
    QString get_Message();
    void disconnect();
    bool get_isOpened();
    void displayError(QAbstractSocket::SocketError socketError);
private slots:
    void read_Message();
signals:
    void isGetMessage(QString s);
private:
    bool isSend_get;
    QTcpSocket *tcpSocket;
    QString ip;
    int port;
    QString message;
};

#endif // SOCKETTCP_H
