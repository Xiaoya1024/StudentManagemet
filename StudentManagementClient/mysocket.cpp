#include "mysocket.h"
#include "ui_mysocket.h"
#include<QGraphicsOpacityEffect>

MySocket::MySocket(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MySocket)
{
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    effect->setOpacity(0.9);

    ui->setupUi(this);
    //设置密码格式
    ui->lineEditUserPwd->setEchoMode(QLineEdit::Password);

    tcpSocket=new QTcpSocket(this);
    tcpSocket->abort();//取消已有的连接
    tcpSocket->connectToHost(ip,port);

    connect(tcpSocket,&QTcpSocket::connected,
            [=](){
        qDebug()<<"Link successful";
    });

    //发生错误时执行displayError函数
    connect(tcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));
    //连接好之后准备接收服务器发来下的数据
    connect(tcpSocket,SIGNAL(readyRead()),this,SLOT(readMessages()));

    ui->lineEditUserID->setGraphicsEffect(effect);
    ui->textBrowser->setGraphicsEffect(effect);

}

MySocket::~MySocket()
{
    delete ui;
}

void MySocket::displayError(QAbstractSocket::SocketError){
    qDebug()<<tcpSocket->errorString();//输出错误信息
}

void MySocket::readMessages(){//接收服务器那边发来的消息
    response_header  res;
    tcpSocket->read((char *)&res,sizeof(response_header));
    //根据响应判断
    student_courseScore_package *cs;
     student_courseScoreInfo_package *s1;
    switch(res.statu)
    {
        case 0x00:{//登陆失败
            qDebug()<<"登录失败";
            QMessageBox::information(this,"warning","Fail!!",QMessageBox::Ok);}
            break;
        case 0x01:{//登陆成功
            qDebug()<<"登录成功";
            if(res.length==0){
                this->hide();
                //接受信息包和头像
                user_simple_package myInfo;
                tcpSocket->read((char *)&myInfo,sizeof(user_simple_package));
                qDebug()<<"接受完信息报";

                student=new StudentWindow();
                student->tcpSocket=tcpSocket;
                student->GetInfo(myInfo);
                student->GetImg();
                student->show();
            }
            if(res.length==4){
                this->hide();
                manager=new ManagerWindow();
                manager->tcpSocket=tcpSocket;
                manager->show();
            }}
            break;
         case 0x02:{
            user_full_package myInfo;
            tcpSocket->read((char *)&myInfo,sizeof(user_full_package));
            qDebug()<<"接受完完整信息报";
            student->GetInfo2(myInfo);}
            break;
         case 0x03:{
            qDebug()<<"接受课程信息";
            student_course_package mycourse;
            for(int i=0;i<res.length;i++){
                tcpSocket->read((char *)&mycourse,sizeof(student_course_package));
                student->GetCourse(mycourse);
            }
        }
        break;
         case 0x04:{
            qDebug()<<"接受成绩信息"<<res.length;
            student_courseScore_package myscore;
            for(int i=0;i<res.length;i++){
                tcpSocket->read((char *)&myscore,sizeof(student_courseScore_package));
                student->GetScore(myscore);
            }}
            break;
        case 0x05:{
            qDebug()<<"接受选修课信息";
            student_course_package myscourse;
            for(int i=0;i<res.length;i++){
                tcpSocket->read((char *)&myscourse,sizeof(student_course_package));
                student->GetSelectCourse(myscourse);
                qDebug()<<myscourse.CourseID<<myscourse.CourseName<<myscourse.TchName<<
                          myscourse.CourseCredit<<myscourse.CourseTypeName<<myscourse.CourseLimitNum
                       <<myscourse.StuNum<<myscourse.isSelected;

            }
        }
        break;
       case 0x06:{
            qDebug()<<"接受选课是否成功信息";
            if(res.length){
                 qDebug()<<"选课成功";
                 QMessageBox::information(this,"warning","Success!!",QMessageBox::Ok);
            }else{
                 qDebug()<<"选课失败";
                 QMessageBox::information(this,"warning","Fail!!",QMessageBox::Ok);
            }}
            break;
       case 0x07:{
            qDebug()<<"修改密码是否成功信息";
            if(res.length){
                 qDebug()<<"修改密码成功";
                 QMessageBox::information(this,"warning","Success!!",QMessageBox::Ok);
             }else{
                 qDebug()<<"修改密码s失败";
                 QMessageBox::information(this,"warning","Fail!!",QMessageBox::Ok);
             }}
             break;

       case 0x08:
            qDebug()<<"接受学院信息";
            InstituteInfo_package info;
            for(int i=0;i<res.length;i++){
                tcpSocket->read((char *)&info,sizeof(info));
                manager->GetInstituteInfo(info);
            }
            break;

      case 0x09:
            qDebug()<<"接受某个学院信息";
            ClassInfo_package classInfo;
            for(int i=0;i<res.length;i++){
                tcpSocket->read((char *)&classInfo,sizeof(classInfo));
                manager->GetClassInfo(classInfo);
            }
            break;
      case 0x0A:
            qDebug()<<"接受某个班信息";
           user_full_package classStuInfo;
            for(int i=0;i<res.length;i++){
                    tcpSocket->waitForReadyRead(20);
                    qint64 x= tcpSocket->read((char *)&classStuInfo,sizeof(user_full_package));
                     qDebug()<<x;
                     manager->GetClassStuInfo(classStuInfo);
            }
            break;
      case 0x0B:
            qDebug()<<"查询课程信息";
            student_course_package c1;
            for(int i=0;i<res.length;i++){
                    tcpSocket->waitForReadyRead(20);
                    qint64 x= tcpSocket->read((char *)&c1,sizeof(student_course_package));
                     qDebug()<<x;
                     manager->GetCourseInfo(c1);
            }
            break;
      case 0x0C:
            qDebug()<<"查询选课学生22"<<res.length;
            user_mid_package  c2;
            for(int i=0;i<res.length;i++){
                    tcpSocket->waitForReadyRead(20);
                    qint64 x= tcpSocket->read((char *)&c2,sizeof(user_mid_package));
                     qDebug()<<x;
                     manager->GetCourseStu(c2);
            }
           break;
       case 0x0D:
            qDebug()<<"查询课程"<<res.length;
            cs=(student_courseScore_package *)malloc(sizeof(student_courseScore_package)*res.length);
            manager->ss=cs;
            for(int i=0;i<res.length;i++){
                     qint64 x= tcpSocket->read((char *)&cs[i],sizeof(student_courseScore_package));
                      qDebug()<<x;
                     manager->GetCourseScore(cs[i]);
            }

            break;
       case 0x0E:
            qDebug()<<"导出成绩"<<res.length;
           s1=(student_courseScoreInfo_package *)malloc(res.length*sizeof(student_courseScoreInfo_package));
             for(int i=0;i<res.length;i++){
                    tcpSocket->waitForReadyRead(20);
                    qint64 x= tcpSocket->read((char *)&s1[i],sizeof(student_courseScoreInfo_package));
                     qDebug()<<s1[i].StuName<<x;


            }
            manager->GetCourseScore2(s1,res.length);
            break;
       case 0x0F:
            qDebug()<<"导入成绩是否成功";
            if(res.length){
                QMessageBox::information(this,"warning","Success!!",QMessageBox::Ok);
                manager->GetLabelin(-1);

            }else{
                QMessageBox::information(this,"warning","Fail!!",QMessageBox::Ok);
                manager->GetLabelin(-2);
            }
             break;
       case 0x10:
            qDebug()<<"班级信息";
             manager->cla=(class_Info_Package*)malloc(sizeof(class_Info_Package)*res.length);
             for(int i=0;i<res.length;i++){
                    tcpSocket->waitForReadyRead(20);
                    qint64 x= tcpSocket->read((char *)&manager->cla[i],sizeof(class_Info_Package));
                     qDebug()<<manager->cla[i].ClassName<<x;
            }
             manager->GetClassLabel(res.length);

           break;
       case 0x11:
        if(res.length){
            QMessageBox::information(this,"warning","Success!!",QMessageBox::Ok);

        }else{
            QMessageBox::information(this,"warning","Fail!!",QMessageBox::Ok);
        }
        break;
    case 0x12:
     if(res.length){
         QMessageBox::information(this,"warning","Success!!",QMessageBox::Ok);

     }else{
         QMessageBox::information(this,"warning","Fail!!",QMessageBox::Ok);
     }
        break;

    }

}
//登陆窗口
void MySocket::on_pushButtonLogin_clicked()
{
    //获取表单内容
    QString userID=ui->lineEditUserID->text();
    //qDebug()<<userID;
    QString userPwd=ui->lineEditUserPwd->text();
    //清空表单
    ui->lineEditUserID->clear();
    ui->lineEditUserPwd->clear();

    if(userID.isEmpty()||userPwd.isEmpty())
    {
        qDebug()<<"Error :Can't be empty!";
        QMessageBox::information(this,"Warning","Can't be empty!",QMessageBox::Ok);
    }
    else{
        //首先发送请求报文
        client_header loginReq;
        loginReq.cmdType=0x00;
        loginReq.length=sizeof(login_package);

        tcpSocket->write((char*)&loginReq,sizeof(client_header));

        //发送登陆包
        login_package loginP;
        char*  ch;
        QByteArray ba;
        ba= userID.toLatin1();
        ch=ba.data();
        strncpy(loginP.userID,ch,20);
        //strncpy(loginP.userID,userID.toStdString().c_str(),20);

        ba = userPwd.toLatin1();
        ch=ba.data();
        strncpy(loginP.password,ch,20);
        //qDebug()<<loginP.userID;
        tcpSocket->write((char*)&loginP,sizeof(login_package));
    }

}

