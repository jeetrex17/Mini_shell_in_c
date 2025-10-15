#ifndef SHELL_H
#define SHELL_H

// systems headers
#include <stdio.h>
#include <stdlib.h> 

//constants 
#define  JEET_RL_BUFFER 1024  // rl = readline 
#define JEET_TOK_BUFFER 6
#define JEET_TOK_DELIM "\t\r\a\n"

//functions decalations 
void jeet_loop(void)
char *read_jeet_line(void)
char **split_jeet_line(char* line)
int jeet_launch(char **args)



#endif 
