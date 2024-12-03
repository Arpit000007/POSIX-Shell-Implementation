#include "func.h"
void searchFile(string currDir, string file){
    queue<string> dir;
    dir.push(currDir);
    DIR *folder = nullptr;
    while(dir.size()>0){
        folder = opendir(&dir.front()[0]);
        dirent* d;
        while(d=readdir(folder)){
            char* curr=d->d_name;
            if(strcmp(d->d_name,&file[0])==0){
                cout<<"true"<<endl;
                return;
            }
            struct stat sb;
            string str = dir.front()+"/"+string(curr);
            if (stat(&str[0], &sb) == -1)
                    {
                        cout << "ERROR IN GETTING STATS FOR " << d->d_name << endl;
                        return;
                    }
                    else
                    {
                        if(sb.st_mode & S_IFDIR && curr[0]!='.'){
                            dir.push(dir.front()+"/"+curr);
                        }
                    }
        }
        closedir(folder);
        dir.pop();
    }
    cout<<"false"<<endl;
}