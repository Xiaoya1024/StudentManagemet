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
    student_course_package* stuCoursePackage;
    student_courseScore_package* stuCourseScorePackage;

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
            userSimplePackage=sqlServer.FindUserSimpleInfo(userID,userType);
            write((char*)&userSimplePackage,sizeof(user_simple_package));

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
        stuCoursePackage=sqlServer.FindStuSelectedCourseInfo(userID,type,&num);
        qDebug()<<"选修课的个数："<<num;
        responseHeader.statu=0x05;
        responseHeader.length=num;
        write((char*)&responseHeader,sizeof(response_header));
        qDebug()<<"successful";
        for(int i=0;i<num;i++){
            write((char*)&stuCoursePackage[i],sizeof(stuCoursePackage));
            qDebug()<<"选修课序号："<<stuCoursePackage[i].CourseID<<stuCoursePackage[i].CourseName<<stuCoursePackage[i].CourseCredit
                   <<stuCoursePackage[i].CourseTypeName<<stuCoursePackage[i].TchName<<stuCoursePackage[i].CourseLimitNum<<
                     stuCoursePackage[i].StuNum<<stuCoursePackage[i].isSelected;
        }
    }
        break;
    default:
        break;
    }
}

