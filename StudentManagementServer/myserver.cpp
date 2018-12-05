#include "myserver.h"

SqlServer sqlServer=fun();
SqlServer fun(){
    SqlServer sqlServer;
    sqlServer.InitSql();
    return sqlServer;
}


MyServer::MyServer(QObject *parent)
    : QTcpServer(parent)
{

}

MyServer::~MyServer()
{

}

void MyServer::incomingConnection(qintptr socketDescriptor){
    //每当一个新的客户端连接时，通过标识码socketDescriptor，实现与对应的客户端通信
    socketList.append(socketDescriptor);
    qDebug()<<"the client had linked!";

    //为一个客户端分配一个线程
    ServerThread *thread=new ServerThread(socketDescriptor,0);

    //开启一个线程
    connect(thread,SIGNAL(started()),this,SLOT(showConnection()));
    connect(thread,SIGNAL(disconnectTCP(int)),this,SLOT(showDisConnection(int)));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));

    thread->start();
}

void MyServer::showConnection(){
    count++;
    qDebug()<<"Client counts:"<<count;
}
void MyServer::showDisConnection(int socketDescriptor){
    count--;
    qDebug()<<"count:"<<count;
    for(int i=0;i<socketUserList.size();i++){
        if(socketUserList.at(i).socketDescriptor==socketDescriptor){
            socketUserList.removeAt(i);
        }
    }
}
