#ifndef SHELL_H
#define SHELL_H

// systems headers
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // For fork(), chdir(), execvp()
#include <sys/wait.h>   // For waitpid()
#include <fcntl.h>   // for open()
#include <string.h>

//constants 
#define  JEET_RL_BUFFER 1024  // rl = readline 
#define JEET_TOK_BUFFER 6
#define JEET_TOK_DELIM " \t\r\a\n"

//functions decalations 
void jeet_loop(void);
char *read_jeet_line(void);
char **jeet_split_line(char* line);
int jeet_launch(char **args);

//builtin functions 
int jeet_cd(char **args);
int jeet_exit(char **args);
int jeet_help(char **args);

int jeet_execute(char **args);
    
#endif 
