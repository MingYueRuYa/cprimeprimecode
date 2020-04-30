#ifndef message_hpp_h
#define message_hpp_h

// 定义网络报文
enum MessageTypes
{
    T_Login = 0,
    T_Login_Result,
    T_Logout,
    T_Logout_Result,
    T_ERROR
};

struct MessageHeader
{
    short length;
    short type;
};

struct Login : public MessageHeader
{
    Login()
    {
        length = sizeof(Login);
        type  = T_Login;
    }

    char name[32];
    char passwrod[32];
};

struct Login_Result : public MessageHeader
{
    Login_Result()
    {
        length = sizeof(Login_Result);
        type  = T_Login_Result;
    }

    char name[32];
    char passwrod[32];
};

struct Logout : public MessageHeader
{
    Logout()
    {
        length = sizeof(Logout);
        type  = T_Logout;
    }

    char name[32];
    char passwrod[32];
};

struct LogOut_Result : public MessageHeader
{
    LogOut_Result()
    {
        length = sizeof(Logout);
        type  = T_Logout_Result;
        // 0 表示成功
        result = 0;
    }

    int result;
};

#endif // message_hpp_h