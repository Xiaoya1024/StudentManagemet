#include "serverthread.h"

ServerThread::ServerThread(int socketDescriptor,QObject*parent):
    QThread(parent),socketDescriptor(socketDescriptor)
{

}
ServerThread::~ServerThread(){
    socket->close();
}
void ServerThread::run(){
    socket=new MySocket(socketDescriptor,0);

    /*
    重写incomingConnection(qintptr socketDescriptor)函数，
    再有连接时这个函数会被系统调用，socketDescriptor为套接字描述符，
    用这个描述符创建一个socket就可以了，即setSocketDescriptor这个函数，
    描述符传给这个函数参数即可
    */
    //如果传入的套接字描述符不合法，退出run函数
    if(!socket->setSocketDescriptor(socketDescriptor)){
        return;
    }

    //当Client向主机发来消息时，触发readyRead()信号，触发slotRevData()槽函数
    connect(socket,SIGNAL(readyRead()),socket,SLOT(slotRevData()));

    //当客户端断开连接时，引发disconnecttoHost的槽函数，这个槽函数里会发送一个信号，最后被主机知道
    connect(socket,&MySocket::disconnected,this,&ServerThread::disconnectToHost);
    //要启动事件循环，必须在run()内调用exec()
    exec();
}
void ServerThread::disconnectToHost(){
    emit disconnectTCP(socketDescriptor);
    socket->disconnectFromHost();
}
