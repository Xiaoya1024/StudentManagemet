#include <QApplication>
#include"mysocket.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MySocket mySocket;
    mySocket.show();

    return a.exec();
}
