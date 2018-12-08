#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QMainWindow>
#include "mysocket.h"
namespace Ui {
class ManagerWindow;
}

class ManagerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = 0);
    ~ManagerWindow();
    void GetInstituteInfo(InstituteInfo_package instiInfo);
    void GetClassInfo(ClassInfo_package classInfo);
    void GetClassStuInfo(user_full_package stuInfo);
    void GetCourseInfo(student_course_package courseInfo);
    void GetCourseStu(user_mid_package  c2);
    void GetCourseScore(student_courseScore_package s2);
    void GetCourseScore2(student_courseScoreInfo_package *s1,int n);
    void GetLabelin(int i);
    void GetClassLabel(int n);
     QTcpSocket *tcpSocket;
     student_courseScore_package *ss;
     class_Info_Package *cla;
private slots:
    void on_actionxueyuanchauxn_triggered();
    void on_tableWidget_InstitueInfo_itemClicked(QTableWidgetItem *item);
    void on_pushButtonback1_clicked();
    void on_tableWidget_InClass_itemClicked(QTableWidgetItem *item);
    void on_pushButtonback2_clicked();
    void on_action1_3_triggered();
    void on_comboBox_currentIndexChanged(int index);
    void on_tableWidget_course1_itemClicked(QTableWidgetItem *item);
    void on_pushButton_6_clicked();
    void on_pushButton_in_clicked();
    void on_pushButton_out_clicked();
    void on_action1_8_triggered();
    void on_action1_5_triggered();
    void on_comboBox_course_currentIndexChanged(int index);
    void on_action1_11_triggered();
    void on_comboBox_class_currentIndexChanged(int index);
    void on_pushButton_add_clicked();
    void on_action2_4_triggered();
    void on_pushButton_clicked();
    void on_pushButton_del_clicked();

private:
    Ui::ManagerWindow *ui;

};

#endif // MANAGERWINDOW_H
