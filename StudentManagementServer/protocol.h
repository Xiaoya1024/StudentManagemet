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

typedef struct user_full_package
{
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

typedef struct  student_courseScore_package
{
    char CourseID[10];
    char CourseName[30];
    int CourseScore;
}student_courseScore_package;

typedef struct ClientInfo{
    int socketDescriptor;
    QString userName;
}ClientInfo;
#endif // PROTOCOL_H
