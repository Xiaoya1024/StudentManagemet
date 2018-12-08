#include "managerwindow.h"
#include "ui_managerwindow.h"
ManagerWindow::ManagerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerWindow)
{
    ui->setupUi(this);
    ui->tableWidget_InstitueInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tableWidget_InstitueInfo->setSelectionMode(QAbstractItemView::SingleSelection);
}

ManagerWindow::~ManagerWindow()
{
    delete ui;
}

void ManagerWindow::GetInstituteInfo(InstituteInfo_package instiInfo){
    int row=ui->tableWidget_InstitueInfo->rowCount();
    ui->tableWidget_InstitueInfo->setRowCount(row+1);
    qDebug()<<instiInfo.InstituteID<<instiInfo.InstituteName<<instiInfo.AssistantName<<instiInfo.StuNum;
    ui->tableWidget_InstitueInfo->setItem(row,0,new QTableWidgetItem(instiInfo.InstituteID));
    ui->tableWidget_InstitueInfo->setItem(row,1,new QTableWidgetItem(instiInfo.InstituteName));
    ui->tableWidget_InstitueInfo->setItem(row,2,new QTableWidgetItem(instiInfo.AssistantName));
    ui->tableWidget_InstitueInfo->setItem(row,3,new QTableWidgetItem(QString::number(instiInfo.StuNum)));
    ui->tableWidget_InstitueInfo->setItem(row,4,new QTableWidgetItem("查看"));
}

void ManagerWindow::GetClassInfo(ClassInfo_package classInfo){
    int row=ui->tableWidget_InClass->rowCount();
    ui->tableWidget_InClass->setRowCount(row+1);
    qDebug()<<classInfo.ClassID<<classInfo.ClassName<<classInfo.MasterName<<classInfo.MonitorName<<classInfo.StuNum;
    ui->tableWidget_InClass->setItem(row,0,new QTableWidgetItem(classInfo.ClassID));
    ui->tableWidget_InClass->setItem(row,1,new QTableWidgetItem(classInfo.ClassName));
    ui->tableWidget_InClass->setItem(row,2,new QTableWidgetItem(classInfo.MasterName));
    ui->tableWidget_InClass->setItem(row,3,new QTableWidgetItem(classInfo.MonitorName));
    ui->tableWidget_InClass->setItem(row,4,new QTableWidgetItem(QString::number(classInfo.StuNum)));
    ui->tableWidget_InClass->setItem(row,5,new QTableWidgetItem("查看"));

}

void ManagerWindow::GetClassStuInfo(user_full_package stuInfo){
    int row=ui->tableWidget_ClassStu->rowCount();
    ui->tableWidget_ClassStu->setRowCount(row+1);
    qDebug()<<stuInfo.userID<<stuInfo.userName;
    ui->tableWidget_ClassStu->setItem(row,0,new QTableWidgetItem(stuInfo.userID));
    ui->tableWidget_ClassStu->setItem(row,1,new QTableWidgetItem(stuInfo.userName));
    ui->tableWidget_ClassStu->setItem(row,2,new QTableWidgetItem(stuInfo.userInstituteName));
    ui->tableWidget_ClassStu->setItem(row,3,new QTableWidgetItem(stuInfo.userClassName));
    ui->tableWidget_ClassStu->setItem(row,4,new QTableWidgetItem(stuInfo.userAssistantName));
    ui->tableWidget_ClassStu->setItem(row,5,new QTableWidgetItem(stuInfo.usermasterName));
    if(stuInfo.userGender){
         ui->tableWidget_ClassStu->setItem(row,6,new QTableWidgetItem("男"));
    }else{
         ui->tableWidget_ClassStu->setItem(row,6,new QTableWidgetItem("女"));
    }
    ui->tableWidget_ClassStu->setItem(row,7,new QTableWidgetItem(QString::number(stuInfo.userAge)));
    ui->tableWidget_ClassStu->setItem(row,8,new QTableWidgetItem(stuInfo.userBirthDay));
    ui->tableWidget_ClassStu->setItem(row,9,new QTableWidgetItem(stuInfo.userCardID));
    ui->tableWidget_ClassStu->setItem(row,10,new QTableWidgetItem(stuInfo.userNativePlace));
    ui->tableWidget_ClassStu->setItem(row,11,new QTableWidgetItem(stuInfo.userNationality));

}

