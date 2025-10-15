#include "shell.h"

int main(void)
{
    printf("Welcome to Jeet Shell!\n");
    printf("Type commands, or 'help' for info, or 'exit' to quit.\n\n");

    // Run the main shell loop
    jeet_loop();

    // Exit cleanly
    return EXIT_SUCCESS;
}

