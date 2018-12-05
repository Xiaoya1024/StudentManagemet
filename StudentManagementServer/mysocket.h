#ifndef MYSOCKET_H
#define MYSOCKET_H
#include<QTcpSocket>
#include<QHostAddress>
#include"protocol.h"
#include"mysqlserver.h"
#include<QDir>
#include<QDebug>
#include"myserver.h"

class SqlServer;

class MySocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit MySocket(int socket,QObject*parent=0);
//signals:
//    void signRevData(QByteArray,int);
public slots:
    void slotRevData();
    //void sendMsg(char*msg,int len,int id);
private:
    int socketDescriptor;
    QString userID;
    int userType;

};

#endif // MYSOCKET_H