void ManagerWindow::GetCourseInfo(student_course_package courseInfo){
    int row=ui->tableWidget_course1->rowCount();
    ui->tableWidget_course1->setRowCount(row+1);
    qDebug()<<courseInfo.CourseID<<courseInfo.CourseName;
    ui->tableWidget_course1->setItem(row,0,new QTableWidgetItem(courseInfo.CourseID));
    ui->tableWidget_course1->setItem(row,1,new QTableWidgetItem(courseInfo.CourseName));
    ui->tableWidget_course1->setItem(row,2,new QTableWidgetItem(courseInfo.TchName));
    ui->tableWidget_course1->setItem(row,3,new QTableWidgetItem(QString::number(courseInfo.CourseCredit)));
    ui->tableWidget_course1->setItem(row,4,new QTableWidgetItem(courseInfo.CourseTypeName));
    ui->tableWidget_course1->setItem(row,5,new QTableWidgetItem(QString::number(courseInfo.CourseLimitNum)));
    ui->tableWidget_course1->setItem(row,6,new QTableWidgetItem(QString::number(courseInfo.StuNum)));
    ui->tableWidget_course1->setItem(row,7,new QTableWidgetItem("查看"));
}

void ManagerWindow::GetCourseStu(user_mid_package  c2){
    int row=ui->tableWidget_coursestu->rowCount();
    ui->tableWidget_coursestu->setRowCount(row+1);
    qDebug()<<c2.userID<<c2.userName;
    ui->tableWidget_coursestu->setItem(row,0,new QTableWidgetItem(c2.userID));
    ui->tableWidget_coursestu->setItem(row,1,new QTableWidgetItem(c2.userName));
    if(c2.userGender){
       ui->tableWidget_coursestu->setItem(row,2,new QTableWidgetItem("男"));
    }else{
        ui->tableWidget_coursestu->setItem(row,2,new QTableWidgetItem("女"));
    }
    ui->tableWidget_coursestu->setItem(row,3,new QTableWidgetItem(c2.userInstituteName));
    ui->tableWidget_coursestu->setItem(row,4,new QTableWidgetItem(c2.userClassName));
}



void ManagerWindow::GetCourseScore(student_courseScore_package s2){

    ui->comboBox_course->addItem(s2.CourseID);

}

void ManagerWindow::GetCourseScore2(student_courseScoreInfo_package *s1,int n){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
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
     out <<tr("学号,") << tr("姓名,")<<tr("课程ID,")<<tr("课程名称,")<< tr("成绩," )<<",\n";//表头
     for(int i=0;i<n;i++){
        out <<"\t" <<s1[i].StuID<<","<<tr(s1[i].StuName)  << tr(",\t")<<s1[i].CourseID << ","<<tr(s1[i].CourseName)  << "," <<s1[i].CourseScore  << ","<<",\n";//表头
     }
     file.close();

}


void ManagerWindow::GetLabelin(int i){
    if(i==-1){
        ui->label_in->setText("导入完成");
    }else if(i==-2){
     ui->label_in->setText("导入失败");
    }
}

void ManagerWindow::GetClassLabel(int n){
    for(int i=0;i<n;i++){
        ui->comboBox_class->addItem(cla[i].ClassID);
    }

}


//查询学院
void ManagerWindow::on_actionxueyuanchauxn_triggered()
{
    client_header getInfoReq;
    getInfoReq.cmdType=0x07;
    getInfoReq.length=sizeof(client_header);
    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));

    ui->stackedWidget->setCurrentIndex(1);
    ui->tableWidget_InstitueInfo->clearContents();
    ui->tableWidget_InstitueInfo->setRowCount(0);
}
//查看学院信息
void ManagerWindow::on_tableWidget_InstitueInfo_itemClicked(QTableWidgetItem *item)
{
    int row=ui->tableWidget_InstitueInfo->currentRow();
    int col=ui->tableWidget_InstitueInfo->currentColumn();
    if(col==4){

        client_header getInfoReq;
        getInfoReq.cmdType=0x08;
        QString str=ui->tableWidget_InstitueInfo->item(row,0)->text();
        char id[10];
        getInfoReq.length=10;
        strncpy(id,str.toLocal8Bit().data(),10);
        tcpSocket->write((char*)&getInfoReq,sizeof(client_header));
        tcpSocket->write((char*)id,10);
        qDebug()<<"查看学院"<<getInfoReq.length;
        ui->stackedWidget->setCurrentIndex(2);
        ui->tableWidget_InClass->clearContents();
        ui->tableWidget_InClass->setRowCount(0);
    }


}

