#include "studentwindow.h"
#include "ui_studentwindow.h"


StudentWindow::StudentWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentWindow)
{
    ui->setupUi(this);
    ui->tableWidget_stuCourse->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tableWidget_stuScore->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_StuSelectCourse->setEditTriggers(QAbstractItemView::NoEditTriggers);

//    ui->tableWidget_stuCourse->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->tableWidget_stuScore->setSelectionBehavior(QAbstractItemView::SelectRows);
//    ui->tableWidget_StuSelectCourse->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableWidget_stuCourse->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_stuScore->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_StuSelectCourse->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableWidget_stuCourse->resizeColumnsToContents();



    // ui->label_Index_StuImg->setPixmap(QPixmap(":/new/prefix1/1.png").scaled(100,100));
   /*  QByteArray bytearray;
    QPixmap image(":/new/prefix1/1.png");
    QBuffer buffer(&bytearray);
       buffer.open(QIODevice::WriteOnly);
       bool bOk = image.save(&buffer,"PNG",20);
       QPixmap imageresult;//
          imageresult.loadFromData(bytearray);
          ui->label_Index_StuImg->setPixmap(imageresult.scaled(100,100));*/
}

StudentWindow::~StudentWindow()
{
    delete ui;
}
void StudentWindow::GetInfo(user_simple_package info){
    ui->stackedWidget->setCurrentIndex(0);
    QString str;
    str=QString::fromLocal8Bit(info.userID);
    ui->label_Index_StuID->setText(str);
    //str=QString::fromLocal8Bit(info.userName);
    qDebug()<<"name"<<info.userName;
    ui->label_Index_StuName->setText(info.userName);
}
void StudentWindow::GetImg()
{
   qDebug()<<"accept a connection!"<<endl;
       QByteArray array;
       while(tcpSocket->waitForReadyRead(10)){
           qDebug()<<"bytesAvailable";

           array.append((QByteArray)tcpSocket->readAll());
       }
        qDebug()<<"array"<<array.size();

      /* QBuffer buffer(&array);
       buffer.open(QIODevice::ReadOnly);

       QImageReader reader(&buffer,"JPG");
       QImage img = reader.read();*/

      // if(!img.isNull()){
        if(array.size()>0){
           qDebug()<<"right"<<endl;
           QPixmap pix; //= QPixmap::fromImage(img);
           pix.loadFromData(array);
           ui->label_Index_StuImg->setPixmap(pix.scaled(ui->label_Index_StuImg->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
           ui->label_Info_StuImg->setPixmap(pix.scaled(ui->label_Info_StuImg->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
       } else {
           qDebug()<<"error"<<endl;
       }
   // ui->label_Index_StuImg->setPixmap(QPixmap(":/new/prefix1/1.jpg").scaled(100,150));
   // ui->label_Info_StuImg->setPixmap(QPixmap(":/new/prefix1/1.jpg").scaled(100,150));
}
//完整信息
void StudentWindow::GetInfo2(user_full_package info){

    QString str;
    str=ui->label_Index_StuID->text();
    ui->label_Info_StuID->setText(str);

    str=ui->label_Index_StuName->text();
    ui->label_Info_StuName->setText(str);

    ui->label_Info_StuInstitute->setText(info.userInstituteName);
    qDebug()<<"学院姓名"<<info.userInstituteName;
    ui->label_Info_StuClass->setText(info.userClassName);
     qDebug()<<"班级姓名"<<info.userClassName;
    ui->label_Info_StuAssistant->setText(info.userAssistantName);
    ui->label_Info_StuMaster->setText(info.usermasterName);

    if(info.userGender==true){
        ui->label_Info_StuSex->setText("男");
    }
    else{
        ui->label_Info_StuSex->setText("女");
    }
    ui->label_Info_StuAge->setText(QString::number(info.userAge));

    str=QString::fromLocal8Bit(info.userBirthDay);
    ui->label_Info_StuBirthDay->setText(str);
    str=QString::fromLocal8Bit(info.userCardID);
    ui->label_Info_StuCardID->setText(str);

    ui->label_Info_StuNationality->setText(info.userNationality);
    ui->label_Info_StuNativePlace->setText(info.userNativePlace);

}
//查询课程信息
void StudentWindow::GetCourse(student_course_package mycourse)
{
    int row=ui->tableWidget_stuCourse->rowCount();
    ui->tableWidget_stuCourse->setRowCount(row+1);
    qDebug()<<mycourse.CourseID<<mycourse.CourseName<<mycourse.TchName<<
              mycourse.CourseCredit<<mycourse.CourseTypeName;
    ui->tableWidget_stuCourse->setItem(row,0,new QTableWidgetItem(mycourse.CourseID));
    ui->tableWidget_stuCourse->setItem(row,1,new QTableWidgetItem(mycourse.CourseName));
    ui->tableWidget_stuCourse->setItem(row,2,new QTableWidgetItem(mycourse.TchName));
    ui->tableWidget_stuCourse->setItem(row,4,new QTableWidgetItem(mycourse.CourseTypeName));
    ui->tableWidget_stuCourse->setItem(row,3,new QTableWidgetItem(QString::number(mycourse.CourseCredit)));

}
//查看成绩
void StudentWindow::GetScore(student_courseScore_package myscore)
{
    int row=ui->tableWidget_stuScore->rowCount();
    ui->tableWidget_stuScore->setRowCount(row+1);
    qDebug()<<myscore.CourseID<<myscore.CourseName<<myscore.CourseScore;

    ui->tableWidget_stuScore->setItem(row,0,new QTableWidgetItem(myscore.CourseID));
    ui->tableWidget_stuScore->setItem(row,1,new QTableWidgetItem(myscore.CourseName));
    ui->tableWidget_stuScore->setItem(row,2,new QTableWidgetItem(QString::number(myscore.CourseScore)));
}
//选课
 void StudentWindow::GetSelectCourse(student_course_package mycourse)
 {
     int row=ui->tableWidget_StuSelectCourse->rowCount();
     ui->tableWidget_StuSelectCourse->setRowCount(row+1);
     qDebug()<<mycourse.CourseID<<mycourse.CourseName<<mycourse.TchName<<
               mycourse.CourseCredit<<mycourse.CourseTypeName<<mycourse.CourseLimitNum
            <<mycourse.StuNum<<mycourse.isSelected;

     ui->tableWidget_StuSelectCourse->setItem(row,0,new QTableWidgetItem(mycourse.CourseID));
     ui->tableWidget_StuSelectCourse->setItem(row,1,new QTableWidgetItem(mycourse.CourseName));
     ui->tableWidget_StuSelectCourse->setItem(row,2,new QTableWidgetItem(mycourse.TchName));
     ui->tableWidget_StuSelectCourse->setItem(row,3,new QTableWidgetItem(QString::number(mycourse.CourseCredit)));
     ui->tableWidget_StuSelectCourse->setItem(row,4,new QTableWidgetItem(mycourse.CourseTypeName));
     ui->tableWidget_StuSelectCourse->setItem(row,5,new QTableWidgetItem(QString::number(mycourse.CourseLimitNum)));
     ui->tableWidget_StuSelectCourse->setItem(row,6,new QTableWidgetItem(QString::number(mycourse.StuNum)));
     if(mycourse.isSelected){//已选
         ui->tableWidget_StuSelectCourse->setItem(row,7,new QTableWidgetItem("已选"));
     }else{
         ui->tableWidget_StuSelectCourse->setItem(row,7,new QTableWidgetItem("选课"));
     }

 }

//查看更多
void StudentWindow::on_label_Index_StuLearnMore_linkActivated(const QString &link)
{
    //首先发送请求报文
   //ui->stackedWidget->setCurrentIndex(1);

   /* client_header getInfoReq;
    getInfoReq.cmdType=0x01;
    getInfoReq.length=sizeof(client_header);

    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));

    user_full_package myInfo;
    tcpSocket->read((char *)&myInfo,sizeof(user_full_package));
    qDebug()<<"接受完完整信息报";
    GetInfo2(myInfo);*/
}

//完整信息
void StudentWindow::on_buttonStuInfo_triggered()
{
    //首先发送请求报文
    client_header getInfoReq;
    getInfoReq.cmdType=0x01;
    getInfoReq.length=sizeof(client_header);

    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));
    ui->stackedWidget->setCurrentIndex(1);
}
//查询已选课程
void StudentWindow::on_buttonStuCourse_triggered()
{
   // QStringList headers;
  //  headers<< QStringLiteral("CourseID") << QStringLiteral("CourseName")<< QStringLiteral("TchName")<< QStringLiteral("CourseCredit")<< QStringLiteral("CourseTypeName");
  //  ui->tableWidget_stuCourse->setHorizontalHeaderLabels(headers);
    //首先发送请求报文
    client_header getInfoReq;
    getInfoReq.cmdType=0x02;
    getInfoReq.length=sizeof(client_header);

    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));
    ui->stackedWidget->setCurrentIndex(3);
    ui->tableWidget_stuCourse->clearContents();
    ui->tableWidget_stuCourse->setRowCount(0);
}
//查询成绩
void StudentWindow::on_buttonStuScore_triggered()
{
    client_header getInfoReq;
    getInfoReq.cmdType=0x03;
    getInfoReq.length=sizeof(client_header);

    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));
    ui->stackedWidget->setCurrentIndex(5);
    ui->tableWidget_stuCourse->clearContents();
    ui->tableWidget_stuCourse->setRowCount(0);
}
//选课 除了专业课
void StudentWindow::on_buttonStuSelectCourse_triggered()
{
       //全部选修课
    client_header getInfoReq;
    getInfoReq.cmdType=0x04;
    getInfoReq.length=0;
    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));

    ui->stackedWidget->setCurrentIndex(4);
    ui->tableWidget_StuSelectCourse->clearContents();
    ui->tableWidget_StuSelectCourse->setRowCount(0);
}
//选课 下拉框
void StudentWindow::on_comboBox_StuSelectCourse_currentIndexChanged(int index)
{
    index=ui->comboBox_StuSelectCourse->currentIndex();
    client_header getInfoReq;
    getInfoReq.cmdType=0x04;
    getInfoReq.length=index;
    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));


    ui->tableWidget_StuSelectCourse->clearContents();
    ui->tableWidget_StuSelectCourse->setRowCount(0);
}
//选课
void StudentWindow::on_tableWidget_StuSelectCourse_itemClicked(QTableWidgetItem *item)
{
    int row=ui->tableWidget_StuSelectCourse->currentRow();
    int col=ui->tableWidget_StuSelectCourse->currentColumn();

    QString str1=ui->tableWidget_StuSelectCourse->item(row,col)->text();
    if(col==7 &&  QString::compare( str1, "选课" ) ==0){
        qDebug()<<"选课";
        qDebug()<<"行数"<<row;
        client_header getInfoReq;
        getInfoReq.cmdType=0x05;
        getInfoReq.length=sizeof(client_header);
        tcpSocket->write((char*)&getInfoReq,sizeof(client_header));

        student_courseScore_package course;
        QString str;
        str=ui->tableWidget_StuSelectCourse->item(row,0)->text();
        strncpy(course.CourseID,str.toLocal8Bit().data(),10);

        tcpSocket->write((char*)&course,sizeof(student_courseScore_package));
        qDebug()<<"课程号"<<course.CourseID;

    }
}
//鼠标移动到上面样式改变
void StudentWindow::on_tableWidget_StuSelectCourse_itemEntered(QTableWidgetItem *item)
{
   /* int col=ui->tableWidget_StuSelectCourse->currentColumn();
    qDebug()<<"s";
    if(col==7 ){
        qDebug()<<"ss";
         this->setCursor(Qt::PointingHandCursor);
    }*/
}

