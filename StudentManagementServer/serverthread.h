#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include"mysocket.h"

class MySocket;

class ServerThread:public QThread
{
    Q_OBJECT
public:
    ServerThread(int socketDes,QObject*parent=0);
    ~ServerThread();
    void run();
    int socketDescriptor;
signals:
    void disconnectTCP(int);
private slots:
    void disconnectToHost();
private:
    MySocket *socket;
};

#endif // SERVERTHREAD_H
