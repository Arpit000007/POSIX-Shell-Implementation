# Requirement 1
- On execution the logged in username and system name are being displayed and the directory from where the executable is run will be the home directory.
- env.cpp contains the methods implemented for this.

# Requirement 2
- cd.
    - The user will be able to cd to the folders inside the root but can not go back from the root.
    - The implementation is in Main.cpp.
- pwd.
    - The present working directory relative to the root will be printed.
    - The implementation is in Main.cpp.
- echo.
    - This will print whatever the user will give as arguments to the command.
    - The implementation is in Main.cpp. 

# Requirement 3
- ls command will list all the files in the current directory.
- The flags -l and -a are also handled.
- The implementation is in ls.cpp.

# Requirement 4
- The processes which are not implemented will run in background if "&" is present at the end or will run in foreground if "&" is not present.
- The implementation is in Main.cpp.

# Requirement 5
- pinfo will print the required information for the process id given as argument.
- If no argument is given the details of the current running process will be printed
- The implementation is in Main.cpp.

# Requirement 6
- search command will search for the file or folder passed as argument.
- All the folders under the current folder will be searched recursively.
- If the file/folder is present, true will be printed else false will be printed
- The implementation is in Search.cpp.

# Requirement 7
- The IO is redirected when "<<", ">>" and ">" are used.
- Assuming that there are spaces between and after the symbols. 
- The implementation is in redirection.cpp.

## Execution steps
```c++
- compile by running the make file - make
- run - ./output
```


