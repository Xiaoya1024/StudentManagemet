#ifndef MYSERVER_H
#define MYSERVER_H

#include<QTcpServer>
#include"serverthread.h"
#include"protocol.h"
#include<QtNetwork>
#include"mysqlserver.h"
#include<QDebug>
#include<QAbstractSocket>
#include<QMessageBox>
#include<QByteArray>

class SqlServer;
extern SqlServer sqlServer;
SqlServer fun();


class MyServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit MyServer(QObject *parent=0);
    ~MyServer();
    QList<ClientInfo> socketUserList;
    QList<int> socketList;//建立一个list存连接服务器的客户端id
    int count=0;

protected:
    //重写此虚函数，每次有客户端来连接时触发该虚函数
    void incomingConnection(qintptr socketDescriptor);
private slots:
    void showConnection();
    void showDisConnection(int socketDescriptor);

};

#endif // MYSERVER_H
