#include "mysocket.h"

MySocket::MySocket(int socketDescriptor,QObject*parent)
    :QTcpSocket(parent),socketDescriptor(socketDescriptor)
{

}

//服务器收到用户发来的消息，进行解析和回复
void MySocket::slotRevData(){
    client_header clientHeader;
    login_package loginPackage;
    response_header responseHeader;
    user_simple_package userSimplePackage;
    user_full_package userFullPackage;
    user_full_package* stuInfoInClass;
    user_mid_package* stuInfoInCourse;
    student_course_package* stuCoursePackage;
    student_course_package* courseAllInfo;
    student_courseScore_package* stuCourseScorePackage;
    InstituteInfo_package* instituteInfoPackage;
    ClassInfo_package* classInfoPackage;
    student_courseScore_package* courseInfoToScore;
    student_courseScoreInfo_package* stuCourseScoreInfo;
    add_stu_package addStuPackage;
    class_Info_Package* classSimpleInfoPackage;

    read((char*)&clientHeader,sizeof(client_header));
    qDebug()<<clientHeader.cmdType<<clientHeader.length;
    qDebug()<<"socketDescriptor:"<<socketDescriptor;
    switch (clientHeader.cmdType) {
    case 0x00://登录请求
        {
        read((char*)&loginPackage,sizeof(login_package));
        int ok=sqlServer.checkLogin(loginPackage.userID,loginPackage.password);
        if(ok==-1){//登录失败
            responseHeader.statu=0x00;
            responseHeader.length=0;
            write((char*)&responseHeader,sizeof(response_header));
            qDebug()<<"fail";
        }
        else{//登录成功
            userType=ok;
            responseHeader.statu=0x01;
            responseHeader.length=ok;
            write((char*)&responseHeader,sizeof(response_header));
            qDebug()<<"successful";
            userID=loginPackage.userID;
            if(userType!=4){
                userSimplePackage=sqlServer.FindUserSimpleInfo(userID,userType);
                write((char*)&userSimplePackage,sizeof(user_simple_package));
                //发送图片信息
                waitForBytesWritten(10);
                QPixmap pix(tr(":/1.jpg"));
                QBuffer buffer;
                buffer.open(QIODevice::WriteOnly);
                pix.save(&buffer,"jpg",20);
                quint32 pix_len=(quint32)buffer.data().size();
                qDebug()<<"image size:"<<pix_len;
                QByteArray dataArray;
                dataArray.append(buffer.data());
                quint32 write_len=write(dataArray);
                qDebug()<<"write len:"<<write_len;
            }
        }
    }
        break;
    case 0x01://请求完整用户信息包
    {
        responseHeader.statu=0x02;
        responseHeader.length=0;
        write((char*)&responseHeader,sizeof(response_header));
        qDebug()<<"successful";

        if(userType==0){//如果是学生
            userFullPackage=sqlServer.FindUserFullInfo(userID,userType);
            write((char*)&userFullPackage,sizeof(user_full_package));
        }
    }
        break;
    case 0x02:{//学生请求已选的课程的信息
        int num=0;
        stuCoursePackage=sqlServer.FindStuCourseInfo(userID,&num);
        qDebug()<<"课程的个数："<<num;

        responseHeader.statu=0x03;
        responseHeader.length=num;//发送个数
        write((char*)&responseHeader,sizeof(response_header));
        qDebug()<<"successful";
        for(int i=0;i<num;i++){
            write((char*)&stuCoursePackage[i],sizeof(stuCoursePackage[i]));
            qDebug()<<"课程的序号数："<<stuCoursePackage[i].CourseName<<stuCoursePackage[i].CourseID<<stuCoursePackage[i].CourseCredit
                   <<stuCoursePackage[i].CourseTypeName<<stuCoursePackage[i].TchName;
        }
    }
        break;
    case 0x03:{//学生请求查看成绩
        int num=0;
        stuCourseScorePackage=sqlServer.FindStuCourseScoreInfo(userID,&num);
        qDebug()<<"已出成绩的课程个数："<<num;
        responseHeader.statu=0x04;
        responseHeader.length=num;
        write((char*)&responseHeader,sizeof(response_header));
        qDebug()<<"successful";
        for(int i=0;i<num;i++){
            write((char*)&stuCourseScorePackage[i],sizeof(student_courseScore_package));
            qDebug()<<"有成绩的课程序号数："<<stuCourseScorePackage[i].CourseID<<stuCourseScorePackage[i].CourseName<<stuCourseScorePackage[i].CourseScore;
        }
    }
        break;
    case 0x04:{//学生点击选课按钮，查看选修课信息
        int type=clientHeader.length;
        int num=0;
        stuCoursePackage=sqlServer.FindStuSelectedCourseInfo(userID,type,&num);//找到选修课的信息
        qDebug()<<"选修课的个数："<<num;
        responseHeader.statu=0x05;
        responseHeader.length=num;
        write((char*)&responseHeader,sizeof(response_header));
        qDebug()<<"successful";
        for(int i=0;i<num;i++){
            write((char*)&stuCoursePackage[i],sizeof(student_course_package));
            qDebug()<<"选修课序号："<<stuCoursePackage[i].CourseID<<stuCoursePackage[i].CourseName<<stuCoursePackage[i].CourseCredit
                   <<stuCoursePackage[i].CourseTypeName<<stuCoursePackage[i].TchName<<stuCoursePackage[i].CourseLimitNum<<
                     stuCoursePackage[i].StuNum<<stuCoursePackage[i].isSelected;
        }
    }
        break;
    case 0x05:{//学生点击某一门课进行选课
          student_courseScore_package stuCourseScorePag;
          read((char*)&stuCourseScorePag,sizeof(student_courseScore_package));
          qDebug()<<"点击的选课科目码："<<stuCourseScorePag.CourseID;
          bool isOk=sqlServer.isStuSelectedCourseSucced(userID,QString(stuCourseScorePag.CourseID));
          responseHeader.statu=0x06;
          if(isOk){//表示选课成功
              responseHeader.length=1;
          }
          else responseHeader.length=0;
          write((char*)&responseHeader,sizeof(response_header));
    }
        break;
    case 0x06:{//用户点击修改密码
        read((char*)&loginPackage,sizeof(login_package));
        bool isOk=sqlServer.ChangePwd(userID,loginPackage.password);
        if(isOk){
            responseHeader.length=1;
        }
        else responseHeader.length=0;
        responseHeader.statu=0x07;
        write((char*)&responseHeader,sizeof(response_header));
    }
        break;
    case 0x07:{//管理员点击学院查询
        int num=0;
        instituteInfoPackage=sqlServer.FindInstituteInfo(&num);
        responseHeader.statu=0x08;
        responseHeader.length=num;
        write((char*)&responseHeader,sizeof(response_header));
        for(int i=0;i<num;i++){
            write((char*)&instituteInfoPackage[i],sizeof(InstituteInfo_package));
            qDebug()<<"学院信息"<<i<<":"<<instituteInfoPackage[i].InstituteID<<instituteInfoPackage[i].InstituteName
                   <<instituteInfoPackage[i].AssistantName<<instituteInfoPackage[i].StuNum;
        }

    }
        break;
    case 0x08:{//管理员在学院查询那里点击了查看
        int len=clientHeader.length;
        char ID[10];
        read((char*)ID,len);
        QString instituteID(ID);
        qDebug()<<"instituteID:"<<instituteID;
        int num=0;
        classInfoPackage=sqlServer.FindClassInfo(instituteID,&num);
        responseHeader.statu=0x09;
        responseHeader.length=num;
        write((char*)&responseHeader,sizeof(response_header));
        for(int i=0;i<num;i++){
            write((char*)&classInfoPackage[i],sizeof(ClassInfo_package));
            qDebug()<<"班级信息"<<i<<":"<<classInfoPackage[i].ClassID<<classInfoPackage[i].ClassName
                   <<classInfoPackage[i].MasterName<<classInfoPackage[i].MonitorName<<classInfoPackage[i].StuNum;
        }

    }
        break;
    case 0x09:{//管理员在班级查询那里点了查看，查看该班级里的学生信息
        int len=clientHeader.length;//发给我的长度
        char ID[10];
        read((char*)ID,len);
        QString classID(ID);
        qDebug()<<"ClassID:"<<classID;
        int num=0;
        stuInfoInClass=sqlServer.FindStuInfoInClass(classID,&num);
        responseHeader.statu=0x0A;
        responseHeader.length=num;
        write((char*)&responseHeader,sizeof(response_header));
        for(int i=0;i<num;i++){
            waitForBytesWritten(10);//避免接收方收不完整
            qint64 x=write((char*)&stuInfoInClass[i],sizeof(user_full_package));
            qDebug()<<"发送的包的大小："<<x;
            qDebug()<<"学生名字："<<stuInfoInClass[i].userName;
        }
    }
        break;
    case 0x0A:{//管理员点击课程查询按钮，服务端返回所有的课程信息
        int num=0;
        int type=clientHeader.length;
        courseAllInfo=sqlServer.FindAllCourseInfo(&num,type);
        qDebug()<<"课程的个数："<<num;
        responseHeader.statu=0x0B;
        responseHeader.length=num;
        write((char*)&responseHeader,sizeof(response_header));
        for(int i=0;i<num;i++){
            write((char*)&courseAllInfo[i],sizeof(student_course_package));
            qDebug()<<"选修课序号："<<courseAllInfo[i].CourseID<<courseAllInfo[i].CourseName<<courseAllInfo[i].CourseCredit
                   <<courseAllInfo[i].CourseTypeName<<courseAllInfo[i].TchName<<courseAllInfo[i].CourseLimitNum<<
                     courseAllInfo[i].StuNum;
        }
    }
        break;
    case 0x0B:{//管理员点击某一个课程的查看信息，返回选择该课程的所有同学信息
        int len=clientHeader.length;
        char ID[10];
        read((char*)ID,len);
        QString CourseID(ID);
        qDebug()<<"CourseID"<<CourseID;
        int num=0;
        stuInfoInCourse=sqlServer.FindStuInfoInCourse(CourseID,&num);
        responseHeader.statu=0x0C;
        responseHeader.length=num;
        write((char*)&responseHeader,sizeof(response_header));
        for(int i=0;i<num;i++){
            write((char*)&stuInfoInCourse[i],sizeof(user_mid_package));
            qDebug()<<"学生名字："<<stuInfoInCourse[i].userName;
        }
    }
        break;
    case 0x0C:{//客户端点击成绩那里，反馈给客户端相应的课程信息
        int num;
        courseInfoToScore=sqlServer.FindAllCourseInfoToScore(&num);
        responseHeader.statu=0x0D;
        responseHeader.length=num;
        write((char*)&responseHeader,sizeof(response_header));
        for(int i=0;i<num;i++){
            write((char*)&courseInfoToScore[i],sizeof(student_courseScore_package));
            qDebug()<<"课程信息："<<courseInfoToScore[i].CourseID<<
                      courseInfoToScore[i].CourseName<<courseInfoToScore[i].CourseScore;
        }
    }
        break;
    case 0x0D:{//客户端导出成绩
        int len=clientHeader.length;
        char ID[10];
        read((char*)ID,len);
        QString CourseID(ID);
        qDebug()<<"CourseID"<<CourseID;
        int num=0;
        stuCourseScoreInfo=sqlServer.FindStuScoreOfCourse(CourseID,&num);
        responseHeader.statu=0x0E;
        responseHeader.length=num;
        write((char*)&responseHeader,sizeof(response_header));
        for(int i=0;i<num;i++){
            write((char*)&stuCourseScoreInfo[i],sizeof(student_courseScoreInfo_package));
            qDebug()<<"学生姓名："<<stuCourseScoreInfo[i].StuName;
        }
    }
        break;
    case 0x0E:{//客户端点击导入成绩
        int len=clientHeader.length;
        qDebug()<<"CSV文件长度："<<len;
        student_courseScoreInfo_package *stuCourseScoreInfo;
        stuCourseScoreInfo=(student_courseScoreInfo_package*)malloc(sizeof(student_courseScoreInfo_package)*len);
        bool OK=true;
        for(int i=1;i<len;i++){
            waitForReadyRead(20);
            read((char*)&stuCourseScoreInfo[i],sizeof(student_courseScoreInfo_package));
            qDebug()<<stuCourseScoreInfo[i].CourseID<<stuCourseScoreInfo[i].StuID<<stuCourseScoreInfo[i].CourseScore;
            bool isOk=sqlServer.UpdateStuScoreOfCourse(stuCourseScoreInfo[i].StuID,stuCourseScoreInfo[i].CourseID,stuCourseScoreInfo[i].CourseScore);
            if(!isOk){
                for(int k=i+1;k<len;k++){
                    read((char*)&stuCourseScoreInfo[i],sizeof(student_courseScoreInfo_package));
                }
                OK=false;
                break;
            }
            else qDebug()<<"插入成功";
        }
        responseHeader.statu=0x0F;
        if(OK){
            responseHeader.length=1;//成功
        }
        else
            responseHeader.length=0;
        write((char*)&responseHeader,sizeof(response_header));

    }
        break;
    case 0x0F:{//添加一个学生
        int num=0;
        classSimpleInfoPackage=sqlServer.FindAllClassInfo(&num);
        responseHeader.statu=0x10;
        responseHeader.length=num;
        write((char*)&responseHeader,sizeof(response_header));
        for(int i=0;i<num;i++){
            write((char*)&classSimpleInfoPackage[i],sizeof(class_Info_Package));
            qDebug()<<classSimpleInfoPackage[i].ClassName;
        }
    }
        break;
    case 0x10:{//接收发来的学生信息包
        read((char*)&addStuPackage,sizeof(add_stu_package));
        bool isOk=sqlServer.addStuInfo(&addStuPackage);
        responseHeader.statu=0x11;
        if(isOk){
            responseHeader.length=1;
            qDebug()<<"添加学生成功";
        }
        else{
            responseHeader.length=0;
             qDebug()<<"添加学生失败";
        }
        write((char*)&responseHeader,sizeof(response_header));
    }
        break;
    case 0x11:{//接收发来的将要删除的学号
        int len=clientHeader.length;
        char ID[10];
        read((char*)ID,len);
        QString StuID(ID);
        qDebug()<<"StuID:"<<StuID;
        bool isOk=sqlServer.deleteStu(StuID);
        responseHeader.statu=0x12;
        if(isOk)responseHeader.length=1;//删除成功
        else responseHeader.length=0;
        write((char*)&responseHeader,sizeof(response_header));
    }
        break;
    default:
        break;
    }
}

