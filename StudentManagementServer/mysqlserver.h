#ifndef SQLSERVER_H
#define SQLSERVER_H

#include<QSqlQuery>//专门对Sql语句操作的类
#include<QSqlError>
#include<QSqlDatabase>
#include<QDebug>
#include<QTcpSocket>
#include"protocol.h"

class SqlServer
{
public:
    SqlServer();
    void InitSql();//连接数据库

    /*
    这里填写各种对数据库的操作方法
    */
    int checkLogin(QString userID,QString userPwd);//检查登录是否成功，成功返回用户的type，不成功返回-1
    user_simple_package FindUserSimpleInfo(QString userID,int userType);//获取用户的简单信息
    user_full_package FindUserFullInfo(QString userID,int userType);//获取用户完整信息
    student_course_package* FindStuCourseInfo(QString StuID,int *cont);//学生查看自己选的课程信息
    student_courseScore_package* FindStuCourseScoreInfo(QString StuID,int *cont);//学生查看自己成绩
    student_course_package* FindStuSelectedCourseInfo(QString StuID,int type,int *cont);//学生选课
    bool isStuSelectedCourseSucced(QString StuID,QString CourseID);//学生选课是否成功
    bool ChangePwd(QString UserID,QString Pwd);
    InstituteInfo_package* FindInstituteInfo(int *cont);
    ClassInfo_package* FindClassInfo(QString InstituteID,int*cont);
    user_full_package* FindStuInfoInClass(QString ClassID,int*cont);
    student_course_package* FindAllCourseInfo(int *cont,int type);
    user_mid_package* FindStuInfoInCourse(QString CourseID,int *cont);
private:
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlQuery *query2;
};

#endif // SQLSERVER_H
