#include "mysqlserver.h"

SqlServer::SqlServer()
{

}
void SqlServer::InitSql(){
    //添加SqlServer数据库
    db=QSqlDatabase::addDatabase("QODBC");
    QString dsn=QString::fromLocal8Bit("QTDSN");
    //连接数据库
    db.setHostName("127.0.0.1");

    /*
    最初这里我和我的搭档都想错了，认为对于不同的用户，应该分类成拥有不同权限的角色，
    这样每次一个用户登录时，就直接让这个用户操作数据库，因为对这个用户分配了权限，
    所以这个用户对某些操作不能实现，但是这个想法从一开始就是错的，还是对用户权限这里
    理解的不到位，用户权限是为了给操作数据库的程序员们设置的，而不是给使用我们系统的
    用户使用的，使用我们系统的用户在我们这里只是一条数据，而不是拥有操作数据库的“程序员”，
    对于用户权限的控制应该体现在界面上，如果用户没有删除数据这个功能，那么用户的界面上就
    不会显示删除这个按钮，这样用户就不能删除数据了。
    */
    //数据库用户名
    db.setUserName("sa");
    //数据库密码
    db.setPassword("asdejing");
    //使用的数据库名称
    db.setDatabaseName(dsn);

    if(db.open()){//数据库打开成功
        qDebug()<<"Database connected successfully!";
        query=new QSqlQuery(db);
        query2=new QSqlQuery(db);
        return;
    }
    else{//数据库打开失败
        qDebug()<<"Database connected failed!";
        return;
    }
}
int SqlServer::checkLogin(QString userID, QString userPwd){
    qDebug()<<"userID:"<<userID<<"userPwd:"<<userPwd;
    QString str=QString("select UserType from UserTable Where UserID='%1' And UserPwd='%2'").arg(userID).arg(userPwd);
    query->exec(str);
    int num=query->numRowsAffected();
    query->next();
    qDebug()<<"num:"<<num;
    if(num!=1){
        return -1;
    }
    else{
        qDebug()<<"userType:"<<query->value(0).toInt();
        return query->value(0).toInt();
    }
}
user_simple_package SqlServer::FindUserSimpleInfo(QString userID,int userType){
    user_simple_package userSimplePackage;
    qDebug()<<"userID"<<userID;
    if(userType==0){//如果是学生
        QString str=QString("select StuName from StudentTable where StuID='%1'").arg(userID);
        query->exec(str);
        int num=query->numRowsAffected();
        qDebug()<<"num:"<<num;
        query->next();
        strncpy(userSimplePackage.userID,userID.toLatin1().data(),10);
        qDebug()<<query->value(0).toString();
        strncpy(userSimplePackage.userName,query->value(0).toString().toLocal8Bit().data(),20);
        qDebug()<<"StuName:"<<userSimplePackage.userName;

    }
    else{

    }
    return userSimplePackage;
}
user_full_package SqlServer::FindUserFullInfo(QString userID, int userType){//用户完整信息包
    user_full_package userFullPackage;
    qDebug()<<"userID"<<userID;
    if(userType==0){
        QString str=QString("select * from stuFullInfo where StuID='%1'").arg(userID);
        query->exec(str);
        int num=query->numRowsAffected();
        qDebug()<<"num:"<<num;
        query->next();
        strncpy(userFullPackage.userInstituteName,query->value("InstitueName").toString().toLocal8Bit().data(),30);

        strncpy(userFullPackage.userClassName,query->value("ClassName").toString().toLocal8Bit().data(),30);
        strncpy(userFullPackage.userAssistantName,query->value("AssistantName").toString().toLocal8Bit().data(),20);
        strncpy(userFullPackage.usermasterName,query->value("MasterName").toString().toLocal8Bit().data(),20);
        userFullPackage.userGender=query->value("StuGender").toBool();
        strncpy(userFullPackage.userCardID,query->value("StuCardID").toString().toLocal8Bit().data(),20);
        QString str1=userFullPackage.userCardID;
        strncpy(userFullPackage.userBirthDay,QString(str1.mid(6,8)).toLocal8Bit().data(),10);
        userFullPackage.userAge=2018-str1.mid(6,4).toInt();
        strncpy(userFullPackage.userNativePlace,query->value("StuNativePlace").toString().toLocal8Bit().data(),50);
        strncpy(userFullPackage.userNationality,query->value("StuNationality").toString().toLocal8Bit().data(),50);
    }
    return userFullPackage;
}
student_course_package* SqlServer::FindStuCourseInfo(QString StuID,int*cont){//学生查看自己选的课程信息
    QString str=QString("select * from stuCourseInfo where StuID='%1'").arg(StuID);
    query->exec(str);
    int num=query->numRowsAffected();
    *cont=num;
    qDebug()<<"num:"<<num;
    student_course_package* studentCoursePackage;
    studentCoursePackage =(student_course_package*)malloc(sizeof(student_course_package)*num);
    int i=0;
    while (query->next()) {
        strncpy(studentCoursePackage[i].CourseID,query->value("CourseID").toString().toLocal8Bit().data(),10);
        strncpy(studentCoursePackage[i].CourseName,query->value("CourseName").toString().toLocal8Bit().data(),30);
        strncpy(studentCoursePackage[i].CourseTypeName,query->value("CourseTypeName").toString().toLocal8Bit().data(),20);
        strncpy(studentCoursePackage[i].TchName,query->value("WorkerName").toString().toLocal8Bit().data(),20);
        studentCoursePackage[i].CourseCredit=query->value("CourseCredit").toInt();
        i++;
    }
    return studentCoursePackage;
}
student_courseScore_package* SqlServer::FindStuCourseScoreInfo(QString StuID,int *cont){//学生查看自己成绩
    QString str=QString("select * from stuCourseInfo where StuID='%1'and Score!=NULL").arg(StuID);
    query->exec(str);
    int num=query->numRowsAffected();
    *cont=num;
    qDebug()<<"num:"<<num;
    student_courseScore_package* studentCourseScorePackage;
    studentCourseScorePackage=(student_courseScore_package*)malloc(sizeof(student_courseScore_package)*num);
    int i=0;
    while(query->next()){
        strncpy(studentCourseScorePackage[i].CourseID,query->value("CourseID").toString().toLocal8Bit().data(),10);
        strncpy(studentCourseScorePackage[i].CourseName,query->value("CourseName").toString().toLocal8Bit().data(),30);
        studentCourseScorePackage[i].CourseScore=query->value("Score").toInt();
        i++;
        qDebug()<<studentCourseScorePackage[i].CourseID<<studentCourseScorePackage[i].CourseName<<studentCourseScorePackage[i].CourseScore;

    }
    return studentCourseScorePackage;
}
student_course_package* SqlServer::FindStuSelectedCourseInfo(QString StuID, int type, int *cont){
    QString str;
    if(type==0)//查询全部选修课信息
        str=QString("select * from selectedCourseInfo");
    else if(type==1)//通识课
        str=QString("select * from selectedCourseInfo where courseTypeName='通识课'");
    else if(type==2)//实践课
        str=QString("select * from selectedCourseInfo where courseTypeName='实践课'");
    else if(type==3)//英语课
        str=QString("select * from selectedCourseInfo where courseTypeName='英语课'");
    else if(type==4)//体育课
        str=QString("select * from selectedCourseInfo where courseTypeName='体育课'");
    query->exec(str);
    int num=query->numRowsAffected();
    *cont=num;
    qDebug()<<"num:"<<num;
    student_course_package* studentCoursePackage;
    studentCoursePackage=(student_course_package*)malloc(sizeof(student_course_package)*num);
    int i=0;
    while(query->next()){
        strncpy(studentCoursePackage[i].CourseID,query->value("CourseID").toString().toLocal8Bit().data(),10);
        strncpy(studentCoursePackage[i].CourseName,query->value("CourseName").toString().toLocal8Bit().data(),30);
        strncpy(studentCoursePackage[i].CourseTypeName,query->value("CourseTypeName").toString().toLocal8Bit().data(),20);
        strncpy(studentCoursePackage[i].TchName,query->value("TeacherName").toString().toLocal8Bit().data(),20);
        studentCoursePackage[i].CourseCredit=query->value("CourseCredit").toInt();
        studentCoursePackage[i].CourseLimitNum=query->value("CourseLimitNum").toInt();
        studentCoursePackage[i].StuNum=query->value("StuNum").toInt();

        QString str1=QString("select * from stuCourseInfo where StuID='%1'and CourseID='%2'").arg(StuID).arg(studentCoursePackage[i].CourseID);
        query2->exec(str1);
        int num=query2->numRowsAffected();
        if(num==1)
            studentCoursePackage[i].isSelected=true;
        else
            studentCoursePackage[i].isSelected=false;
        i++;
    }
    return studentCoursePackage;
}
