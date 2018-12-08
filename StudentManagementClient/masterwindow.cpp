#include "masterwindow.h"
#include "ui_masterwindow.h"

MasterWindow::MasterWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MasterWindow)
{
    ui->setupUi(this);
}

MasterWindow::~MasterWindow()
{
    delete ui;
}
