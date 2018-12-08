#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include "mysocket.h"
namespace Ui {
class StudentWindow;
}

class StudentWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = 0);
    ~StudentWindow();
    void GetInfo(user_simple_package info);
    void GetInfo2(user_full_package info);
    void GetImg();
    void GetCourse(student_course_package mycourse);
    void GetScore(student_courseScore_package myscore);
    void GetSelectCourse(student_course_package mycourse);


   QTcpSocket *tcpSocket;

private slots:
   void on_label_Index_StuLearnMore_linkActivated(const QString &link);

   void on_buttonStuInfo_triggered();

   void on_buttonStuCourse_triggered();

   void on_buttonStuScore_triggered();

   void on_buttonStuSelectCourse_triggered();


   void on_comboBox_StuSelectCourse_currentIndexChanged(int index);

   void on_tableWidget_StuSelectCourse_itemClicked(QTableWidgetItem *item);

   void on_tableWidget_StuSelectCourse_itemEntered(QTableWidgetItem *item);

   void on_tableWidget_StuSelectCourse_itemChanged(QTableWidgetItem *item);

   void on_tableWidget_StuSelectCourse_cellEntered(int row, int column);

   void on_buttonStuForgotPwd_triggered();

   void on_button_StuForgotPwd_True_clicked();

private:
    Ui::StudentWindow *ui;

};

#endif // STUDENTWINDOW_H
