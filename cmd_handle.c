#include "header.h"
#include "input.h"

int dirct_command(char *str[200], int len, char command_string[200])
{
    int signal_flag = 1;
    int pipe_flag[4] = {0};
    char pipes[4][3] = {"|", ">", "<", ">>"};
    int up_flag = 0;
    for (int i = 0; i < len; i++)
    {
        for (int k = 0; k < 4; k++)
        {
            if (!strcmp(pipes[k], str[i]))
            {
                pipe_flag[k]++;
            }
        }
    }
    for (int i = 1; i < 4; i++)
    {
        up_flag = up_flag | pipe_flag[i];
    }
    if (pipe_flag[1] > 0 && pipe_flag[3] > 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Problem in Syntax\n");
        return 0;
    }
    if (pipe_flag[0])
    {
        pipe_flag[0]++;
        if (handle_pipe(command_string, pipe_flag[0]))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (up_flag)
    {
        str[len] = NULL;
        char **temp_ = redirect(str);
        if (temp_ == NULL)
            signal_flag = 0;
        else
            signal_flag = 1;
    }
    else if (!strcmp(str[len - 1], "&")) 
    {
        signal_flag = execute_back_process(str, len, command_string);
    }
    else if (!strcmp(str[0], "cd"))
    {
        signal_flag = execute_cd_func(str, len, command_string);
    }
    else if (!strcmp(str[0], "pwd"))
    {
        signal_flag = execute_pwd_func(str, len, command_string);
    }
    else if (!strcmp(str[0], "echo"))
    {
        signal_flag = execute_echo_func(str, len, command_string);
    }
    else if (!strcmp(str[0], "ls"))
    {
        signal_flag = execute_ls_func(str, len, command_string);
    }
    else if (!strcmp(str[0], "pinfo"))
    {
        signal_flag = execute_pinfo_func(str, len, command_string);
    }
    else if (!strcmp(str[0], "history"))
    {
        signal_flag = print_history(str, len, command_string);
    }
    else if (!strcmp(str[0], "nightswatch"))
    {
        signal_flag = nightswatch(str, len, command_string);
    }
    else if (!strcmp(str[0], "setenv"))
    {
        signal_flag = setenv_function(str, len, command_string);
    }
    else if (!strcmp(str[0], "unsetenv"))
    {
        signal_flag = unsetenv_function(str, len, command_string);
    }
    else if (!strcmp(str[0], "jobs"))
    {
        signal_flag = jobs(len);
    }
    else if (!strcmp(str[0], "overkill"))
    {
        signal_flag = overkill(str, len, command_string);
    }
    else if (!strcmp(str[0], "kjob"))
    {
        signal_flag = kjob(str, len, command_string);
    }
    else if (!strcmp(str[0], "fg"))
    {
        signal_flag = fg(str, len, command_string);
    }
    else if (!strcmp(str[0], "bg"))
    {
        signal_flag = bg(str, len, command_string);
    }
    else
    {
        signal_flag = execute_front_process(str, len, command_string);
    }
    return signal_flag;
}
int dist_command_2(char *command)
{
    int sig_flag = 1;
    int flag_com = 0;
    char command_string[200] = "\0";
    strcpy(command_string, command);
    char *str[200];
    int i = 0;
    char *token = strtok(command, "\t \n");
    while (token != NULL)
    {
        flag_com = 1;
        str[i] = token;
        i++;
        token = strtok(NULL, "\t \n");
    }
    if (flag_com)
    {
        sig_flag = dirct_command(str, i, command_string);
    }
    free(token);
    return sig_flag;
}
int dist_command_1(char *command)
{
    int val = 0;
    char temp[200] = "\0";
    char *token = strtok(command, ";");
    while (token != NULL)
    {
        strcpy(temp, token);
        token = strtok(NULL, ";");
        if (strcmp(temp, "") || strcmp(temp, " ") || strcmp(temp, "   ") || temp[0] != '\t')
        {
            val = dist_command_2(temp);
        }
    }
    free(token);
    return val;
}