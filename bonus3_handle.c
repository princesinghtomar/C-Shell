#include "header.h"
#include "input.h"

int and_n_or(char *command)
{
    char str1[500] = "\0";
    char str2[500] = "\0";
    strcpy(str1, command);
    strcpy(str2, command);
    int arr[200] = {0};
    char *token = strtok(str1, " \t\n");
    int i = 0;
    int val = 1;
    int j = 0;
    char *strip[200];
    while (token != NULL)
    {
        strip[j] = token;
        if (!strcmp(token, "$"))
        {
            arr[i] = 1;
            i++;
        }
        else if (!strcmp(token, "@"))
        {
            arr[i] = -1;
            i++;
        }
        token = strtok(NULL, " \t\n");
        j++;
    }
    int operator_number = i;
    int prev = 0;
    for (int i = 0; i < j; i++)
    {
        if ((!i || i == (j - 1)) && (!strcmp(strip[i], "@") || !strcmp(strip[i], "$")))
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Syntax is not correct\n");
            return 0;
        }
        if (!strcmp(strip[i], "@") || !strcmp(strip[i], "$"))
        {
            if (prev)
            {
                bold_red();
                printf("Error : ");
                reset();
                printf("Syntax is not correct\n");
                return 0;
            }
            else
            {
                prev = 1;
            }
        }
        else
        {
            prev = 0;
        }
    }
    token = strtok(str2, "$@");
    i = 0;
    char *str[200];
    while (token != NULL)
    {
        str[i] = token;
        token = strtok(NULL, "$@");
        i++;
    }
    val = dist_command_1(str[0]);
    for (int i = 1; i <= operator_number; i++)
    {
        if (!strcmp(str[i], "") || !strcmp(str[i], " ") || !strcmp(str[i], "  ") || !strcmp(str[i], "   "))
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Syntax is not correct\n");
            return 0;
        }
        int temp_val = dist_command_1(str[i]);
        if (arr[i - 1] == 1)
        {
            val = val | temp_val;
        }
        if (arr[i - 1] == -1)
        {
            val = val & temp_val;
        }
    }
    return val;
}