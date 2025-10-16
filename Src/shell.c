#include "shell.h"
#include <string.h>

void jeet_loop(void)
{
    int status ;
    char *line; 
    char **args;

    do{
        printf("type_nigga > ");
        
        line = read_jeet_line();
        args = jeet_split_line(line);
        status = jeet_execute(args);


        free(line);
        free(args); // never foget to free the memeotry 

    } while(status);
}


// now we will make that read_jeet_line we can also use getline or fgets if needed but for learnng lets do thsi only 

char *read_jeet_line(void)
{
    int buffersize = JEET_RL_BUFFER;
    int postion = 0;
    char *buffer = malloc(sizeof(char) * buffersize);
    int c;

    if(!buffer){
        fprintf(stderr, "jeet says : Allocation error\n");
        exit(EXIT_FAILURE);
    }

    while(1){
        c = getchar(); 
        if(c == EOF || c == '\n'){
            buffer[postion] = '\0';
            return buffer;
        }
        else{
            buffer[postion] = c;
        }
        postion++;


        if(postion >= buffersize){
            buffersize += JEET_RL_BUFFER;
            buffer = realloc(buffer, buffersize);
            
            if(!buffer)
            {
                fprintf(stderr , "jeet says : Allocation error\n");
                exit(EXIT_FAILURE);
            }

        }
    }

}

// char *read_jeet_line(void){
//     char *line = NULL;
//     ssize_t = buffersize = 0;
//
//     if(getline(&line , &buffersize, stdin) == -1){
//         if(eof(stdin)){
//             exit(EXIT_SUCCESS);
//         }
//         else{
//             perror("readline");
//             exit(EXIT_FAILURE);
//         }
//     }
//     return line;
// }


char **jeet_split_line(char *line){
    int buffersize = JEET_TOK_BUFFER;
    int postion = 0;

    char **tokens = malloc(sizeof(char *) * buffersize);
    char *token;

    if(!tokens){
        fprintf(stderr, "jeet says : Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line , JEET_TOK_DELIM);
    while(token != NULL){
        tokens[postion] = token;
        postion++;

        if(postion >= buffersize)
        {
            buffersize += JEET_TOK_BUFFER;
            tokens = realloc(tokens, buffersize*sizeof(char *));

            if(!tokens){
                fprintf(stderr , "jeet says Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL , JEET_TOK_DELIM);   // contuning from where it left off

    }

    tokens[postion] = NULL;

    return tokens;
}


int jeet_launch(char **args){
    pid_t pid , wpid; // if pid = 0 its running child process , if pid > 0 then parrent else error 
    int status;

    pid = fork();
    if(pid == 0){   //child process 
        if (execvp(args[0], args) == -1){
            perror("Nigga");
        }
        exit(EXIT_FAILURE);
    }
    else if(pid < 0){
        // error while forking
        perror("Nigga");
    }
    else{
        do {
            wpid = waitpid(pid , &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

// making bultin functions

int jeet_cd(char **args);
int jeet_help(char **args);
int jeet_exit(char **args);

char *builtin_str[] = {
    "cd", "help" , "exit"
};

int (*builtin_func[])(char **) = {
    &jeet_cd,
    &jeet_help,
    &jeet_exit
};


int jeet_num_builtin(){
    return (sizeof(builtin_func) / sizeof(char *));
}


// now implementing the builting func cd help and exit 

int jeet_cd(char **args){
    if(args[1] == NULL){
        fprintf(stderr , "Nigga taking you back to jail\n");

        if(chdir(getenv("HOME")) != 0){
            perror("Nigga");
        }
    }
    else { // here we will call chdir() a system call in child process
        if(chdir(args[1]) != 0){
            perror("nigga\n");
        }
    }

    return 1;
}

int jeet_help(char **args) {
    int n = jeet_num_builtin();
    printf(
        "    ____. _________ ___ ______________.____    .____     \n"
        "   |    |/   _____//   |   \\_   _____/|    |   |    |    \n"
        "   |    |\\_____  \\/    ~    \\    __)_ |    |   |    |    \n"
        " /\\__|    |/        \\    Y    /        \\|    |___|    |___ \n"
        " \\________/_______  /\\___|_  /_______  /|_______ \\_______ \\\n"
        "                  \\/       \\/        \\/         \\/       \\/\n"
        "\n"
        "          Slaves at your service\n"
        "------------------------------------------------------\n"
        "Built-ins: %d\n"
        "  cd    : change directory\n"
        "  help  : show this message\n"
        "  exit  : exit the shell\n"
        "\n",
        n
    );

    return 1;
}

int jeet_exit(char **args){
    printf("Bye nigga dont shot and steal\n");
    return 0;
}

int jeet_execute(char **args){
    if(args[0] == NULL){
        fprintf(stderr , "Bro what ?? why empty coomand? why ??? \n ");
        return 1;
    
    }

    for( int i = 0; i < jeet_num_builtin() ; i++){
       if(strcmp(args[0] , builtin_str[i]) == 0){
            return (*builtin_func[i])(args);
        }
    }

    return jeet_launch(args);
}
