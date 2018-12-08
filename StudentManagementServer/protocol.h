#ifndef PROTOCOL_H
#define PROTOCOL_H
/*
客户端请求协议头
statu   含义
0x00    点击登录按钮，请求登录
0x01    点击查看更多按钮，请求更多信息
0x02    点击已选课程，请求已选课程信息
0x03    点击成绩，请求查看课程成绩
0x04    点击选课，请求查看选修课成绩信息,0-全部，1-通识课，2-实践，3-英语，4-体育
0x05    学生点击选择某一门课
0x06    点击修改密码
0x07    点击学院查询
0x08    在学院查询列表那里，点击查看班级信息
0x09    在班级查询列表那里，点击查看班级成员信息
0x0A    点击课程查询按钮，查看所有的课程信息
0x0B    点击课程查看按钮，查看该课程所有的
0x0C
*/
#pragma pack (1)
typedef struct client_header{
    //表示客户端的请求类型
    char cmdType;
    //表示该数据包之后跟随的数据长度
    int length;
}client_header;

//登录包
typedef struct login_package{
    char userID[20];
    char password[20];
}login_package;



/*
服务器端响应协议头
statu   含义
0x00    表示响应失败，length=0，（用户名或密码错误）
0x01    表示响应成功，length返回下一附件的长度
0x02    表示发送完整信息
0x03    表示接下来我要发送已选课程信息
0x04    表示接下来我要发送有成绩的课程信息
0x05    表示接下来我要发送选修课的课程信息
0x06    表示接下来我要发送：选课是否成功的信息
0x07    表示回应修改密码是否成功
0x08    表示回应学院查询的结果，发送学院的信息
0x09    表述回应学院查询界面查看按钮，发送学院里面的班级信息
0x0A    表述回应班级查询界面查看按钮，发送该班级的学生的信息
0x0B    表示回应课程查询，发送所有的课程信息
0x0C
*/
typedef struct response_header{
    char statu;//响应状态码
    int length;//数据长度
}response_header;

//用户基本信息包
typedef struct user_simple_package
{
    char userID[10];
    char userName[20];
}user_simple_package;
//用户完整信息包
typedef struct user_full_package
{
    char userID[10];
    char userName[20];
    char userInstituteName[30];//学院
    char userClassName[30];//班级
    char userAssistantName[20];//辅导员
    char usermasterName[20];//班主任
    bool userGender;
    int userAge;
    char userBirthDay[10];
    char userCardID[20];
    char userNativePlace[50];
    char userNationality[50];
}user_full_package;
//用户中等信息包
typedef struct user_mid_package{
    char userID[10];
    char userName[20];
    bool userGender;
    char userInstituteName[30];//学院
    char userClassName[30];//班级
}user_mid_package;
//添加学生包
typedef struct add_stu_package{
    char stuID[10];
    char stuName[20];
    char stuClassID[10];
    char userCardID[20];
    char userNativePlace[50];
    char userNationality[50];
    bool userGender;
}add_stu_package;

//学生选的课程信息包
typedef struct student_course_package
{
    char CourseID[10];
    char CourseName[30];
    char TchName[20];
    int  CourseCredit;
    char CourseTypeName[20];
    int CourseLimitNum;//课程限选人数
    int StuNum;//当前选课人数
    bool isSelected;

}student_course_package;
//学生课程成绩包
typedef struct  student_courseScore_package
{
    char CourseID[10];
    char CourseName[30];
    int CourseScore;
}student_courseScore_package;

typedef struct class_Info_Package
{
    char ClassID[10];
    char ClassName[30];
}class_Info_Package;

typedef struct  student_courseScoreInfo_package
{
    char StuID[10];
    char StuName[20];
    char CourseID[10];
    char CourseName[30];
    int CourseScore;
}student_courseScoreInfo_package;
//学院信息包
typedef struct InstituteInfo_package
{
    char InstituteID[10];
    char InstituteName[30];
    char AssistantName[20];
    int StuNum;
}InstituteInfo_package;

//班级id，名字，学生人数，班主任，班长
typedef struct ClassInfo_package
{
    char ClassID[10];
    char ClassName[30];
    char MasterName[20];
    char MonitorName[20];
    int StuNum;
}ClassInfo_package;

//客户端信息
typedef struct ClientInfo{
    int socketDescriptor;
    QString userName;
}ClientInfo;
#endif // PROTOCOL_H
