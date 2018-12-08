#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QMainWindow>
#include "mysocket.h"
namespace Ui {
class TeacherWindow;
}

class TeacherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TeacherWindow(QWidget *parent = 0);
    ~TeacherWindow();

private:
    Ui::TeacherWindow *ui;
    QTcpSocket *tcpSocket;
};

#endif // TEACHERWINDOW_H
