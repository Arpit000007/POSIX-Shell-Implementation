#ifndef MAKE_GPP_FUNC
#define MAKE_GPP_FUNC

#include<iostream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <bits/stdc++.h>
#include <termios.h>
#include <dirent.h>
#include <fstream>

#include <sstream>
#include <unistd.h>
using namespace std;
string getUser();
string getHost();
string getCurrDir();
void listFiles(vector<string>);
void pinfo(int);
void searchFile(string currDir,string file);
void handleRedirection(string);
void changeRedirection();
#endif