void MySocket::on_pushButton_clicked()
{
    /*QString fileName = QFileDialog::getOpenFileName(this, tr("Excel file"), qApp->applicationDirPath (),
          tr("Files (*.csv)"));
        QFile file(fileName);

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
         {
            qDebug()<< "Cannot open file for reading: ";
            return;
         }

         QStringList list;
         list.clear();
         QTextStream in(&file);
         int i=-1;
         student_courseScoreInfo_package *s;
         while(!in.atEnd())
         {
             if(i==-1){
                 i++;
                 continue;
             }
             //  s=(student_courseScoreInfo_package*)malloc((i+1)*sizeof(student_courseScoreInfo_package));
            QString fileLine = in.readLine();
            list = fileLine.split(QRegExp("[,\"\t]"), QString::SkipEmptyParts);

                qDebug()<<"0"<<list.at(0);
               qDebug()<<"1"<<list.at(2);
                qDebug()<<"2"<<list.at(4);
               /* char*  ch;
                QByteArray ba;
                QString str;
                str=list.at(0);
                ba=str.toLatin1();
                ch=ba.data();
                strncpy(s[i].StuID,ch,10);

                str=list.at(2);
                ba=str.toLatin1();
                ch=ba.data();
                strncpy(s[i].CourseID,ch,10);

                str=list.at(4);
                s[i].CourseScore=str.toInt();

            i++;
         }
             file.close();*/

    /*QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
    tr("Files (*.csv)"));
    if (fileName.isEmpty())
     return;
     //打开.csv文件
     QFile file(fileName);
     if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
     {
    return;
     }

    QTextStream out(&file);
     out << tr("1,") << tr("2,")<< tr("3,") << tr("4,") <<",\n";//表头
     file.close();*/
}
