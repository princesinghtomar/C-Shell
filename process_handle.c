#include "header.h"
#include "input.h"

int execute_back_process(char *command[200], int len, char command_string[200])
{
    command[len - 1] = NULL;
    for (int i = len; i >= 0; i--)
    {
        if (command_string[i] == '&')
        {
            command_string[i] = '\0';
        }
    }
    pid_t pid;
    char str_copy[600] = "\0";
    for (int i = 0; i < len - 1; i++)
    {
        strcat(str_copy, command[i]);
        strcat(str_copy, " ");
    }
    pid = fork();
    if (pid == 0)
    {
        signal(SIGINT, SIG_DFL);
        signal(SIGTSTP, SIG_DFL);
        int val = execvp(command[0], command);
        if (val == -1)
        {
            bold_red();
            printf("\nError : ");
            reset();
            printf("Failed to execute command \n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS); 
    }
    else if (pid < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Failed to fork \n");
        return 0;
    }
    else
    {
        signal(SIGCHLD, check_process);
        p_pid[child_process] = pid;
        strcpy(p_name[child_process], str_copy);
        printf("[%d]+ %d\n", child_process, pid);
        setpgid(pid, 0);
        child_process++;
        tcsetpgrp(0, getpgrp());
    }
    return 1;
}
int execute_front_process(char *command[200], int len, char command_string[200])
{
    command[len] = NULL;
    int val;
    int status;
    char str_copy[600] = "\0";
    for (int i = 0; i < len; i++)
    {
        strcat(str_copy, command[i]);
        strcat(str_copy, " ");
    }
    pid_t pid = fork();
    if (pid < 0)
    {
        bold_red();
        printf("Error : ");
        reset();
        printf("Failed to fork\n");
        return 0;
    }
    else if (pid == 0)
    {
        val = execvp(command[0], command);
        if (val == -1)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Failed to execute the command \n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);
        front_process_id = pid;
        setpgid(pid, 0);
        status = 0;
        gid_t process_gid = __getpgid(pid);
        tcsetpgrp(0, process_gid);

        int val = waitpid(pid, &status, WUNTRACED);
        if (val < 0)
        {
            bold_red();
            printf("Error : ");
            reset();
            printf("Failed to wait \n");
            kill(pid, SIGKILL);
            return 0;
        }
        tcsetpgrp(0, getpgrp());
        front_process_id = 0;
        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);

        // if we get ctrl z signal
        if (WIFSTOPPED(status))
        {

            p_pid[child_process] = pid;
            p_status[child_process] = status;
            strcpy(p_name[child_process], str_copy);
            child_process++;
            return 0;
        }
    }
    return !status;
}