void ManagerWindow::on_pushButtonback1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
//查看班级学生
void ManagerWindow::on_tableWidget_InClass_itemClicked(QTableWidgetItem *item)
{
    int row=ui->tableWidget_InClass->currentRow();
    int col=ui->tableWidget_InClass->currentColumn();
    if(col==5){
        qDebug()<<"查看";
        client_header getInfoReq;
        getInfoReq.cmdType=0x09;
        QString str=ui->tableWidget_InClass->item(row,0)->text();
        char id[10];
        getInfoReq.length=10;
        strncpy(id,str.toLocal8Bit().data(),10);
        tcpSocket->write((char*)&getInfoReq,sizeof(client_header));
        tcpSocket->write((char*)id,10);
        qDebug()<<"查看班级学生"<<getInfoReq.length;
        ui->stackedWidget->setCurrentIndex(3);
        ui->tableWidget_ClassStu->clearContents();
        ui->tableWidget_ClassStu->setRowCount(0);
    }
}

void ManagerWindow::on_pushButtonback2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void ManagerWindow::on_action1_3_triggered()
{
    client_header getInfoReq;
    getInfoReq.cmdType=0x0A;
    getInfoReq.length=0;
    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));

    ui->stackedWidget->setCurrentIndex(6);
    ui->tableWidget_course1->clearContents();
    ui->tableWidget_course1->setRowCount(0);
}

void ManagerWindow::on_comboBox_currentIndexChanged(int index)
{
    index=ui->comboBox->currentIndex();
    client_header getInfoReq;
    getInfoReq.cmdType=0x0A;
    getInfoReq.length=index;
    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));


    ui->tableWidget_course1->clearContents();
    ui->tableWidget_course1->setRowCount(0);
}



void ManagerWindow::on_tableWidget_course1_itemClicked(QTableWidgetItem *item)
{
    int row=ui->tableWidget_course1->currentRow();
    int col=ui->tableWidget_course1->currentColumn();
    if(col==7){

        client_header getInfoReq;
        getInfoReq.cmdType=0x0B;
        QString str=ui->tableWidget_course1->item(row,0)->text();
        char id[10];
        getInfoReq.length=10;
        strncpy(id,str.toLocal8Bit().data(),10);
        tcpSocket->write((char*)&getInfoReq,sizeof(client_header));
        tcpSocket->write((char*)id,10);
        qDebug()<<"查看选课学生"<<getInfoReq.length;
        ui->stackedWidget->setCurrentIndex(7);
        ui->tableWidget_coursestu->clearContents();
        ui->tableWidget_coursestu->setRowCount(0);
    }
}

void ManagerWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}
//导入文件
void ManagerWindow::on_pushButton_in_clicked()
{
    ui->label_in->setText("导入中...");
    QString fileName = QFileDialog::getOpenFileName(this, tr("Excel file"), qApp->applicationDirPath (),
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
         student_courseScoreInfo_package *s=new student_courseScoreInfo_package();
         while(!in.atEnd())
         {
             if(i==-1){
                 i++;
                 continue;
             }


             s=(student_courseScoreInfo_package*)realloc(s, (i+1)*sizeof(student_courseScoreInfo_package));

            QString fileLine = in.readLine();
            list = fileLine.split(QRegExp("[,\"\t]"), QString::SkipEmptyParts);

                //qDebug()<<"0"<<list.at(0);
               // qDebug()<<"1"<<list.at(2);
              //  qDebug()<<"2"<<list.at(4);
                char*  ch;
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
             file.close();
    client_header getInfoReq;
    getInfoReq.cmdType=0x0E;
    getInfoReq.length=i;
    qDebug()<<i;
    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));
    for(int k=1;k<i;k++)
    {
    qint64 x=tcpSocket->write((char*)&s[k],sizeof(student_courseScoreInfo_package));
    qDebug()<<k<<"x"<<x<<s[k].StuID<<s[k].CourseID<<s[k].CourseScore;
    }
   // tcpSocket->write((char*)&getInfoReq,sizeof(client_header));
        free(s);


}
//导出文件
void ManagerWindow::on_pushButton_out_clicked()
{
    client_header getInfoReq;
    getInfoReq.cmdType=0x0D;
    QString str=ui->comboBox_course->currentText();
    char id[10];
    getInfoReq.length=10;
    strncpy(id,str.toLocal8Bit().data(),10);

    qDebug()<<id;
    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));
     tcpSocket->write((char*)id,10);
}
//得到课程列表
void ManagerWindow::on_action1_8_triggered()
{

}

