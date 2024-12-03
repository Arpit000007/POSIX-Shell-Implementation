#include "func.h"
int oldInFd = dup(STDIN_FILENO);
int oldOpFd = dup(STDOUT_FILENO);
void handleRedirection(string str)
{
    string inFile;
    string opFile;

    int l = str.length();
    for (int i = 0; i < l;)
    {
        if (str[i] == '<')
        {
            if (str[i + 1] == '<')
            {
                i++;
            }
            i++;
            while (i < l && str[i] == ' ')
                i++;
            while (i < l && (str[i] != '>' && str[i] != ' '))
            {
                inFile += str[i];
                i++;
            }
            if (inFile.length() > 0)
            {
                int ifd = open(&inFile[0], O_RDONLY);
                int errsv = errno;
                if (errsv == ENOENT)
                {
                    cout << "Input file does not exist.";
                    exit(0);
                }
                else
                {
                    dup2(ifd, STDIN_FILENO);
                }
                close(ifd);
            }
        }
        if (str[i] == '>')
        {
            bool append = false;
            if (str[i + 1] == '>')
            {
                append = true;
                i++;
            }
            i++;
            while (i < l && str[i] == ' ')
                i++;
            while (i < l && (str[i] != '<' && str[i] != ' '))
            {
                opFile += str[i];
                i++;
            }
            if (opFile.length() > 0)
            {
                int ofd;
                if (append)
                    ofd = open(&opFile[0], O_WRONLY | O_CREAT | O_APPEND, 0644);

                else
                    int ofd = open(&opFile[0], O_WRONLY | O_CREAT, 0644);
                dup2(ofd, STDOUT_FILENO);
                close(ofd);
            }
        }
        else
        {
            i++;
        }
    }
}

void changeRedirection()
{
    dup2(oldInFd, STDIN_FILENO);
    dup2(oldOpFd, STDOUT_FILENO);
}