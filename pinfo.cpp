#include "func.h"
void pinfo(int pid){
    string path = "/proc/"+to_string(pid)+"/status";
    cout<<"pid -- "<<pid<<endl;
    FILE *fp = fopen(&path[0],"r");
    char line[256];
    pid_t fg = tcgetpgrp(STDIN_FILENO);
    pid_t pgid = getpgid(pid);
    while(fgets(line,256,fp)){
        if(strstr(line,"State")){
            cout<<"Process Status -- "<<line[7];
            if(line[7]=='S'||line[7]=='R'&&pgid==pid){
                cout<<'+';
            }
            cout<<endl;
        }
        
        else if(strstr(line,"VmRSS")){
            cout<<"memory -- "<<&line[11];
        }
    }
    string exePath = "/proc/"+to_string(pid)+"/exe";
        char exe[100];
        if(readlink(&exePath[0],exe,sizeof(exe)-1)!=-1)
            cout<<"Executable Path -- "<<exe;
}