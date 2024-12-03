#include "func.h"
string getUser()
{
    char user[50];
    if (getlogin_r(user, 50) == 0)
    {
        return user;
    }
    return "USER";
}

string getHost()
{
    char host[50];
    if (gethostname(host, 50) == 0)
    {
        return host;
    }
    return "HOST";
}
string getCurrDir()
{
    char currDir[50];
    if (getcwd(currDir, 50) != "\0")
    {
        return currDir;
    }
    return "DIR";
}