#include "sockettcp.h"
#include <QByteArray>
#include <QtNetwork>

SocketTcp::SocketTcp(QString ip, int port, bool isSend_get)
{
    this->ip = ip;
    this->port = port;
    this->isSend_get = isSend_get;
    tcpSocket = new QTcpSocket();
    tcpSocket->connectToHost(ip, port);
    connect(tcpSocket, &QIODevice::readyRead, this, &SocketTcp::read_Message);
    connect(tcpSocket, &QAbstractSocket::errorOccurred,this, &SocketTcp::displayError);
}

void SocketTcp::send_Message(QString s)
{
    int t = s.size();
    QString str_temp = QString::number(t);
    t = str_temp.size();
    for(int i = 4-t;i>0;i--){
        str_temp = " "+str_temp;
    }
    s = str_temp+s;
    qDebug()<<"send_message : "<<s;
    QByteArray sbA = s.toUtf8();
    tcpSocket->write(sbA);
    tcpSocket->flush();
}

void SocketTcp::read_Message()
{
    QByteArray sbB = tcpSocket->readAll();
    if(!sbB.isEmpty()){
        message = QString(sbB);
        while(true){
            int message_1 = message.mid(0, 4).toInt();
            QString str_true = message.mid(4, message_1);
            emit isGetMessage(str_true);
            if(message.size() == 4 + message_1)break;
            else {
                message = message.mid(4+message_1, message.size()-1);
            }
        }
    }else{
        message = "Something Wrong!";
    }
}

QString SocketTcp::get_Message()
{
    return message;
}

void SocketTcp::disconnect()
{
    tcpSocket->disconnectFromHost();
}

bool SocketTcp::get_isOpened()
{
    return tcpSocket->isOpen();
}

void SocketTcp::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug()<<"The host was not found. Please check the host name and port settings.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug()<<"The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct.";
        break;
    default:
        qDebug()<<tr("The following error occurred: %1.").arg(tcpSocket->errorString());
    }
}
