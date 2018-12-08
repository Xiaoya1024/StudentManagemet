#ifndef ASSISTANTWINDOW_H
#define ASSISTANTWINDOW_H

#include <QMainWindow>
#include "mysocket.h"
namespace Ui {
class AssistantWindow;
}

class AssistantWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AssistantWindow(QWidget *parent = 0);
    ~AssistantWindow();

private:
    Ui::AssistantWindow *ui;
    QTcpSocket *tcpSocket;
};

#endif // ASSISTANTWINDOW_H
