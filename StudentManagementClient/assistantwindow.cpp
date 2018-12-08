#include "assistantwindow.h"
#include "ui_assistantwindow.h"

AssistantWindow::AssistantWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AssistantWindow)
{
    ui->setupUi(this);
}

AssistantWindow::~AssistantWindow()
{
    delete ui;
}
