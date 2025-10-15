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
        args = split_jeet_line(line);
        status = jeet_excute(args);


        free(line)
        free(args) // never foget to free the memeotry 

    } while(status)
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

    char **tokens = malloc(sizeof(char) * buffersize);
    char *token;
    if(!token){
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
            tokens = realloc(tokens, buffersize*sizeof(char));

            if(!token){
                fprintf(stderr , "jeet says Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL , JEET_TOK_DELIM);   // contuning from where it left off 
    }

    tokens[postion] = NULL;

    return tokens;
}
