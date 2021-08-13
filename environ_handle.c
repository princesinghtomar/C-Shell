#include "header.h"
#include "input.h"

int setenv_function(char *command[200], int len, char command_string[200])
{
    if (len != 3)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Incorrect number of arguments for setenv command \n");
        return 0;
    }
    else
    {
        if (setenv(command[1], command[2], 1) == -1)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Unable to execute setenv command\n");
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

int unsetenv_function(char *command[200], int len, char command_string[200])
{
    if (len != 2)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Incorrect number of arguments for unsetenv command \n");
        return 0;
    }
    else
    {
        if (getenv(command[1]) == NULL)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Environment variable not present\n");
            return 0;
        }
        int val = unsetenv(command[1]);
        if (val < 0)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Environment variable not found\n");
            return 0;
        }
        else
        {
            return 1;
        }
    }
}
