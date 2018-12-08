#ifndef PROTOCOL_H
#define PROTOCOL_H
/*
客户端请求协议头
statu   含义
0x00    点击登录按钮，请求登录
0x01    点击查看更多按钮，请求更多信息
0x02    点击已选课程，请求已选课程信
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
0x02
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

typedef struct student_course_package
{
    char CourseID[10];
    char CourseName[30];
    char TchName[20];
    int  CourseCredit;
    char CourseTypeName[20];
    int CourseLimitNum;
    int StuNum;
    bool isSelected;

}student_course_package;

typedef struct  student_courseScore_package
{
    char CourseID[10];
    char CourseName[30];
    int CourseScore;
}student_courseScore_package;


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

typedef struct user_mid_package{
    char userID[10];
    char userName[20];
    bool userGender;
    char userInstituteName[30];//学院
    char userClassName[30];//班级
}user_mid_package;
typedef struct  student_courseScoreInfo_package
{
    char StuID[10];
    char StuName[20];
    char CourseID[10];
    char CourseName[30];
    int CourseScore;
}student_courseScoreInfo_package;
typedef struct class_Info_Package
{
    char ClassID[10];
    char ClassName[30];
}class_Info_Package;
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

#endif // PROTOCOL_H
