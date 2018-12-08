#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QWidget>
#include<QtNetwork>
#include"protocol.h"
#include<QString>
#include<QByteArray>
#include<QStringList>
#include<QStackedWidget>
#include<QTableWidget>
#include<QMessageBox>
#include<QDebug>
#include<QImageReader>
#include<string>
#include<qfiledialog.h>

#include "studentwindow.h"
#include "teacherwindow.h"
#include "managerwindow.h"
#include "assistantwindow.h"
#include "masterwindow.h"



//#define ip "192.168.43.186"
#define ip "127.0.0.1"
#define port 8000

namespace Ui {
class MySocket;
}
class StudentWindow;
class TeacherWindow;
class ManagerWindow;
class AssistantWindow;
class MasterWindow;


class MySocket : public QWidget
{
    Q_OBJECT

public:
    explicit MySocket(QWidget *parent = 0);
    ~MySocket();
protected:
    void Init();
private slots:
    void displayError(QAbstractSocket::SocketError);
    void readMessages();
    void on_pushButtonLogin_clicked();

    void on_pushButton_clicked();

private:
    Ui::MySocket *ui;
    QTcpSocket *tcpSocket;
    StudentWindow *student;
    TeacherWindow *teacher;
    ManagerWindow *manager;
    AssistantWindow *assistant;
    MasterWindow *master;

};

#endif // MYSOCKET_H
