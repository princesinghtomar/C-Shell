#include "header.h"
#include "input.h"

int execute_cd_func(char *command[200], int len, char command_string[200])
{
    char prev_dir1[5000] = "\0";
    strcpy(prev_dir1, prev_dir);
    getcwd(prev_dir, 4096);
    if (len > 2)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Too many arguments for cd\n");
        return 0;
    }
    else if (len == 1)
    {
        struct passwd s1;
        s1 = get_user_name();
        char path[500] = "/home/";
        strcat(path, s1.pw_name);
        if (chdir(path) < 0)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Target directory not found\n");
            strcpy(prev_dir, prev_dir1);
            return 0;
        }
    }
    else if (!strcmp(command[1], "-"))
    {
        if (chdir(prev_dir1) < 0)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Can't return to previous directory\n");
            return 0;
        }
        getcwd(prev_dir1, 4096);
        printf("%s\n", prev_dir1);
    }
    else if (command[1][0] == '~' || !strcmp(command[1], "~/"))
    {
        char str[100] = "\0";
        strcpy(str, command[1]);
        struct passwd s1;
        char path[500] = "\0";
        s1 = get_user_name();
        strcpy(path, "/home/");
        strcat(path, s1.pw_name);
        if (strlen(command[1]) > 2)
        {
            strcat(path, str + 1);
        }
        else
        {
            strcpy(path, "/home/");
            strcat(path, s1.pw_name);
        }
        if (chdir(path) < 0)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Target directory not found\n");
            strcpy(prev_dir, prev_dir1);
            return 0;
        }
    }
    else if (chdir(command[1]) < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Target directory not found\n");
        strcpy(prev_dir, prev_dir1);
        return 0;
    }
    return 1;
}