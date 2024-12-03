#include "func.h"
void listFiles(vector<string> tokens)
{
    cout << "In listfiles" << endl;
    DIR *folder = nullptr;
    string fName = ".";
    string flags;
    bool lFlag = false, aFlag = false;
    int s = tokens.size();
    vector<string> dirNames;
    if (s == 1)
    {
        fName = ".";
    }
    else
    {
        for (int i = 1; i < s; i++)
        {
            string curr = tokens.at(i);
            if (curr[0] != '-' && curr!="&")
            {
                dirNames.push_back(tokens.at(i));
            }
            else if (curr[0] == '-')
            {
                flags = curr;
                for (int i = 1; i < flags.length(); i++)
                {
                    if (flags[i] == 'l')
                        lFlag = true;
                    else if (flags[i] == 'a')
                        aFlag = true;
                    else
                    {
                        cout << "ls: invalid option -- " << flags[i];
                        return;
                    }
                }
            }
        }
    }
    if (dirNames.size() == 0)
        dirNames.push_back(".");
    for (int i = 0; i < dirNames.size(); i++)
    {
        string curr = dirNames.at(i);
            if (dirNames.size() > 1)
                cout << curr << "/:" << endl;

            folder = opendir(&curr[0]);
            if (folder == nullptr)
            {
                cout << "ls: cannot access '" << curr << "' :"
                     << "No such file or directory" << endl;
            }
            struct dirent *dr;
            while (dr = readdir(folder))
            {
                if (!aFlag && dr->d_name[0] == '.')
                    continue;
                if (lFlag)
                {
                    struct stat sb;
                    string path = curr + "/" + dr->d_name;
                    if (stat(&path[0], &sb) == -1)
                    {
                        cout << "ERROR IN GETTING STATS FOR " << dr->d_name << endl;
                        return;
                    }
                    else
                    {
                        char *modeval = new char[11];
                        mode_t perm = sb.st_mode;
                        modeval[0] = sb.st_mode & S_IFDIR?'d':'-';
                        modeval[1] = (perm & S_IRUSR) ? 'r' : '-';
                        modeval[2] = (perm & S_IWUSR) ? 'w' : '-';
                        modeval[3] = (perm & S_IXUSR) ? 'x' : '-';
                        modeval[4] = (perm & S_IRGRP) ? 'r' : '-';
                        modeval[5] = (perm & S_IWGRP) ? 'w' : '-';
                        modeval[6] = (perm & S_IXGRP) ? 'x' : '-';
                        modeval[7] = (perm & S_IROTH) ? 'r' : '-';
                        modeval[8] = (perm & S_IWOTH) ? 'w' : '-';
                        modeval[9] = (perm & S_IXOTH) ? 'x' : '-';
                        modeval[10] = '\0';

                        passwd* psw=getpwuid(sb.st_uid);
                        string user=psw->pw_name;
                        group* gr = getgrgid(sb.st_gid);
                        string grp=gr->gr_name;
                        time_t mtime = sb.st_mtime;
                        string modTime = asctime(std::localtime(&mtime));
                        modTime=modTime.substr(4,modTime.length()-13);
                        cout << modeval << " " << sb.st_nlink << " " << user << " " << grp << " "
                  << sb.st_size << " " << modTime << " ";
                    }
                }
                cout << dr->d_name << endl;
            }
            closedir(folder);
    }
}