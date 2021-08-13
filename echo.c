#include "header.h"
#include "input.h"

int execute_echo_func(char *command[200], int len, char command_string[200])
{
    //printf("%s\n",command[1]);
    if (!strcmp(command[1], "-n"))
    {
        for (int i = 1; i < len; i++)
        {
            printf("%s ", command[i]);
        }
    }
    else
    {
        for (int i = 1; i < len; i++)
        {
            printf("%s ", command[i]);
        }
        printf("\n");
    }
    return 1;
}