void ManagerWindow::on_action1_5_triggered()
{
    client_header getInfoReq;
    getInfoReq.cmdType=0x0C;
    getInfoReq.length=sizeof(client_header);
    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));
    ui->stackedWidget->setCurrentIndex(9);
    ui->comboBox_course->clear();
    ui->comboBox_course->setCurrentIndex(0);
}

void ManagerWindow::on_comboBox_course_currentIndexChanged(int index)
{
    ui->label_coursename->setText(ss[index].CourseName);
}

void ManagerWindow::on_action1_11_triggered()
{
    client_header getInfoReq;
    ui->stackedWidget->setCurrentIndex(10);
    getInfoReq.cmdType=0x0F;
    getInfoReq.length=sizeof(client_header);
    tcpSocket->write((char*)&getInfoReq,sizeof(client_header));
    ui->comboBox_class->clear();
    ui->comboBox_class->setCurrentIndex(0);
}

void ManagerWindow::on_comboBox_class_currentIndexChanged(int index)
{
    ui->label_classname->setText(cla[index].ClassName);
}

void ManagerWindow::on_pushButton_add_clicked()
{
    //获取表单内容
    QString stuID=ui->lineEdit_stuid->text();
    QString stuName=ui->lineEdit_stuname->text();
    qDebug()<<stuName;
     QString stuClass=ui->comboBox_class->currentText();
    QString stuCardID=ui->lineEdit_cardid->text();
    QString stuNp=ui->lineEdit_stunp->text();
    QString stuNa=ui->lineEdit_na->text();
   // QString stuGender=ui->comboBox_gender->currentText();
    //清空表单
    ui->lineEdit_stuid->clear();
    ui->lineEdit_stuname->clear();
    ui->lineEdit_cardid->clear();
    ui->lineEdit_stunp->clear();
    ui->lineEdit_na->clear();

    if(stuID.isEmpty()||stuName.isEmpty()||stuCardID.isEmpty()||stuNp.isEmpty()||stuNa.isEmpty())
    {
        qDebug()<<"Error :Can't be empty!";
        QMessageBox::information(this,"Warning","Can't be empty!",QMessageBox::Ok);
    }
    else{
        //首先发送请求报文
        client_header loginReq;
        loginReq.cmdType=0x10;
        loginReq.length=sizeof(login_package);

        tcpSocket->write((char*)&loginReq,sizeof(client_header));

        //发送登陆包
        add_stu_package asp;

        strncpy(asp.stuID,stuID.toStdString().c_str(),10);


        strncpy(asp.stuName,stuName.toStdString().c_str(),20);


        strncpy(asp.stuClassID,stuClass.toStdString().c_str(),10);


        strncpy(asp.userCardID,stuCardID.toStdString().c_str(),20);


        strncpy(asp.userNativePlace,stuNp.toStdString().c_str(),50);

        strncpy(asp.userNationality,stuNa.toStdString().c_str(),50);
        if(ui->comboBox_gender->currentIndex()==0){
            asp.userGender=true;
        }else{
            asp.userGender=false;
        }
        qDebug()<<asp.stuID<<asp.stuName<<asp.userNativePlace<<asp.userNationality;
        tcpSocket->write((char*)&asp,sizeof(add_stu_package));
    }
}

void ManagerWindow::on_action2_4_triggered()
{
    ui->stackedWidget->setCurrentIndex(11);
}

void ManagerWindow::on_pushButton_clicked()
{

}

void ManagerWindow::on_pushButton_del_clicked()
{
    QString stuID=ui->lineEdit_delstuid->text();
    if(stuID.isEmpty())
    {
        qDebug()<<"Error :Can't be empty!";
        QMessageBox::information(this,"Warning","Can't be empty!",QMessageBox::Ok);
    }else{
        client_header req;
        req.cmdType=0x11;
        req.length=10;
        char id[10];
        strncpy(id,stuID.toLocal8Bit().data(),10);
        tcpSocket->write((char*)&req,sizeof(client_header));
        tcpSocket->write((char*)id,10);
    }
}
