#ifndef MASTERWINDOW_H
#define MASTERWINDOW_H

#include <QMainWindow>
#include "mysocket.h"
namespace Ui {
class MasterWindow;
}

class MasterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MasterWindow(QWidget *parent = 0);
    ~MasterWindow();


private:
    Ui::MasterWindow *ui;
    QTcpSocket *tcpSocket;
};

#endif // MASTERWINDOW_H
