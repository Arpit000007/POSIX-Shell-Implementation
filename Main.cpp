#include "func.h"
using namespace std;
using namespace filesystem;
void changeDir(string path)
{  
    int res = chdir(&path[0]);
    if (res != 0)
    {
        cout << "Directory " << path << " does not exists" << endl;
    }
}

void echo(string str)
{
    int l = str.length();
    if (str[0] == '"')
    {
        for (int i = 1; i < l && !(str[i] == '"' || str[i] == '>'); i++)
            cout << str[i];
        cout << endl;
    }
    else
    {
        for (int i = 0; i < l && !(str[i] == '>'); i++)
            cout << str[i];
        cout << endl;
    }
}

int main()
{
    string user = getUser();
    string host = getHost();
    string homeDir = get_current_dir_name();
    string currDir = "~";
    string prevDir;
    while (true)
    {

        if (homeDir.compare(get_current_dir_name()) == 0)
        {
            currDir = "~";
        }
        cout << user << "@" << host << ":" << currDir << ">";
        string line, temp;
        getline(cin, line);
        if (line.empty())
        {
            continue;
        }
        vector<string> commands;
        char *cmdtok = strtok(&line[0], ";");
        while (cmdtok != 0)
        {
            commands.push_back(cmdtok);
            cmdtok = strtok(NULL, ":");
        }
        for (int i = 0; i < commands.size(); i++)
        {
            string str = commands.at(i);
            temp = str;
            if (str.find(">") || str.find("<"))
                handleRedirection(str);
            vector<string> tokens;
            char *tok = strtok(&str[0], " ");

            while (tok != 0)
            {
                tokens.push_back(tok);
                tok = strtok(NULL, " ");
            }
            int s = tokens.size();
            string cmd = tokens.at(0);

            if (cmd.compare("cd") == 0)
            {
                bool succ;
                if (s == 1)                    
                {
                    prevDir=homeDir;
                    changeDir(homeDir);
                }
                if (s > 2)
                {
                    cout << "Invalid arguments" << endl;
                    continue;
                }
                else if (currDir == "~" && tokens.at(1) == "..")
                {
                    currDir = get_current_dir_name();
                }
                else
                {
                    if(tokens.at(1)=="-"){
                        if(prevDir.empty()){
                            cout<<"bash: cd: OLDPWD not set";
                            return 1;
                        }
                        else{
                            tokens.at(1)=prevDir;
                            prevDir=get_current_dir_name();
                        }
                    }
                    else{
                        prevDir=get_current_dir_name();
                    }
                    changeDir(tokens.at(1));
                }
                cout << get_current_dir_name() << endl;
                currDir = string("~") + &(get_current_dir_name()[homeDir.length()]);
            }
            else if (cmd.compare("echo") == 0)
            {
                echo(temp.substr(temp.find_first_of(tokens.at(1)[0])));
            }
            else if (cmd.compare("pwd") == 0)
            {
                cout << currDir << endl;
            }
            else if (cmd.compare("ls") == 0)
            {
                listFiles(tokens);
            }
            else if (cmd.compare("pinfo") == 0)
            {
                int pid;
                if (s == 1)
                    pid = getpid();
                else
                    pid = stoi(tokens.at(1));
                pinfo(pid);
            }
            else if (cmd.compare("search") == 0)
            {
                searchFile(get_current_dir_name(), tokens.at(1));
            }
            else
            {
                bool bg = false;
                if (tokens.at(s - 1) == "&")
                {
                    s = s - 1;
                    bg = true;
                }
                char *arg[s + 1];
                arg[0] = &cmd[0];
                for (int i = 1; i < s + 1; i++)
                {
                    arg[i] = &tokens[i][0];
                }

                arg[s] = nullptr;
                pid_t id = fork();
                if (id == 0)
                {
                    if(bg){
                        setpgid(0,0);
                    }
                    execvp(&cmd[0], arg);
                    exit(0);
                }
                else
                {
                    int st;
                    if (bg){
                        cout<<id<<endl;
                        waitpid(id, &st, 0);
                        
                    }

                    else
                    {
                        wait(NULL);
                        cout << id << endl;
                    }
                }
            }
            cout.flush();
            changeRedirection();
        }
    }
    return 0;
}