#include "myserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

//    QPixmap pix(":/1.jpg");
//    QBuffer buffer;
//    buffer.open(QIODevice::ReadWrite);
//    pix.save(&buffer,"jpg");
//    quint32 pix_len=(quint32)buffer.data().size();

//    qDebug()<<"image size:"<<pix_len;
    MyServer s;
    s.listen(QHostAddress::Any,8000);
    return a.exec();
}