void StudentWindow::on_tableWidget_StuSelectCourse_itemChanged(QTableWidgetItem *item)
{  /* qDebug()<<"d";
    int col=ui->tableWidget_StuSelectCourse->currentColumn();
    if(col!=7 ){
        qDebug()<<"dd";
         this->setCursor(Qt::ArrowCursor);
    }*/
}

void StudentWindow::on_tableWidget_StuSelectCourse_cellEntered(int row, int column)
{  /* qDebug()<<"d";
    int col=ui->tableWidget_StuSelectCourse->currentColumn();
    if(col!=7 ){
        qDebug()<<"dd";
         this->setCursor(Qt::ArrowCursor);
    }else{
        qDebug()<<"ddd";
       this->setCursor(Qt::PointingHandCursor);
    }*/
}
//修改密码
void StudentWindow::on_buttonStuForgotPwd_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void StudentWindow::on_button_StuForgotPwd_True_clicked()
{
    //获取表单内容
    QString userPwd=ui->lineEdit_StuForgotPwd_InputPwd->text();
    //清空表单
    ui->lineEdit_StuForgotPwd_InputPwd->clear();

    if(userPwd.isEmpty())
    {
        qDebug()<<"Error :Can't be empty!";
        QMessageBox::information(this,"Warning","Can't be empty!",QMessageBox::Ok);
    }
    else if(userPwd.length()<6){
        qDebug()<<"Error :Can't be short!";
        QMessageBox::information(this,"Warning","Can't be short!",QMessageBox::Ok);
    }
    else{
        //首先发送请求报文
        client_header loginReq;
        loginReq.cmdType=0x06;
        loginReq.length=sizeof(login_package);

        tcpSocket->write((char*)&loginReq,sizeof(client_header));

        //发送登陆包
        login_package loginP;
        char*  ch;
        QByteArray ba;

        ba = userPwd.toLatin1();
        ch=ba.data();
        strncpy(loginP.password,ch,20);

        tcpSocket->write((char*)&loginP,sizeof(login_package));
    }
}
