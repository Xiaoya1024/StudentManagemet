#include "mysqlserver.h"

SqlServer::SqlServer()
{

}
void SqlServer::InitSql(){
    //添加SqlServer数据库
    db=QSqlDatabase::addDatabase("QODBC");
    qDebug()<<"ODBC driver?"<<db.isValid();
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
    不会显示删除这个按钮，这样用户就不除数据了。
    */
    //数据库用户名
    db.setUserName("sa");
    //数据库密码
    db.setPassword("123456");
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
        qDebug()<<db.lastError().text();
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
    QString str=QString("select * from stuCourseInfo where StuID='%1'and Score is not NULL").arg(StuID);
    qDebug()<<str;
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
        str=QString("select * from selectedCourseInfo where courseTypeID='01'");
    else if(type==2)//实践课
        str=QString("select * from selectedCourseInfo where courseTypeID='02'");
    else if(type==3)//英语课
        str=QString("select * from selectedCourseInfo where courseTypeID='03'");
    else if(type==4)//体育课
        str=QString("select * from selectedCourseInfo where courseTypeID='04'");
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
        int num1=query2->numRowsAffected();
        qDebug()<<"这个课是否已经选过？1：已选，0：未选"<<num1;
        if(num1==1)
            studentCoursePackage[i].isSelected=true;//说明已经选过这门课
        else
            studentCoursePackage[i].isSelected=false;//说明还没有选这门课
        i++;
    }
    return studentCoursePackage;
}
bool SqlServer::isStuSelectedCourseSucced(QString StuID, QString CourseID){

    query->prepare("exec p_checkinsert ?,?,?");
    query->bindValue(0,StuID);
    query->bindValue(1,CourseID);
    query->bindValue(2,1,QSql::Out);
    bool isOk=query->exec();
    qDebug()<<"是否执行成功isOk："<<isOk;
    int num=query->boundValue(2).toInt();
    qDebug()<<"num:"<<num;
    if(num==1){
        QString str=QString("insert into ScoreTable values('%1','%2',NULL)").arg(StuID).arg(CourseID);
        qDebug()<<str;
        query2->exec(str);
        qDebug()<<"进入到里面";
        return true;
    }
    else return false;
}
bool SqlServer::ChangePwd(QString UserID, QString Pwd){
    QString str=QString("update UserTable Set UserPwd='%1' where UserID='%2'").arg(Pwd).arg(UserID);
    bool isOk=query->exec(str);
    return isOk;
}
InstituteInfo_package* SqlServer::FindInstituteInfo(int *cont){
    QString str=QString("select * from InstituteInfo");
    query->exec(str);
    *cont=query->numRowsAffected();
    qDebug()<<"学院的个数："<<*cont;
    InstituteInfo_package* instituteInfoPackage;
    instituteInfoPackage=(InstituteInfo_package*)malloc(sizeof(InstituteInfo_package)*(*cont));
    int i=0;
    while (query->next()) {
        strncpy(instituteInfoPackage[i].InstituteID,query->value("InstituteID").toString().toLocal8Bit().data(),10);
        strncpy(instituteInfoPackage[i].InstituteName,query->value("InstitueName").toString().toLocal8Bit().data(),30);
        strncpy(instituteInfoPackage[i].AssistantName,query->value("AssistantName").toString().toLocal8Bit().data(),20);
        instituteInfoPackage[i].StuNum=query->value("stuNum").toInt();
        i++;
    }
    return instituteInfoPackage;
}
ClassInfo_package* SqlServer::FindClassInfo(QString InstituteID, int *cont){
    QString str=QString("Select * from classInfo where InstituteID='%1'").arg(InstituteID);
    query->exec(str);
    *cont=query->numRowsAffected();
    qDebug()<<"这个学院里的班级数目："<<*cont;
    ClassInfo_package* classInfoPackage;
    classInfoPackage=(ClassInfo_package*)malloc(sizeof(ClassInfo_package)*(*cont));
    int i=0;
    while (query->next()) {
        strncpy(classInfoPackage[i].ClassID,query->value("ClassID").toString().toLocal8Bit().data(),10);
        strncpy(classInfoPackage[i].ClassName,query->value("ClassName").toString().toLocal8Bit().data(),30);
        strncpy(classInfoPackage[i].MasterName,query->value("MasterName").toString().toLocal8Bit().data(),20);
        strncpy(classInfoPackage[i].MonitorName,query->value("MonitorName").toString().toLocal8Bit().data(),20);
        classInfoPackage[i].StuNum=query->value("StuNum").toInt();
        i++;
    }
    return classInfoPackage;
}
user_full_package* SqlServer::FindStuInfoInClass(QString ClassID, int *cont){
    QString str=QString("select * from stuFullInfo where ClassID='%1'").arg(ClassID);
    query->exec(str);
    *cont=query->numRowsAffected();
    qDebug()<<"这个班级的学生人数："<<*cont;
    user_full_package* stuInfoInClass;
    stuInfoInClass=(user_full_package*)malloc(sizeof(user_full_package)*(*cont));
    int i=0;
    while(query->next()){
        strncpy(stuInfoInClass[i].userID,query->value("StuID").toString().toLocal8Bit().data(),10);
        strncpy(stuInfoInClass[i].userName,query->value("StuName").toString().toLocal8Bit().data(),20);
        strncpy(stuInfoInClass[i].userInstituteName,query->value("InstitueName").toString().toLocal8Bit().data(),30);
        strncpy(stuInfoInClass[i].userClassName,query->value("ClassName").toString().toLocal8Bit().data(),30);
        strncpy(stuInfoInClass[i].userAssistantName,query->value("AssistantName").toString().toLocal8Bit().data(),20);
        strncpy(stuInfoInClass[i].usermasterName,query->value("MasterName").toString().toLocal8Bit().data(),20);
        stuInfoInClass[i].userGender=query->value("StuGender").toBool();
        strncpy(stuInfoInClass[i].userCardID,query->value("StuCardID").toString().toLocal8Bit().data(),20);
        QString str1=stuInfoInClass[i].userCardID;
        strncpy(stuInfoInClass[i].userBirthDay,QString(str1.mid(6,8)).toLocal8Bit().data(),10);
        stuInfoInClass[i].userAge=2018-str1.mid(6,4).toInt();
        strncpy(stuInfoInClass[i].userNativePlace,query->value("StuNativePlace").toString().toLocal8Bit().data(),50);
        strncpy(stuInfoInClass[i].userNationality,query->value("StuNationality").toString().toLocal8Bit().data(),50);
        i++;
    }
    return stuInfoInClass;
}
student_course_package* SqlServer::FindAllCourseInfo(int *cont,int type){
    QString str;
    if(type==0)//查询全部选修课信息
        str=QString("select * from selectedCourseInfo");
    else if(type==1)//通识课
        str=QString("select * from selectedCourseInfo where courseTypeID='01'");
    else if(type==2)//实践课
        str=QString("select * from selectedCourseInfo where courseTypeID='02'");
    else if(type==3)//英语课
        str=QString("select * from selectedCourseInfo where courseTypeID='03'");
    else if(type==4)//体育课
        str=QString("select * from selectedCourseInfo where courseTypeID='04'");
    else if(type==5)//专业课
        str=QString("select * from selectedCourseInfo where courseTypeID='05'");
    query->exec(str);
    int num=query->numRowsAffected();
    *cont=num;
    qDebug()<<"课程的个数："<<num;
    student_course_package* courseAllInfo;
    courseAllInfo=(student_course_package*)malloc(sizeof(student_course_package)*num);
    int i=0;
    while(query->next()){
        strncpy(courseAllInfo[i].CourseID,query->value("CourseID").toString().toLocal8Bit().data(),10);
        strncpy(courseAllInfo[i].CourseName,query->value("CourseName").toString().toLocal8Bit().data(),30);
        strncpy(courseAllInfo[i].CourseTypeName,query->value("CourseTypeName").toString().toLocal8Bit().data(),20);
        strncpy(courseAllInfo[i].TchName,query->value("TeacherName").toString().toLocal8Bit().data(),20);
        courseAllInfo[i].CourseCredit=query->value("CourseCredit").toInt();
        courseAllInfo[i].CourseLimitNum=query->value("CourseLimitNum").toInt();
        courseAllInfo[i].StuNum=query->value("StuNum").toInt();
        i++;
    }
    return courseAllInfo;
}
user_mid_package* SqlServer::FindStuInfoInCourse(QString CourseID, int *cont){
    QString str=QString("select * from stuFullInfo,stuCourseInfo where stuFullInfo.StuID=stuCourseInfo.StuID and CourseID='%1'").arg(CourseID);
    query->exec(str);
    *cont=query->numRowsAffected();
    qDebug()<<"选这门课的学生人数："<<*cont;
    user_mid_package* stuInfoInCourse;
    stuInfoInCourse=(user_mid_package*)malloc(sizeof(user_mid_package)*(*cont));
    int i=0;
    while(query->next()){
       strncpy(stuInfoInCourse[i].userID,query->value("StuID").toString().toLocal8Bit().data(),10);
       strncpy(stuInfoInCourse[i].userName,query->value("StuName").toString().toLocal8Bit().data(),20);
       strncpy(stuInfoInCourse[i].userInstituteName,query->value("InstitueName").toString().toLocal8Bit().data(),30);
       strncpy(stuInfoInCourse[i].userClassName,query->value("ClassName").toString().toLocal8Bit().data(),30);
       stuInfoInCourse[i].userGender=query->value("StuGender").toBool();
       i++;
    }
    return stuInfoInCourse;
}
student_courseScore_package* SqlServer::FindAllCourseInfoToScore(int *cont){
    QString str=QString("select * from selectedCourseInfo");
    query->exec(str);
    int num=query->numRowsAffected();
    *cont=num;
    qDebug()<<"课程的个数："<<num;
    student_courseScore_package* courseInfoToScore;
    courseInfoToScore=(student_courseScore_package*)malloc(sizeof(student_courseScore_package)*num);
    int i=0;
    while (query->next()) {
        strncpy(courseInfoToScore[i].CourseID,query->value("CourseID").toString().toLocal8Bit().data(),10);
        strncpy(courseInfoToScore[i].CourseName,query->value("CourseName").toString().toLocal8Bit().data(),30);
        i++;
    }
    return courseInfoToScore;
}
student_courseScoreInfo_package* SqlServer::FindStuScoreOfCourse(QString CourseID, int *cont){
    QString str=QString("select * from stuCourseInfo where CourseID='%1'").arg(CourseID);
    qDebug()<<"str:"<<str;
    query->exec(str);
    *cont=query->numRowsAffected();
    qDebug()<<"学生人数："<<*cont;
    student_courseScoreInfo_package* stuCourseScoreInfo;
    stuCourseScoreInfo=(student_courseScoreInfo_package*)malloc(sizeof(student_courseScoreInfo_package)*(*cont));
    int i=0;
    while (query->next()) {
        strncpy(stuCourseScoreInfo[i].StuID,query->value("StuID").toString().toLocal8Bit().data(),10);
        strncpy(stuCourseScoreInfo[i].StuName,query->value("StuName").toString().toLocal8Bit().data(),20);
        strncpy(stuCourseScoreInfo[i].CourseID,query->value("CourseID").toString().toLocal8Bit().data(),10);
        strncpy(stuCourseScoreInfo[i].CourseName,query->value("CourseName").toString().toLocal8Bit().data(),30);
        stuCourseScoreInfo[i].CourseScore=query->value("Score").toInt();
        qDebug()<<stuCourseScoreInfo[i].StuID<<stuCourseScoreInfo[i].StuName
               <<stuCourseScoreInfo[i].CourseID<<stuCourseScoreInfo[i].CourseName;
        i++;
    }
    return stuCourseScoreInfo;
}
bool SqlServer::UpdateStuScoreOfCourse(QString StuID, QString CourseID, int Score){

    db.transaction();
    QString str=QString("update stuCourseInfo set Score='%1' where StuID='%2' and CourseID='%3'").arg(Score).arg(StuID).arg(CourseID);
    bool isOk=query->exec(str);
    if(isOk){

        db.commit();
        return true;
    }
    else{
        db.rollback();
        return false;
    }

}
class_Info_Package* SqlServer::FindAllClassInfo(int *cont){
    QString str=QString("select * from classInfo");
    query->exec(str);
    *cont=query->numRowsAffected();
    class_Info_Package* classInfoPackage;
    classInfoPackage=(class_Info_Package*)malloc(sizeof(class_Info_Package)*(*cont));
    int i=0;
    while(query->next()){
        strncpy(classInfoPackage[i].ClassID,query->value("ClassID").toString().toLocal8Bit().data(),10);
        strncpy(classInfoPackage[i].ClassName,query->value("ClassName").toString().toLocal8Bit().data(),30);
        i++;
    }
    return classInfoPackage;
}
bool SqlServer::addStuInfo(add_stu_package*addStuPackage){
    QString str=QString("insert into StudentTable values('%1','%2','%3','../1.jpg','%4','%5','%6',1)")
            .arg(addStuPackage->stuID).arg(addStuPackage->stuName).arg(addStuPackage->userGender)
            .arg(addStuPackage->userNativePlace).arg(addStuPackage->userNationality)
            .arg(addStuPackage->userCardID);
   QString str1=QString("insert into StuClassTable values('%1','%2')").arg(addStuPackage->stuID).arg(addStuPackage->stuClassID);
   qDebug()<<addStuPackage->stuName<<addStuPackage->userNationality<<addStuPackage->userNativePlace;
   db.transaction();
   bool isOk1=query->exec(str);
   bool isOk2=query2->exec(str1);
   if(isOk1&&isOk2){
       db.commit();
       return true;
   }
   else{
       db.rollback();
       return false;
   }
}
bool SqlServer::deleteStu(QString StuID){
    query->prepare("exec deleteStu ?,?");
    query->bindValue(0,StuID);
    query->bindValue(1,1,QSql::Out);
    bool isOk=query->exec();
    qDebug()<<"是否执行成功？"<<isOk;
    int num=query->boundValue(1).toInt();
    qDebug()<<"num:"<<num;
    if(num==1){
        qDebug()<<"学生删除成功！";
        return true;
    }
    else{
        return false;
    }
}
